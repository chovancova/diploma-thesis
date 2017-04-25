#ifndef _DATA_SETS_H_
#define _DATA_SETS_H_
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#define _HEART 1
#define _IRIS  2
#define _SEEDS 3
#define _SKIN  4       
#define _WINE  5
#define _YEAST			6
#define _HEART_SHORT      7

// -------------------------------------------------------------
#define PATH_INPUT_FOLDER   "..\\DataSets\\data\\"
#define PATH_OUTPUT_FOLDER  "..\\DataSets\\out\\"

struct feature
{
	feature() : Feature() {}
	feature(size_t size) : Feature(size) {}
	std::vector<float> Feature;
};

class DataSets
{
public:
	unsigned long DatasetSize;
	unsigned int Attributes;
	unsigned int InputAttributes;
	unsigned int OutputAttributes;
	unsigned int OutputIntervals;
	std::vector<unsigned int> LingvisticAttributes;
	std::vector<feature> Pattern;
	char NameDataset[50];

private:
	std::vector<float> min_;
	std::vector<float> max_;
	int get_dataset_file(unsigned datasetId, FILE* file, bool& returns) ;
	int read_crisp_file_iris(FILE* fp) ;
	int read_crisp_file_heart(FILE* fp) ;
	int read_crisp_file_yeast(FILE* fp) ;
	int read_crisp_file_wine(FILE* fp) ;
	int ReadCrispFileWineQuality(FILE* fp) ;*/
	int read_crisp_file_skin(FILE* fp) ;
	int read_crisp_file_seeds(FILE* fp) ;	
	int read_crisp_file_heart_short(FILE* fp) ;	
	void initialize_attributes(unsigned id_dataset, unsigned& attributes, unsigned& input_attributes, unsigned& output_attributes, unsigned& output_intervals, unsigned long& size_dataset);

public:
	DataSets(unsigned int id_dataset);
	~DataSets();
	int ReadDataSets(unsigned int id_dataset);
	int WriteCrispFile() ;
	unsigned long GetDatasetSize() 
	{
		return DatasetSize;
	}
	float InitialError() ;
	void Normalization();
};

#endif
