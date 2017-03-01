#ifndef _FUZZY_H_
#define _FUZZY_H_
#define LIMIT_ITTERATION  100
#include "DataSets.h"
#include <complex.h>

class Fuzzyfication : public DataSets
{
public:
	FILE* LoggerFile;

	///<summary>Result- polygon - [X][Y][Z]
	///		X-axis is number of attributes
	///		Y-axis is number of intervals , 
	///		Z-axis is size of dataset.</summary>
	float*** FuzzySetOnInterval;
	unsigned int* Intervals;
	unsigned int IdDataset;


public:
	/**
	* \brief Initialize datasets, fuzzification,
	* Set the initial number of Interval to 2.
	* \param id_dataset Number of dataset.
	*/
	explicit Fuzzyfication(unsigned int id_dataset);
	~Fuzzyfication();

	void RunFuzzification();
	void InitializeDataset() const;

	//Writter
	int WriteFuzzyficationResult(char* filename) const;
	int WriteFuzzyficationLogs() const;
private:
	void AssignMembershipFunction(unsigned int i, float* c) const;

	//work with features, results and so on. 
	void CreateFeatures();
	void ModifyFeatures(unsigned int attr, int interval_new_value) const;
	void DeleteFeatures() const;


	//Ascending Result
	unsigned long CreateAscendingResult(unsigned int i, float* Result, unsigned long* NewResult) const;
	static void SortAscendingOrder(float* PointsOfCut, unsigned int numberOfCutPoints);
	static void SortAscendingOrder(float* Result, unsigned long* NewResult, unsigned long numberOfElements);

	//K-means clusters
	float* Center(unsigned int i, float* Result, unsigned long* NewResult, unsigned long countResult) const;
	float* CenterFuzzy(unsigned int attribute, unsigned int number_clusters, float m, unsigned int distance_type) const;
	float ComputeDistance(float a, float b, int distType, int p) const;

	//Entropy
	float EntropyCalculate(unsigned int i);
};

#endif
