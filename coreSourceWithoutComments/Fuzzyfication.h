#ifndef _FUZZY_H_
#define _FUZZY_H_
#define LIMIT_ITTERATION  1000
#include "DataSets.h"
#include <vector>

class Fuzzyfication : public DataSets
{
public:
	explicit Fuzzyfication(unsigned int id_dataset);
	~Fuzzyfication();
	
	void run_fuzzification_febfc();
	void RunFuzzification(unsigned int method=1);
private:
	FILE* LogFile;
	std::vector<std::vector<std::vector<float>>> FuzzySetOnInterval;
	std::vector<unsigned int> Intervals;
	unsigned int IdDataset;
	void initialize_dataset();
	void initialize_filename(char (&filename_fuzzy)[200]);
	void initialize_variables_for_entropy_result(unsigned long& count_result, std::vector<unsigned long>& new_result, std::vector<float>& result, int& does_entropy_decrease, float& new_entropy, unsigned dimension);
	//work with features, results and so on. 
	void febfc_step_1_create_features();
	void modify_features(unsigned int attr, int interval_new_value) ;
	void delete_features() ;
	void set_lingvistic_attributes(unsigned dimension) ;
	//K-means clusters
	std::vector<float> febfc_step_2_locate_center_of_interval(unsigned int i, std::vector<float> &result, std::vector<unsigned long> &new_result, unsigned long& countResult) ;
	std::vector<float> fuzzy_clustering_fcm(unsigned attribute, unsigned NumberOfCenters, float m, unsigned distance_type) ;
	void print_to_log_file_clusters_interval_location(unsigned i, std::vector<float> c) ;
	float compute_distance(float a, float b, int distType, int p) ;
	//Ascending Result
	unsigned long create_ascending_result(unsigned int i, std::vector<float> &result, std::vector<unsigned long>& new_result) ;
	static void sort_ascending_order(std::vector<float> &PointsOfCut, unsigned int &numberOfCutPoints);
	static void sort_ascending_order(std::vector<float> &Result, std::vector<unsigned long> &NewResult, unsigned long& numberOfElements);
	void febfc_step_3_assign_membership_function(unsigned int i, std::vector<float> &c) ;
		void match_degree_calculation(unsigned attr, unsigned class_m, std::vector<std::vector<std::vector<float>>> &mu, unsigned long &data_item) ;
	void set_scj_on_universal_set_x(unsigned attr, unsigned& class_m, float& max, unsigned long &data_item) ;
	void compute_wage_degree_calculation(unsigned attr, std::vector<std::vector<float>> &sum_mu, std::vector<std::vector<std::vector<float>>> &mu) ;
	void compute_total_fuzzy_entropy(unsigned attr, float& total_fuzzy_entropy, std::vector<unsigned long> count_m, std::vector<std::vector<float>> &sum_mu, std::vector<std::vector<std::vector<float>>> &mu) ;
	void dealocate_pointers_entropy(unsigned attr, std::vector<unsigned long> &count_m, std::vector<std::vector<std::vector<float>>> &mu, std::vector<std::vector<float>> &sum_mu) ;
	void compute_mu_function(unsigned attr, std::vector<unsigned long>& count_m, std::vector<std::vector<std::vector<float>>> &mu) ;
		//Entropy
	float febfc_step_4_compute_total_fuzzy_entropy(unsigned int i) ;
	bool febfc_step_5_does_entropy_decrese(unsigned long count_result, int& does_entropy_decrease, float old_entropy, float new_entropy, unsigned dimension) ;
	void print_to_log_file_new_entropy(float new_entropy, unsigned dimension) ;
	static void print_to_console_dimension(unsigned dimension);
	void print_to_log_file_classes(unsigned attr, std::vector<unsigned long> count_m) ;
	void print_to_file_number_of_interval_for_each_attributes(FILE* file) ;
	void print_to_file_fuzzification_result_all_attributes(FILE* file) ;
	//Writter
	int print_to_cm_file_results(char* filename) ;
	int print_to_log_file_temporary_results() ;
};

#endif
