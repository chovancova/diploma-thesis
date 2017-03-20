#ifndef _DATA_SETS_H_
#define _DATA_SETS_H_
#include <stdlib.h>
#include <stdio.h>
//id of datasets
#define _HEART 1
#define _IRIS  2
#define _SEEDS 3
#define _SKIN  4       
#define _WINE  5
//#define _WINERED     6
//#define _WINEWHITE   7  
#define _YEAST       6
#define _HEART_SHORT      7

// -------------------------------------------------------------
#define PATH_INPUT_FOLDER   "..\\DataSets\\data\\"
#define PATH_OUTPUT_FOLDER  "..\\DataSets\\out\\"

typedef struct
{
	float* Dimension;
} instance;

class DataSets
{
public:
	///<summary>Number of items of datasets. (Total Set)</summary>  
	unsigned long DatasetSize;
	///<summary>Number of attributes of dataset.</summary>
	unsigned int Attributes;
	///<summary>Number of input attributes of dataset.</summary>
	unsigned int InputAttributes;
	///<summary>Number of output attributes of dataset.</summary>
	unsigned int OutputAttributes;
	///<summary>Number of output intervals of dataset.</summary>
	unsigned int OutputIntervals;
	///<summary>Number of non numeric attributes. Attributes types - Ordered, Binary, Nominal. </summary>
	unsigned int* LingvisticAttributes;
	///<summary>Features  -X-axis is size of dataset , Y-axis is number of attributes, </summary>
	instance* Features;
	///<summary>NameDataset of dataset.</summary>
	char NameDataset[50];

private:
	float* min_;
	float* max_;
	int get_dataset_file(unsigned datasetId, FILE* file, bool& returns) const;
	///<summary>Read iris dataset from file.</summary>
	int read_crisp_file_iris(FILE* fp) const;
	///<summary>Read heart dataset from file.</summary>
	int read_crisp_file_heart(FILE* fp) const;
	///<summary>Read yeast dataset from file.</summary>
	int read_crisp_file_yeast(FILE* fp) const;
	///<summary>Read wine dataset from file.</summary>
	int read_crisp_file_wine(FILE* fp) const;
	/*///<summary>Read wine quality dataset from file.</summary>
	int ReadCrispFileWineQuality(FILE* fp) const;*/
	///<summary>Read skin dataset from file.</summary>
	int read_crisp_file_skin(FILE* fp) const;
	///<summary>Read seed dataset from file.</summary>
	int read_crisp_file_seeds(FILE* fp) const;	
	int read_crisp_file_heart_short(FILE* fp) const;	
	void initialize_attributes(unsigned id_dataset, unsigned& attributes, unsigned& input_attributes, unsigned& output_attributes, unsigned& output_intervals, unsigned long& size_dataset);

public:
	/// <summary>  
	/// Initialize dataset - number of attributes, .
	/// <para> Id of dataset.</para>
	/// </summary> 
	DataSets(unsigned int id_dataset);
	///<summary>Destructor of dataset. </summary>
	~DataSets();
	/// <summary>  
	/// Read dataset from file.
	/// <para> Id of dataset.</para>
	/// <returns>Return 0 - dataset not found, 1 - successfull, -1 - error.</returns>
	/// </summary> 
	int ReadDataSets(unsigned int id_dataset) const;
	/// <summary>Check of initial data from dataset. 
	/// Write information about number of attributes, 
	/// and values of loaded dataset to file.   
	/// </summary>
	int WriteCrispFile() const;

	///<summary> <return>Return number of values in dataset.</return> </summary>
	unsigned long GetDatasetSize() const
	{
		return DatasetSize;
	}

	///<summary> <return>Return initial error of dataset.</return> </summary>
	float InitialError() const;
	void Normalization() const;
};

#endif
