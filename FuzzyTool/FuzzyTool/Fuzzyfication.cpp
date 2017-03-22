#include "Fuzzyfication.h"
#include <cstring>
#include <iostream>
#include <ctime>
#define EPSILON 0.00001f


/**
* \brief Initialize datasets, fuzzification,
* Set the initial number of Interval to 2.
* \param id_dataset Number of dataset.
*/
Fuzzyfication::Fuzzyfication(unsigned int id_dataset) : DataSets(id_dataset)
{
	IdDataset = id_dataset;

	///<code>Set the initial number of interval I = 2.</code> 
	Intervals = std::vector<unsigned int>(Attributes, 2);;
	char file_name[99];
	strcpy(file_name, PATH_OUTPUT_FOLDER);
	strcat(file_name, NameDataset);
	strcat(file_name, ".log.txt");

	LogFile = fopen(file_name, "a+");

	if (LogFile == nullptr)
	{
		printf("Error in LogFile - Fuzzyfication()\n");
	}
}

/**
 * \brief Desctructor fo fuzzyfication class. 
 */
Fuzzyfication::~Fuzzyfication()
{
	fclose(LogFile);
}

void Fuzzyfication::RunFuzzification(unsigned int method)
{
	switch (method)
	{
	case 1: run_fuzzification_febfc();
		break;
	default: run_fuzzification_febfc();
		break;
	}
}


void Fuzzyfication::run_fuzzification_febfc()
{
	char filename_fuzzy[200];
	initialize_filename(filename_fuzzy);
	
	fprintf(LogFile, "**********************************************************************************\n");
	fprintf(LogFile, "File name of fuzzy results:\t %s\n", filename_fuzzy);

	initialize_dataset();

	unsigned long count_result;
	std::vector<unsigned long> new_result; 
	std::vector<float> result; 

	int does_entropy_decrease;
	float  old_entropy, new_entropy;

	/////////////////////////////////////////////STEP 1////////////////////////////////////////////////

	//DETERMINATION OF THE NUMBER OF INTERVALS
	//Set initial number of intervals I = 2; 
	febfc_step_1_create_features();

	//For each dimension 
	for (unsigned int dimension = 0; dimension < InputAttributes; dimension++)
	{
		print_to_console_dimension(dimension);

		if (LingvisticAttributes[dimension] != 0)
		{
			set_lingvistic_attributes(dimension);
		}
		else //real - value attribute (discretization of attributes) 
		{
			initialize_variables_for_entropy_result(count_result, new_result, result, does_entropy_decrease, new_entropy, dimension);		
		do
			{
				old_entropy = new_entropy;
				if (does_entropy_decrease != 0)
				{
					modify_features(dimension, does_entropy_decrease);
				}
				/////////////////////////////////////////////STEP 2////////////////////////////////////////////////
				//DETERMINATION OF THE NUMBER OF INTERVALS
				//Locate the centers of interval
				std::vector<float> cluster = febfc_step_2_locate_center_of_interval(dimension, result, new_result, count_result);

				/////////////////////////////////////////////STEP 3////////////////////////////////////////////////
				//Assighn memberhsip function for each interval 
				febfc_step_3_assign_membership_function(dimension, cluster);

				/////////////////////////////////////////////STEP 4////////////////////////////////////////////////
				//Compute the total fuzzy entropy of all intervals for I and I-1 intervals. 
				new_entropy = febfc_step_4_compute_total_fuzzy_entropy(dimension);

				print_to_log_file_new_entropy(new_entropy, dimension);

				/////////////////////////////////////////////STEP 5////////////////////////////////////////////////
				if (febfc_step_5_does_entropy_decrese(count_result, does_entropy_decrease, old_entropy, new_entropy, dimension)) 
					break;

			} while (true);
		
			print_to_log_file_temporary_results();
			
			std::cout << "Write Fuzzyfication Result to file.\n";
			
			print_to_cm_file_results(filename_fuzzy);

			
		}
	}
}

void Fuzzyfication::initialize_variables_for_entropy_result(unsigned long& count_result, std::vector<unsigned long>& new_result, std::vector<float>& result, int& does_entropy_decrease, float& new_entropy, unsigned dimension)
{
	does_entropy_decrease = 0;
	new_entropy = 1000000000.0;
	result = std::vector<float>(DatasetSize, 0.0);
	new_result = std::vector<unsigned long>(DatasetSize, 0l);
	count_result = create_ascending_result(dimension, result, new_result);
}


void Fuzzyfication::set_lingvistic_attributes(unsigned int dimension) 
{
	unsigned int temp_interval;
	Intervals[dimension] = LingvisticAttributes[dimension];
	for (unsigned long x = 0; x < DatasetSize; x++)
	{
		temp_interval = static_cast<unsigned int>(Pattern[x].Feature[dimension]);
		FuzzySetOnInterval[dimension][temp_interval][x] = 1.0f;
	}
}


bool Fuzzyfication::febfc_step_5_does_entropy_decrese(unsigned long count_result, int& does_entropy_decrease, float old_entropy, float new_entropy, unsigned dimension) 
{
	if (does_entropy_decrease == -1 || Intervals[dimension] == count_result)
	{
		return true;
	}

	if (new_entropy <= old_entropy)
	{
		does_entropy_decrease = 1;
	}
	else
	{
		return true;
	}
	return false;
}

void Fuzzyfication::print_to_log_file_new_entropy(float new_entropy, unsigned dimension)
{
	fprintf(LogFile, "\nDimension:\t %d  \nNumber of interval in dimension:\t %d  \nNew Entropy:\t %f\n\n", dimension, Intervals[dimension], new_entropy);
}

void Fuzzyfication::print_to_console_dimension(unsigned dimension)
{
	printf("\nInput attributes (dimension):\t %d\n", dimension);
}


void Fuzzyfication::initialize_dataset()
{
	ReadDataSets(IdDataset);
	Normalization();
}


/***
 * Membership function assigmnment is a procedure for assigning a membership function to each interval. 
 */
 //-------------------------------III.C--MEMBERSHIP FUNCTION ASSIGMENT---------------------------------------
 //-------------------------------CASE 1 - THE LEFT-MOST INTERVAL -------------------------------------------
 //-------------------------------CASE 2 - THE RIGHT-MOST INTERVAL -------------------------------------------
 //-------------------------------CASE 3 - THE INTERNAL INTERVAL -------------------------------------------
void Fuzzyfication::febfc_step_3_assign_membership_function(unsigned int attribute, std::vector<float>& center)
{
	//All X = x1..xn
	for (unsigned long x = 0; x < DatasetSize; x++)
	{
		for (unsigned int interval = 0; interval < Intervals[attribute]; interval++)
		{
			FuzzySetOnInterval[attribute][interval][x] = 0;
		}

		for (unsigned int interval = 0; interval < Intervals[attribute] - 1; interval++)
		{
			if ((Pattern[x].Feature[attribute] >= center[interval])			// x >= c1
				&& (Pattern[x].Feature[attribute] <= center[interval + 1]))  //x <= c2
			{
				//-------------------------------CASE 2 - THE RIGHT-MOST INTERVAL -------------------------------------------
				//the right-most interval , for x <= c2
				FuzzySetOnInterval[attribute][interval][x] =
					(center[interval + 1] - Pattern[x].Feature[attribute]) //(c4 - x) / (c4 - c3)
					/
					(center[interval + 1] - center[interval]);

				//-------------------------------CASE 1 - THE LEFT-MOST INTERVAL -------------------------------------------
				//the left most interval x > c1 
				FuzzySetOnInterval[attribute][interval + 1][x] =
					(Pattern[x].Feature[attribute] - center[interval]) // (x - c1) / (c2 - c1)
					/
					(center[interval + 1] - center[interval]);
			}
		}

		//-------------------------------CASE 3 - THE INTERNAL INTERVAL -------------------------------------------
		if (Pattern[x].Feature[attribute] < center[0]) //x < c1
		{
			FuzzySetOnInterval[attribute][0][x] = 1.0;
		}

		if (Pattern[x].Feature[attribute] > center[Intervals[attribute] - 1]) //x > c1 - 1
		{
			FuzzySetOnInterval[attribute][Intervals[attribute] - 1][x] = 1.0;
		}
	}
}


void Fuzzyfication::febfc_step_1_create_features()
{
	unsigned int attr, intervals;

	for (attr = 0; attr < Attributes; attr++)
	{
		if (LingvisticAttributes[attr] != 0)
		{
			Intervals[attr] = LingvisticAttributes[attr];
		}
		else
		{
			//Set initial number of intervals to 2. 
			Intervals[attr] = 2;
		}
	}

	
	//FuzzySetOnInterval = ( float***) new float**[Attributes];
	FuzzySetOnInterval = std::vector< std::vector<std::vector<float>>>(Attributes, std::vector<std::vector<float>>(0.0));

	for (attr = 0; attr < Attributes; attr++)
	{
		//FuzzySetOnInterval[attr] = (float**) new float*[Intervals[attr]];
		
		FuzzySetOnInterval[attr] = std::vector<std::vector<float>>(Intervals[attr], std::vector<float>(0.0));
		
		for (intervals = 0; intervals < Intervals[attr]; intervals++)
		{
			//FuzzySetOnInterval[attr][intervals] = (float*)newFloat(DatasetSize, 0.0, "FuzzySetOnInterval[attr][intervals] in febfc_step_1_create_features()");
			FuzzySetOnInterval[attr][intervals] = std::vector<float>(DatasetSize, 0.0);
		}
	}

	for (unsigned long x = 0; x < DatasetSize; x++) // Initialisation of Output Attribute
	{
		intervals = (unsigned int)Pattern[x].Feature[InputAttributes];
		FuzzySetOnInterval[InputAttributes][intervals][x] = 1.0;
	}
}

void Fuzzyfication::modify_features(unsigned int attr, int interval_new_value) 
{
	FuzzySetOnInterval[attr].erase(FuzzySetOnInterval[attr].begin() );
	
	Intervals[attr] += interval_new_value;
	FuzzySetOnInterval[attr] = std::vector<std::vector<float>>(Intervals[attr], std::vector<float>(0.0));
	
	for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
	{
		FuzzySetOnInterval[attr][interval] = std::vector<float>(DatasetSize, 0.0);
	}
}

void Fuzzyfication::delete_features() 
{
	FuzzySetOnInterval.empty();
}


unsigned long Fuzzyfication::create_ascending_result(unsigned int dimension, std::vector<float>& result, std::vector< unsigned long>& new_result)
{
	unsigned int new_item;
	unsigned long number_of_elements = 1;
	result[0] = Pattern[0].Feature[dimension];
	new_result[0] = 1;
	for (unsigned long k = 1; k < DatasetSize; k++)
	{
		new_item = 1;
		for (unsigned long q = 0; q < number_of_elements; q++)
			if (Pattern[k].Feature[dimension] == result[q])
			{
				new_item = 0;
				new_result[q]++;
			}
		if (new_item == 1)
		{
			result[number_of_elements] = Pattern[k].Feature[dimension];
			new_result[number_of_elements] = 1;
			number_of_elements++;
		}
	}
	sort_ascending_order(result, new_result, number_of_elements);
	return (number_of_elements);
}


void Fuzzyfication::sort_ascending_order(std::vector<float>& result, std::vector< unsigned long> &new_result, unsigned long &number_of_elements)
{
	unsigned long i;
	unsigned long index = 0L;
	unsigned long value;
	float min;

	do
	{
		min = result[index];
		i = index;

		for (unsigned long k = index + 1; k < number_of_elements; k++)
		{
			if (result[k] < min)
			{
				min = result[k];
				i = k;
			}
		}

		result[i] = result[index];
		result[index] = min;

		value = new_result[i];

		new_result[i] = new_result[index];
		new_result[index] = value;

		index++;
	}
	while (index < number_of_elements - 1);
}


void Fuzzyfication::sort_ascending_order(std::vector<float> &cut_points, unsigned int &number_of_cutting_points)
{
	unsigned int i, num, index = 0;
	float min;
	do
	{
		min = cut_points[index];
		num = index;
		for (i = index + 1; i < number_of_cutting_points; i++)
			if (cut_points[i] < min)
			{
				min = cut_points[i];
				num = i;
			}
		cut_points[num] = cut_points[index];
		cut_points[index] = min;
		index++;
	}
	while (index < number_of_cutting_points - 1);
}


void Fuzzyfication::initialize_filename(char (&filename_fuzzy)[200])
{
	strcpy(filename_fuzzy, PATH_OUTPUT_FOLDER);

	time_t raw_time;
	std::tm* time_info;
	char buffer[20];
	time(&raw_time);
	time_info = std::localtime(&raw_time);
	std::strftime(buffer, 20, "%Y-%m-%d-%H-%M-%S", time_info);
	std::puts(buffer);
	strcat(filename_fuzzy, NameDataset);
	strcat(filename_fuzzy, "_");
	strcat(filename_fuzzy, buffer);
	strcat(filename_fuzzy, ".cm.txt"); // cluster centers
}

//   .----------------. .-----------------..----------------. .----------------. .----------------. .----------------. .----------------. 
//  | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
//  | |  _________   | | | ____  _____  | | |  _________   | | |  _______     | | |     ____     | | |   ______     | | |  ____  ____  | |
//  | | |_   ___  |  | | ||_   \|_   _| | | | |  _   _  |  | | | |_   __ \    | | |   .'    `.   | | |  |_   __ \   | | | |_  _||_  _| | |
//  | |   | |_  \_|  | | |  |   \ | |   | | | |_/ | | \_|  | | |   | |__) |   | | |  /  .--.  \  | | |    | |__) |  | | |   \ \  / /   | |
//  | |   |  _|  _   | | |  | |\ \| |   | | |     | |      | | |   |  __ /    | | |  | |    | |  | | |    |  ___/   | | |    \ \/ /    | |
//  | |  _| |___/ |  | | | _| |_\   |_  | | |    _| |_     | | |  _| |  \ \_  | | |  \  `--'  /  | | |   _| |_      | | |    _|  |_    | |
//  | | |_________|  | | ||_____|\____| | | |   |_____|    | | | |____| |___| | | |   `.____.'   | | |  |_____|     | | |   |______|   | |
//  | |              | | |              | | |              | | |              | | |              | | |              | | |              | |
//  | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
//   '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' 


//---------------------------II.C.--FUZZY ENTROPY OF AN INTERVAL FOR EACH FEATURE DIMENSION---------------------------------------
//---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
//---------------------------II.C.----STEP 2 - SET FUZZY SET A CONTAINS K ELEMENTS ---------------------------
//---------------------------II.C.----STEP 3 - SET ARRAY REPRESENTING M CLASSES INTO WHICH THE N ELEMENTS ARE DEVIDED -------
//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
//---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
//---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------

float Fuzzyfication::febfc_step_4_compute_total_fuzzy_entropy(unsigned int attr)
{
	//1) Let X = {r1, ... , rn} be a universal set with elements ri distributed in pattern space where i = 1..n. 
	//2) Let A be a fuzzy set defined on a interval of pattern space which kontains k elements (k < n). 

	//classes 
	std::vector<unsigned long> count_m;
	count_m = std::vector<unsigned long>(Intervals[attr], 0L);

	//---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
	std::vector<std::vector<float>> sum_mu = std::vector<std::vector<float>>(Intervals[attr], std::vector<float>(Intervals[attr], 0.0));
	std::vector<std::vector<std::vector<float>>> mu = std::vector<std::vector<std::vector<float>>>(Intervals[attr], std::vector<std::vector<float>>(Intervals[attr], std::vector<float>(OutputIntervals, 0.0)));

	//---------------------------II.C.----STEP 2 - SET FUZZY SET A CONTAINS K ELEMENTS ---------------------------
	//---------------------------II.C.----STEP 3 - SET ARRAY REPRESENTING M CLASSES INTO WHICH THE N ELEMENTS ARE DEVIDED -------
	//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
	compute_mu_function(attr, count_m, mu);
	//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
	// Wage Degree Calculation
	compute_wage_degree_calculation(attr, sum_mu, mu);

	print_to_log_file_classes(attr, count_m);

	//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
	//---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
	//---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
	//  Fuzzy Entropy Calculation
	// The fuzzy entropy FE on the universal uset X for the elements within an interval 
	float total_fuzzy_entropy = 0.0f;
	compute_total_fuzzy_entropy(attr, total_fuzzy_entropy, count_m, sum_mu, mu);

	// delete M and sumM
	dealocate_pointers_entropy(attr, count_m, mu, sum_mu);

	return total_fuzzy_entropy;
}


void Fuzzyfication::compute_wage_degree_calculation(unsigned attr, std::vector<std::vector<float>>& sum_mu, std::vector<std::vector<std::vector<float>>>& mu)
{
	//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
		for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
			for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
				sum_mu[class_m][j_a] += mu[class_m][j_a][j_b];
}

void Fuzzyfication::compute_mu_function(unsigned attr, std::vector<unsigned long>& count_m, std::vector<std::vector<std::vector<float>>>& mu)
{
	float max = 0.0f;
	unsigned int class_m = 0;

	for (unsigned long data_item = 0; data_item < DatasetSize; data_item++)
	{
		max = FuzzySetOnInterval[attr][0][data_item];
		//SCJ - set of elements of class j on the universal set X. 
		//It is a subset of the universal X. 
		//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
		set_scj_on_universal_set_x(attr, class_m, max, data_item);

		count_m[class_m]++;

		// Membership Degree Calculation
		match_degree_calculation(attr, class_m, mu, data_item);
	}
}

void Fuzzyfication::match_degree_calculation(unsigned attr, unsigned class_m, std::vector<std::vector<std::vector<float>>>& mu, unsigned long& data_item)
{
	for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
	{
		for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
		{
			mu[class_m][j_a][j_b] += FuzzySetOnInterval[attr][j_a][data_item] * FuzzySetOnInterval[InputAttributes][j_b][data_item];
		}
	}
}

void Fuzzyfication::set_scj_on_universal_set_x(unsigned attr, unsigned& class_m, float& max, unsigned long& data_item)
{
	//---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
	for (unsigned int j = 0; j < Intervals[attr]; j++)
	{
		if (max <= FuzzySetOnInterval[attr][j][data_item])
		{
			class_m = j;
			max = FuzzySetOnInterval[attr][j][data_item];
		}
	}
}


void Fuzzyfication::print_to_log_file_classes(unsigned attr, std::vector<unsigned long> count_m)
{
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
		fprintf(LogFile, "Members in cluster %d :\t %d \n", class_m, count_m[class_m]);
}

void Fuzzyfication::compute_total_fuzzy_entropy(unsigned attr, float& total_fuzzy_entropy, std::vector<unsigned long> count_m, std::vector<std::vector<float>> &sum_mu, std::vector<std::vector<std::vector<float>>>& mu)
{
	float new_entropy = 0.0f;
	float match_degree_d_j = 0.0f;
	for (unsigned int class_m = 0; class_m < Intervals[attr]; class_m++)
	{
		new_entropy = 0.0;
		for (unsigned int j_a = 0; j_a < Intervals[attr]; j_a++)
			for (unsigned int j_b = 0; j_b < OutputIntervals; j_b++)
			{
				//---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
				if (static_cast<float>(sum_mu[class_m][j_a] == 0))
				{
					match_degree_d_j = 0;
				}
				else
				{
					match_degree_d_j = (mu[class_m][j_a][j_b] / sum_mu[class_m][j_a]);
				}

				//---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
				if (!(mu[class_m][j_a][j_b] == 0))
				{
					new_entropy -= match_degree_d_j * log2(match_degree_d_j);
				}
				//	fprintf(LogFile, "dimension=%d, jb=%d, p=%f New Entropy =%f\n", class_m, jb, p, new_entropy);
			}

		//---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
		total_fuzzy_entropy += new_entropy * static_cast<float>(count_m[class_m]) / DatasetSize;
	}
}

void Fuzzyfication::dealocate_pointers_entropy(unsigned attr, std::vector<unsigned long> &count_m, std::vector<std::vector<std::vector<float>>>& mu, std::vector<std::vector<float>>& sum_mu)
{
	mu.clear();
	sum_mu.clear();
	count_m.clear();
}

//   .----------------. .----------------. .----------------. .----------------. .----------------. .-----------------..----------------. 
//  | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
//  | |     ______   | | |              | | | ____    ____ | | |  _________   | | |      __      | | | ____  _____  | | |    _______   | |
//  | |   .' ___  |  | | |              | | ||_   \  /   _|| | | |_   ___  |  | | |     /  \     | | ||_   \|_   _| | | |   /  ___  |  | |
//  | |  / .'   \_|  | | |    ______    | | |  |   \/   |  | | |   | |_  \_|  | | |    / /\ \    | | |  |   \ | |   | | |  |  (__ \_|  | |
//  | |  | |         | | |   |______|   | | |  | |\  /| |  | | |   |  _|  _   | | |   / ____ \   | | |  | |\ \| |   | | |   '.___`-.   | |
//  | |  \ `.___.'\  | | |              | | | _| |_\/_| |_ | | |  _| |___/ |  | | | _/ /    \ \_ | | | _| |_\   |_  | | |  |`\____) |  | |
//  | |   `._____.'  | | |              | | ||_____||_____|| | | |_________|  | | ||____|  |____|| | ||_____|\____| | | |  |_______.'  | |
//  | |              | | |              | | |              | | |              | | |              | | |              | | |              | |
//  | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
//   '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' 
//   .----------------. .----------------. .----------------. .----------------. .----------------. .----------------. .----------------. 
//  | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
//  | |     ______   | | |   _____      | | | _____  _____ | | |    _______   | | |  _________   | | |  _________   | | |  _______     | |
//  | |   .' ___  |  | | |  |_   _|     | | ||_   _||_   _|| | |   /  ___  |  | | | |  _   _  |  | | | |_   ___  |  | | | |_   __ \    | |
//  | |  / .'   \_|  | | |    | |       | | |  | |    | |  | | |  |  (__ \_|  | | | |_/ | | \_|  | | |   | |_  \_|  | | |   | |__) |   | |
//  | |  | |         | | |    | |   _   | | |  | '    ' |  | | |   '.___`-.   | | |     | |      | | |   |  _|  _   | | |   |  __ /    | |
//  | |  \ `.___.'\  | | |   _| |__/ |  | | |   \ `--' /   | | |  |`\____) |  | | |    _| |_     | | |  _| |___/ |  | | |  _| |  \ \_  | |
//  | |   `._____.'  | | |  |________|  | | |    `.__.'    | | |  |_______.'  | | |   |_____|    | | | |_________|  | | | |____| |___| | |
//  | |              | | |              | | |              | | |              | | |              | | |              | | |              | |
//  | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
//   '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' 

float Fuzzyfication::compute_distance(float a, float b, int type_distance, int p)
{
	switch (type_distance)
	{
	case 1:
	{
		return sqrt((a - b) * (a - b));//Euklid
	}
	case 2:
	{
		return (a - b) * (a - b); //Euklid quadratic
	}
	case 3:
	{
		return fabs(a - b); //Mancheten
	}
	case 4:
	{
		return pow(pow((a - b), p), (1 / p)); //Minkowski
	}
	default:
	{
		return sqrt((a - b) * (a - b)); //Euklid
	}
	}
}

std::vector<float> Fuzzyfication::fuzzy_clustering_fcm(unsigned int attribute, unsigned int NumberOfCenters, float m, unsigned int distance_type)
{
	double temp;
	double temp1;
	double temp2;
	std::vector<std::vector<float>> membership_function;
	std::vector<float> centers;
	unsigned int intervals;//Number Of Intervals
	intervals = NumberOfCenters;
	//-------------------------------STEP 1-------------------------------------------
	//Step 1 : Let us suppose that M - dimensional N data points represented by xi (i = 1, 2, . . ., N), are to be clustered.
	centers = std::vector<float>(intervals, 0.0);
	membership_function = std::vector<std::vector<float>>(intervals, std::vector<float>(0.0));
	for (unsigned int interval = 0; interval < intervals; interval++)
	{
		membership_function[interval] = std::vector<float>(DatasetSize, 0.0);
	}
	//-------------------------------------------------------
	int t = 0;
	std::vector<bool> assigned;
	assigned = std::vector<bool>(DatasetSize);

	float current_cluster = 0;
	float last_cluster;
	float difference_coefficient; // current - last
	float min = 0.0;
	float max = 1.0;

	float part = (max - min) / intervals * 1.0f;

	for (unsigned int i = 0; i < intervals; i++)
	{
		centers[i] = min + (i * part);
	}

	difference_coefficient = EPSILON + 1.0f;

	while ((difference_coefficient >= EPSILON) && (t <= LIMIT_ITTERATION))
	{
		for (unsigned long k = 0; k < DatasetSize; k++)
		{
			assigned[k] = false;
		}
		t++;

		last_cluster = current_cluster;
		//number of clusters 
		for (unsigned int i = 0; i < intervals; i++)
		{
			for (unsigned long dataset_item = 0; dataset_item < DatasetSize; dataset_item++)
			{
				temp = 0;
				for (unsigned int interval = 0; interval < intervals; interval++)
					if (assigned[dataset_item] == false)
					{
						float distanceI = compute_distance(Pattern[dataset_item].Feature[attribute], centers[i], distance_type, 4);
						float distanceJ = compute_distance(Pattern[dataset_item].Feature[attribute], centers[interval], distance_type, 4);

						if (distanceI != 0 && distanceJ != 0)
						{
							temp += pow(distanceI / distanceJ, ((2 / (m - 1)) * 1.0f));
							membership_function[i][dataset_item] = (temp == 0) ? 1.0 : 1 / temp;
						}
						else if (distanceI == 0)
						{
							for (unsigned int l = 0; l < intervals; l++)
							{
								membership_function[l][dataset_item] = 0;
							}
							membership_function[i][dataset_item] = 1;
							assigned[dataset_item] = true;
						}
					}
			}
		}
		/////////////////////////////////////////////STEP 3////////////////////////////////////////////////
		// Computing  new febfc_step_2_locate_center_of_interval for every cluster
		for (unsigned int i = 0; i < intervals; i++)
		{
			temp1 = 0;
			temp2 = 0;
			for (unsigned long k = 0; k < DatasetSize; k++)
			{
				temp1 += pow(membership_function[i][k], m) * Pattern[k].Feature[attribute];
				temp2 += pow(membership_function[i][k], m);
			}
			centers[i] = (temp2 == 0) ? 0 : temp1 / temp2;
		}

		current_cluster = 0;
		for (unsigned int i = 0; i < intervals; i++)
			for (unsigned long k = 0; k < DatasetSize; k++)
			{
				float distanceNew = compute_distance(Pattern[k].Feature[attribute], centers[i], distance_type, 4);

				current_cluster += pow(membership_function[i][k], m) * pow(distanceNew, 2);
			}

		if (t > 1) difference_coefficient = fabs(current_cluster - last_cluster);
	}

	membership_function.clear();
	return centers;
}

//---------------------------B.--DETERMINATION OF THE INTERVAL LOCATIONS---------------------------------------
//-------------------------------STEP 1 - INITIAL NUMBER OF CLUSTERS -------------------------------------------
//-------------------------------STEP 2 - INITIAL CENTERS OF CLUSTERS -------------------------------------------
//-------------------------------STEP 3 - ASSIGN CLUSTER LABEL TO EACH ELEMENT------------------------------------
//-------------------------------STEP 4 - RECOMPUTE THE CLUSTER CENTERS ------------------------------------
//-------------------------------STEP 5 - DOES ANY CENTER CHANGE ? ------------------------------------
std::vector<float> Fuzzyfication::febfc_step_2_locate_center_of_interval(unsigned int i, std::vector<float>& Result, std::vector<unsigned long>& NewResult, unsigned long &countResult)
{
	unsigned int q; //cluster
	std::vector<unsigned int> total_patterns; //Nq is total number of patterns within the same cluster q. 
	unsigned int distance_n = 0;
	bool stop;
	unsigned int iteration;
	float center, distance;
	std::vector<float> sum;
	std::vector<float> c;


	//-------------------------------STEP 1- INITIAL NUMBER OF CLUSTERS -------------------------------------------
	iteration = 0;

	//-------------------------------STEP 2 - INITIAL CENTERS OF CLUSTERS -------------------------------------------
	c = fuzzy_clustering_fcm(i, Intervals[i], 2.0f, 3);

	fprintf(LogFile, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	fprintf(LogFile, "Current cluster centers\n");
	print_to_log_file_clusters_interval_location(i, c);

	do
	{
		sum = std::vector<float>(Intervals[i], 0.0);
		total_patterns = std::vector<unsigned int>(Intervals[i], 0.0);
		for (unsigned long k = 0; k < countResult; k++)
		{
			//-------------------------------STEP 3 - ASSIGN CLUSTER LABEL TO EACH ELEMENT------------------------------------
			distance = fabs(Result[k] - c[0]);
			for (q = 0; q < Intervals[i]; q++) // minimal compute_distance calculate
				if (distance >= fabs(Result[k] - c[q]))
				{
					distance = fabs(Result[k] - c[q]);
					distance_n = q;
				}
			sum[distance_n] += Result[k] * NewResult[k];

			total_patterns[distance_n] += NewResult[k];
		}

		stop = false;
		//-------------------------------STEP 4 - RECOMPUTE THE CLUSTER CENTERS ------------------------------------
		for (q = 0; q < Intervals[i]; q++)
		{

			center = static_cast<float>(sum[q]) / static_cast<float>(total_patterns[q]);
			if (c[q] != center)
			{
				c[q] = center;
				stop = true;
			}
			iteration++;

		}
		//-------------------------------STEP 5 - DOES ANY CENTER CHANGE ? ------------------------------------
		//Check - not same cluster centers
		for (q = 0; q < Intervals[i] - 1; q++)
		{
			if (c[q] == c[q + 1])
			{
				printf("Error: c[q]=c[q+1] - locate cluster centers");
			}
		}
	} while ((stop) && (iteration < LIMIT_ITTERATION));


	sort_ascending_order(c, Intervals[i]);

	fprintf(LogFile, "New cluster centers\n");
	print_to_log_file_clusters_interval_location(i, c);

	return c;
}

void Fuzzyfication::print_to_log_file_clusters_interval_location(unsigned i, std::vector<float> c)
{
	for (unsigned z = 0; z < Intervals[i]; z++)
		fprintf(LogFile, "Cluster center [%d] location:\t\t%f\n", z, c[z]);

	fprintf(LogFile, "\n");
}
//   .----------------. .----------------. .----------------. .----------------. .----------------. 
//  | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
//  | | _____  _____ | | |  _______     | | |     _____    | | |  _________   | | |  _________   | |
//  | ||_   _||_   _|| | | |_   __ \    | | |    |_   _|   | | | |  _   _  |  | | | |_   ___  |  | |
//  | |  | | /\ | |  | | |   | |__) |   | | |      | |     | | | |_/ | | \_|  | | |   | |_  \_|  | |
//  | |  | |/  \| |  | | |   |  __ /    | | |      | |     | | |     | |      | | |   |  _|  _   | |
//  | |  |   /\   |  | | |  _| |  \ \_  | | |     _| |_    | | |    _| |_     | | |  _| |___/ |  | |
//  | |  |__/  \__|  | | | |____| |___| | | |    |_____|   | | |   |_____|    | | | |_________|  | |
//  | |              | | |              | | |              | | |              | | |              | |
//  | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
//   '----------------' '----------------' '----------------' '----------------' '----------------' 
//   .----------------. .----------------. .----------------. .----------------.                    
//  | .--------------. | .--------------. | .--------------. | .--------------. |                   
//  | |  _________   | | |     _____    | | |   _____      | | |  _________   | |                   
//  | | |_   ___  |  | | |    |_   _|   | | |  |_   _|     | | | |_   ___  |  | |                   
//  | |   | |_  \_|  | | |      | |     | | |    | |       | | |   | |_  \_|  | |                   
//  | |   |  _|      | | |      | |     | | |    | |   _   | | |   |  _|  _   | |                   
//  | |  _| |_       | | |     _| |_    | | |   _| |__/ |  | | |  _| |___/ |  | |                   
//  | | |_____|      | | |    |_____|   | | |  |________|  | | | |_________|  | |                   
//  | |              | | |              | | |              | | |              | |                   
//  | '--------------' | '--------------' | '--------------' | '--------------' |                   
//   '----------------' '----------------' '----------------' '----------------'                    
void Fuzzyfication::print_to_file_number_of_interval_for_each_attributes(FILE* file)
{
	for (unsigned int attr = 0; attr < Attributes; attr++)
	{
		fprintf(file, "%4d ", Intervals[attr]);
	}
}

void Fuzzyfication::print_to_file_fuzzification_result_all_attributes(FILE* file)
{
	for (unsigned long dataset_value = 0; dataset_value < DatasetSize; dataset_value++)
	{
		for (unsigned int attr = 0; attr < Attributes; attr++)
		{
			for (unsigned int interval = 0; interval < Intervals[attr]; interval++)
			{
				fprintf(file, "%f ", FuzzySetOnInterval[attr][interval][dataset_value]);
			}
			fprintf(file, "\t");
		}
		fprintf(file, "\n");
	}
}

int Fuzzyfication::print_to_cm_file_results(char* filename)
{
	FILE* file;
	file = fopen(filename, "w");
	if (file == nullptr)
	{
		printf("Error FileNameOut in Fuzzy::WriteFuzzyFile()\n");
		return -1;
	}

	//print dataset size, number of input attributes,  number of output attributes
	fprintf(file, "%ld\n%d %d\n", DatasetSize, InputAttributes, OutputAttributes);

	//print number of interval for each attributes. 
	print_to_file_number_of_interval_for_each_attributes(file);
	fprintf(file, "\n\n");

	//Write fuzzification values for all attributes 
	print_to_file_fuzzification_result_all_attributes(file);
	fclose(file);
	return 1;
}

int Fuzzyfication::print_to_log_file_temporary_results()
{
	fprintf(LogFile, "\n ----------------------------------- TEMPORARY RESULTS ------------------------------------------: \n");

	fprintf(LogFile, "Dataset size:\t\t\t%ld\nNumber of Input Attributes:\t\t\t%d\nOutput Attr:\t\t\t%d\n", DatasetSize, InputAttributes, OutputAttributes);

	//print number of interval for each attributes. 
	fprintf(LogFile, "Intervals: \n");
	print_to_file_number_of_interval_for_each_attributes(LogFile);

	fprintf(LogFile, "\n");
	//Write fuzzification values for all attributes 
	print_to_file_fuzzification_result_all_attributes(LogFile);

	fprintf(LogFile, "\n -----------------------------------------------------------------------------------------------: \n");

	return 1;
}
