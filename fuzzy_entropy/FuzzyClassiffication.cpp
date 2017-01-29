#include "FuzzyClassiffication.h"
#include "MembershipFunction.h"


FuzzyClassiffication::FuzzyClassiffication(IDataset* dataset, FuzzyClassifficationInit init_struct)
{
	this->dataset = dataset;
	this->init_struct = init_struct;

	for (unsigned int i = 0; i < init_struct.class_count; i++)
		match_degree.push_back(0.0);

	// DetermineNumberOfIntervals();

	result_log = new CFloatLog("result_iris.txt", true);

	unsigned centers_count = 5;
	ProcessClassification(centers_count);
}

FuzzyClassiffication::~FuzzyClassiffication()
{
	if (kmeans != nullptr)
	{
		delete kmeans;
		kmeans = nullptr;
	}

	delete result_log;
}

void FuzzyClassiffication::DetermineNumberOfIntervals()
{
	unsigned int centers_count_max = 50;
	for (unsigned int centers_count = 2; centers_count < centers_count_max; centers_count++)
	{
		//create new kmeans
		kmeans = new KMeans(centers_count, dataset->getFeatureSize(), init_struct.class_count);

		//train kmeans using dataset
		trainKMeans();
		
		compute_fuzzy_entropy();

		/*
		//zratanie entropie
		float entropy = computeEntropy();
		printf("entropy %f\n", entropy);
		*/


		//if (nie je zlepsneie)
		delete kmeans;
		kmeans = nullptr;
	}

	printf("\n");

}

void FuzzyClassiffication::ProcessClassification(unsigned int centers_count)
{
	kmeans = new KMeans(centers_count, dataset->getFeatureSize(), init_struct.class_count);
	trainKMeans();

	MembershipFunction *membership_function = new MembershipFunction(kmeans);


	std::vector<struct DataItem> result;

	float success_count = 0.0;
	float error_count = 0.0;

	for (unsigned int i = 0; i < dataset->getSize(); i++)
	{
		struct DataItem tmp = dataset->get(i);

		kmeans->process(tmp, 0.0);
		struct KMeansResult kmeans_result = kmeans->get();

		membership_function->process(tmp.features_normalised);


		std::vector<std::vector<float>> membership_result = membership_function->get();

		
		for (unsigned int k = 0; k < membership_result[0].size(); k++)
		{
			for (unsigned int j = 0; j < membership_result.size(); j++)
				result_log->put_value(membership_result[j][k]);
			result_log->put_separator(" | ");
		}

		result_log->put_separator("=> ");

		unsigned int required_max_j = 0;
		for (unsigned int j = 0; j < tmp.label.size(); j++)
		{
			if (tmp.label[j] > tmp.label[required_max_j])
				required_max_j = j;
		}

		unsigned int result_max_j = 0;
		for (unsigned int j = 0; j < kmeans_result.label.size(); j++)
		{
			if (kmeans_result.label[j] > kmeans_result.label[result_max_j])
				result_max_j = j;
			result_log->put_value(kmeans_result.label[j]);
		}
	
		result_log->put_separator("=> ");
		result_log->put_value(required_max_j);
		result_log->put_value(result_max_j);

		if (result_max_j == required_max_j)
		{
			success_count += 1.0;
		}
		else
		{
			error_count += 1.0;
			result_log->put_separator("FAILED ");
		}


		result_log->put_line();
	}

	printf("success rate %f %%\n", 100.0*success_count / (success_count + error_count));

	delete membership_function;
	delete kmeans;
	kmeans = nullptr;
}


void FuzzyClassiffication::trainKMeans()
{
	//init centers from dataset
	for (unsigned int i = 0; i < kmeans->getSize(); i++)
	{
		DataItem item;
		item = dataset->rndFromArray();
		kmeans->setCenter(item, i);
	}

	unsigned int iterations = 0, iterations_max = 10000;

	float k = 0.1;
	float center_difference = 1.0;

	//unsupervised k-means learning
	do
	{
		DataItem item;
		item = dataset->rndFromArray();
		float center_difference_tmp = kmeans->process(item, init_struct.learning_rate);

		center_difference = (1.0 - k)*center_difference + k*center_difference_tmp;

		iterations++;
	} while ((center_difference > 0.000001) && (iterations < iterations_max));

	// printf("iterations %u diff %f\n", iterations, center_difference);
}




float FuzzyClassiffication::compute_fuzzy_entropy()
{
	float result = 0.0;


	std::vector<float> fuzzy_entropy;
	for (unsigned int cluster_id = 0; cluster_id < kmeans->getSize(); cluster_id++) // F(A), F(B), F(C) -> center memership
		fuzzy_entropy.push_back(compute_fuzzy_entropy_of_interval(cluster_id));					//P1 v clanku	
	
	printf("\n");
	for (unsigned int center = 0; center < kmeans->getSize(); center++)
	{
		printf("%6.3f ", fuzzy_entropy[center]);
		result += fuzzy_entropy[center];
	}
	printf(" >>> %6.3f \n", result);

	return result;
}

float FuzzyClassiffication::compute_fuzzy_entropy_of_interval(unsigned int cluster_id)
{
	std::vector<float> match_degree;
	
	MembershipFunction *membership_function = new MembershipFunction(kmeans);

	float elements_count = 0.0;

	for (unsigned int class_index = 0; class_index < init_struct.class_count; class_index++)
	{
		std::vector<struct DataItem> class_ = generate_scj(class_index);

		float total_membership_degree = 0.0;

		for (unsigned int element_idx = 0; element_idx < class_.size(); element_idx++)
		{
			kmeans->process(class_[element_idx], 0.0);

			//v clanku P5 : z class_ sa vyberu len tie ktore patria k klastru "cluster_id"
			if (kmeans->get().cluster_id == cluster_id)
			{
				//spocita membership
				membership_function->process(class_[element_idx].features_normalised);

				//scitaju sa vsetky features
				float feature_sum = 0.0;
				
				
				for (unsigned int feature = 0; feature < class_[element_idx].features_normalised.size(); feature++)
					feature_sum += membership_function->get()[cluster_id][feature];
				feature_sum /= class_[element_idx].features_normalised.size();

				// feature_sum += membership_function->get()[cluster_id][0];
				total_membership_degree+= feature_sum;
				elements_count += 1.0;
			}
		}


		//v clanku P4, zatial este len membership degree (treba vydelit)
		match_degree.push_back(total_membership_degree);
	}



	printf("[%u %6.3f] ", cluster_id, elements_count);


	//v clanku ako P3
	float match_degree_sum = 0.0;
	for (unsigned int class_index = 0; class_index < init_struct.class_count; class_index++)
	{
		match_degree_sum += match_degree[class_index];
	}

	//v clanku ako P3 , match degree
	for (unsigned int class_index = 0; class_index < init_struct.class_count; class_index++)
	{
		match_degree[class_index] /= match_degree_sum;
	}

	//v clanku ako P2, match degree prepocita na entropiu
	float result = 0.0;
	for (unsigned int class_index = 0; class_index < init_struct.class_count; class_index++)
	{
		if (match_degree[class_index] > 0.0)
		result += -match_degree[class_index]*log2f(match_degree[class_index]);
	}

	delete membership_function;

	//pokutova funkcia -> cim menej elements_count, tym vyssia entropia
	float strmost = 10.0;
	result = result*strmost/(strmost + elements_count);

	return result;
}


std::vector<struct DataItem> FuzzyClassiffication::generate_scj(unsigned int class_index)
{
	std::vector<struct DataItem> result;

	for (unsigned int i = 0; i < dataset->getSize(); i++)
	{
		struct DataItem tmp = dataset->get(i);
		if (tmp.label[class_index] > 0.0)
			result.push_back(tmp);
	}

	return result;
}
