#ifndef _DATA_SETS_H_
#define _DATA_SETS_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _IRIS 18
#define _HEART 15

// -------------------------------------------------------------
#define PATHinCrisp    "..\\project_fuzzy\\Data\\"
#define PATHoutCrisp   "..\\project_fuzzy\\Data\\"

typedef struct { float* A; } instance;

class DataSets
{
public:
	unsigned long   TotalSets;
	unsigned int    NumberOfAttributes;
	unsigned int    NumberOfInputAttributes;
	unsigned int    NumberOfOutputAttributes;
	unsigned int    NumberOfOutputIntervals;
	unsigned int*   nonNumericAttributes;
	instance*       R;
	char            nameDB[50];
public:
	DataSets(unsigned int numDB);
	~DataSets();
	int    ReadDataSets(unsigned int numDB);
	int    WriteCrispFile(void);
	int    ReadCrispFileIris(FILE* fp);
	int	  ReadCrispFileHeart(FILE* fp);
	char*         ReturnNameDB(void) { return(nameDB); }
	unsigned long ReturnTotalSets(void) { return(TotalSets); }
	unsigned int  ReturnNoA(void) { return(NumberOfAttributes); }
	float         InitialError(unsigned int numDB);
};

#endif
