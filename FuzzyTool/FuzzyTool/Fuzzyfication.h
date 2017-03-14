#ifndef _FUZZY_H_
#define _FUZZY_H_
#define LIMIT_ITTERATION  100
#include "DataSets.h"
#include <complex.h>

class Fuzzyfication : public DataSets
{
public:
	FILE* LogFile;

	///<summary>Result- polygon - [X][Y][Z]
	///		X-axis is number of attributes
	///		Y-axis is number of intervals , 
	///		Z-axis is size of dataset.</summary>
	float*** FuzzySetOnInterval;
	unsigned int* Intervals;
	unsigned int IdDataset;

	/**
	* \brief Initialize datasets, fuzzification,
	* Set the initial number of Interval to 2.
	* \param id_dataset Number of dataset.
	*/
	explicit Fuzzyfication(unsigned int id_dataset);
	~Fuzzyfication();
	bool determination_number_of_intervals(unsigned long* new_result, unsigned long count_result, int& does_entropy_decrease, float* result, float* cluster, float old_entropy, float& new_entropy, unsigned i);
	void RunFuzzification();
	void InitializeDataset() const;

	//Writter
	int WriteFuzzyficationResult(char* filename) const;
	int WriteFuzzyficationLogs() const;
private:
	void assign_membership_function(unsigned int i, float* c) const;

	//work with features, results and so on. 
	void create_features();
	void modify_features(unsigned int attr, int interval_new_value) const;
	void delete_features() const;


	//Ascending Result
	unsigned long create_ascending_result(unsigned int i, float* Result, unsigned long* NewResult) const;
	static void sort_ascending_order(float* PointsOfCut, unsigned int numberOfCutPoints);
	static void sort_ascending_order(float* Result, unsigned long* NewResult, unsigned long numberOfElements);

	//K-means clusters
	float* center(unsigned int i, float* Result, unsigned long* NewResult, unsigned long countResult) const;
	float* center_fuzzy(unsigned int attribute, unsigned int number_clusters, float m, unsigned int distance_type) const;
	float compute_distance(float a, float b, int distType, int p) const;

	//Entropy
	float entropy_calculate(unsigned int i);
};

#endif
