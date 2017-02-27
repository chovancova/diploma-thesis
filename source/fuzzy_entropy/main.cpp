#include "Dataset.h"
#include "KMeans.h"
#include "FuzzyClassiffication.h"

int main(int argc, char *argv[])
{
	/*if (argc != 3)
	{
		printf("Usage: %s DATASET_TYPE DATASET_FILE", argv[0]);
		return 1;
	}*/
	//std::string ds_type(argv[1]);
	//std::string ds_file(argv[2]);
	std::string ds_type("iris");
	std::string ds_file("iris.data");

	Dataset *dataset = Dataset::create(ds_type, ds_file);
	if (dataset == nullptr)
	{
		return 1;
	}
	
	dataset->normalise();
	dataset->print();
	
	struct FuzzyClassifficationInit fuzzy_init_struct;
	
	fuzzy_init_struct.centers_count = 3;
	fuzzy_init_struct.learning_rate = 0.01f;
	fuzzy_init_struct.class_count = 3;

	FuzzyClassiffication fuzzy_classiffication(dataset, fuzzy_init_struct);


	/*
	KMeans k_means(8, iris.get(0).features.size());


	unsigned iterations_max = 100000;
	float learning_rate = 0.01;

	for (unsigned iterations = 0; iterations < iterations_max; iterations++)
	{
		unsigned int idx = rand() % iris.getSize();
		struct DataItem item = iris.get(idx);
		k_means.process(item, learning_rate);
	}


	 

	printf("\n");
	for (unsigned i = 0; i < k_means.getSize(); i++)
	{
		struct DataItem item = k_means.get_center(i);
		for (unsigned j = 0; j < item.features_normalised.size(); j++)
			printf("%f \t", item.features_normalised[j]);

		printf("\n");

	}

	for (unsigned idx = 0; idx < iris.getSize(); idx++)
	{
		iris.print(idx);

		k_means.process(iris.get(idx), 0.0);

		k_means.print_result();
		printf("\n");
	}


	*/

	printf("program done\n");
	getchar();

	return 0;
}





/**
* Step A. Determination of number of intervals on each dimension.		
	* Step 1) Set the initial number of intervals I = 2. 
	* Step 2) Locate the centers of intervals. (III-B)
	* Step 3) Assign membership function for each interval.  (III-C)							DONE
	* Step 4) Compute the total fuzzy entropy of all intervals for I and I-1 intervals. (II-C) 
	* Step 5) Does the total fuzzy entropy decrease? 
	*			If yes, then partition again (I := I + 1) and go to Step 2;
	*			else go to Step 6. 
	* Step 6) Stop further partiotioning on this dimension and I-1 is the number of intervals. 
*
*
* Step B. Determination of the Interval Locations				DONE
	*		(Determinig the center and width of each interval)
	* Step 1) Set the initial number of clusters, I.
	* Step 2) Set initial centers of clusters.
	* Step 3) Assign cluster label to each element.  
	* Step 4) Recompute the cluster centers. 
	* Step 5) Does any center change? Yes, Stop, Otherwise go to Step 3. 
* 
* Step C. Assign a membership function for each interval.		DONE
	* Case I) The left-most interval. 
	* Case II) The right-most interval. 
	* Case III) The internal intervals. 
* 
* Step D. Class Label Assignment
*	Compute the fuzzy entropy of each feature via summation of the fuzzy entropy of 
*	all intervals in this feature dimension. (II-C)
*		 Evaluation method for fuzzy entropy to set the class of each decision region.  
*		 Assign the decision region to the class with the lowest entropy in this region. 
*		 Once each decision region is given a class label, the traing process is completed. 
*/