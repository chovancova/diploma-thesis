#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../TempFunctions.h"
#include "DataSets.h"

//  ---------------------------------------------------------------------------
DataSets::DataSets(unsigned int numDB)
{
	unsigned int     NoA, NoIA, NoOA, NoOI;
	unsigned long    TS;
	switch (numDB)
	{
	case _HEART:     strcpy(nameDB, "heart");
		TS = 270;   NoIA = 13;  NoOA = 1; NoOI = 2; break;
	case _IRIS:      strcpy(nameDB, "iris");
		TS = 150;   NoIA = 4;  NoOA = 1; NoOI = 3; break;
	default: { printf("Uncorrect DataBase's numbers in main()\n"); getchar(); }
	}
	NoA = NoIA + NoOA;
	R = (instance*) new instance[TS];
	if (!R) MyError("Bad allocation R in DataSets()");
	for (unsigned long k = 0; k < TS; k++)
	{
		R[k].A = (float*) new float[NoA];
		if (!R[k].A) MyError("Bad allocation R[k].A in DataSets()");
	}
	nonNumericAttributes = newUnInt(NoA, 0, "nonNumericAttributes in DataSets()");
	nonNumericAttributes[NoIA] = NoOI;
	TotalSets = TS;
	NumberOfAttributes = NoA;
	NumberOfInputAttributes = NoIA;
	NumberOfOutputAttributes = NoOA;
	NumberOfOutputIntervals = NoOI;
}

// ------------------        ~DataSets()   -------------------------------
DataSets::~DataSets()
{
	for (unsigned long k = 0; k < TotalSets; k++)
	{
			delete[] R[k].A;
	}
	delete[] R;
	delete[] nonNumericAttributes;
}
// -------------------------    Initial Error   ---------------------------
float DataSets::InitialError(unsigned int numDB)
{
	unsigned long* classNoOI, maxClass;
	unsigned int jb;

	classNoOI = newUnLong(NumberOfOutputIntervals, 0l, " classNoOI from InitialErrorDS");
	for (unsigned long k = 0; k < TotalSets; k++)
	{
		jb = R[k].A[NumberOfInputAttributes];
		classNoOI[jb]++;
	}
	maxClass = classNoOI[0];
	for (jb = 0; jb < NumberOfOutputIntervals; jb++)
	{
		printf("classNoOI[jb=%d]=%d\n", jb, classNoOI[jb]);
		if (classNoOI[jb] > maxClass)  maxClass = classNoOI[jb];
	}
	return(1 - (float)maxClass*1.0f / TotalSets);
}

// ------------------        ReadDataSets   -------------------------------
int DataSets::ReadDataSets(unsigned int numDB)
{
	char FileNameDB[99];
	FILE *fp;
	strcpy(FileNameDB, PATHinCrisp);
	strcat(FileNameDB, nameDB);
	strcat(FileNameDB, ".data");

	printf("reading from file >>> %s\n", FileNameDB);

	fp = fopen(FileNameDB, "r");
	if (fp == NULL) MyError("Error reading file from DataSets::ReadDataSets\n");
	switch (numDB)
	{
	case _IRIS: ReadCrispFileIris(fp);  break;
	case _HEART: ReadCrispFileHeart(fp); break;
	};
	fclose(fp);
	return 1;
}  // --------------------------   WriteCrispFile    --------------------------
int DataSets::WriteCrispFile(void)
{
	char FileName[99];
	FILE *fp;
	strcpy(FileName, PATHoutCrisp); strcat(FileName, nameDB); strcat(FileName, ".crisp");
	fp = fopen(FileName, "w");
	if (fp == NULL) { printf("Error FileName in WriteCrispFile()"); getchar(); return 0; };

	for (unsigned int i = 0; i < NumberOfAttributes; i++)
		fprintf(fp, "%d ", nonNumericAttributes[i]);
	fprintf(fp, "\n");

	for (unsigned long k = 0; k < TotalSets; k++)
	{
		fprintf(fp, "(k=%ld)  ", k);
		for (unsigned int i = 0; i < NumberOfAttributes; i++)
			fprintf(fp, "%f ", R[k].A[i]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "End of Crisp File");
	fclose(fp);
	return 1;
}
// --------------------------   ReadCrispFile  - IRIS  -----------------------
int DataSets::ReadCrispFileIris(FILE* fp)
{
	char Opis[20];
	for (unsigned long k = 0; k < TotalSets; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%s", &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], Opis);
		if (!strcmp(Opis, "Iris-setosa")) R[k].A[NumberOfInputAttributes] = 0.0;
		if (!strcmp(Opis, "Iris-versicolor")) R[k].A[NumberOfInputAttributes] = 1.0;
		if (!strcmp(Opis, "Iris-virginica")) R[k].A[NumberOfInputAttributes] = 2.0;
	}
	return 1;
}

// --------------------------   ReadCrispFile  - HEART  --------------------------
int DataSets::ReadCrispFileHeart(FILE* fp)
{
	for (unsigned long k = 0; k < TotalSets; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			&R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
			&R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9],
			&R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13]);
		R[k].A[2]--;    R[k].A[10]--;    R[k].A[13]--;
		if (R[k].A[12] == 3) R[k].A[12] = 0.0;
		if (R[k].A[12] == 6) R[k].A[12] = 1.0;
		if (R[k].A[12] == 7) R[k].A[12] = 2.0;
	}
	nonNumericAttributes[1] = 2; // A[2] - sex
	nonNumericAttributes[2] = 4; // A[3] - chest pain type (1-4)
	nonNumericAttributes[5] = 2; // A[6] - fasting blood sugar > 120 mg/dl
	nonNumericAttributes[6] = 3; // A[7] - hresting electrocardiographic results (0,1,2)
	nonNumericAttributes[8] = 2; // A[9] - exercise induced angina
	nonNumericAttributes[10] = 3; // A[11] - the slope of the peak exercise ST segment
	nonNumericAttributes[11] = 4; // A[12] - number of major vessels (0-3) colored by flourosopy
	nonNumericAttributes[12] = 3; // A[13] - thal: 0->3 (normal); 1->6 (fixed defect); 2->7 (reversable defect)
	return 1;
}


