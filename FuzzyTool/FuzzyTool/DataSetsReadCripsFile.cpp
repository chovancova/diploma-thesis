#include <cstdio>
#include "DataSets.h"
#include <cstring>

// --------------------------   ReadCrispFile  - IRIS  -----------------------
int DataSets::read_crisp_file_iris(FILE* fp)
{
	char Label[20];
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%s",
		       &Pattern[k].Feature[0],
		       &Pattern[k].Feature[1],
		       &Pattern[k].Feature[2],
		       &Pattern[k].Feature[3],
		       Label);

		if (!strcmp(Label, "Iris-setosa"))
		{
			Pattern[k].Feature[InputAttributes] = 0.0;
		}
		if (!strcmp(Label, "Iris-versicolor"))
		{
			Pattern[k].Feature[InputAttributes] = 1.0;
		}
		if (!strcmp(Label, "Iris-virginica"))
		{
			Pattern[k].Feature[InputAttributes] = 2.0;
		}
	}
	return 1;
}

// --------------------------   ReadCrispFile  - HEART  --------------------------
int DataSets::read_crisp_file_heart(FILE* fp) 
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		       &Pattern[k].Feature[0],
		       &Pattern[k].Feature[1],
		       &Pattern[k].Feature[2],
		       &Pattern[k].Feature[3],
		       &Pattern[k].Feature[4],
		       &Pattern[k].Feature[5],
		       &Pattern[k].Feature[6],
		       &Pattern[k].Feature[7],
		       &Pattern[k].Feature[8],
		       &Pattern[k].Feature[9],
		       &Pattern[k].Feature[10],
		       &Pattern[k].Feature[11],
		       &Pattern[k].Feature[12],
		       &Pattern[k].Feature[13]);

		Pattern[k].Feature[2]--;
		Pattern[k].Feature[10]--;
		Pattern[k].Feature[13]--;

		if (Pattern[k].Feature[12] == 3) { Pattern[k].Feature[12] = 0.0; }

		if (Pattern[k].Feature[12] == 6) { Pattern[k].Feature[12] = 1.0; }

		if (Pattern[k].Feature[12] == 7) { Pattern[k].Feature[12] = 2.0; }
	}

	LingvisticAttributes[1] = 2; // Feature[2] - sex
	LingvisticAttributes[2] = 4; // Feature[3] - chest pain type (1-4)
	LingvisticAttributes[5] = 2; // Feature[6] - fasting blood sugar > 120 mg/dl
	LingvisticAttributes[6] = 3; // Feature[7] - hresting electrocardiographic results (0,1,2)
	LingvisticAttributes[8] = 2; // Feature[9] - exercise induced angina
	LingvisticAttributes[10] = 3; // Feature[11] - the slope of the peak exercise ST segment
	LingvisticAttributes[11] = 4; // Feature[12] - number of major vessels (0-3) colored by flourosopy
	LingvisticAttributes[12] = 3; // Feature[13] - thal: 0->3 (normal); 1->6 (fixed defect); 2->7 (reversable defect)
	return 1;
}


// --------------------------   ReadCrispFile - Yeast    --------------------------
int DataSets::read_crisp_file_yeast(FILE* fp) 
{
	char Label[15], DescriptionTemp[15];
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		//AATC_YEAST  0.51  0.40  0.56  0.17  0.50  0.50  0.49  0.22  CYT
		fscanf(fp, "%s  %f  %f  %f  %f  %f  %f  %f  %f  %s", DescriptionTemp,
		       &Pattern[k].Feature[0],
		       &Pattern[k].Feature[1],
		       &Pattern[k].Feature[2],
		       &Pattern[k].Feature[3],
		       &Pattern[k].Feature[4],
		       &Pattern[k].Feature[5],
		       &Pattern[k].Feature[6],
		       &Pattern[k].Feature[7],
		       Label);

		if (Pattern[k].Feature[4] == 0.50) Pattern[k].Feature[4] = 0.0;
		if (Pattern[k].Feature[5] == 0.50) Pattern[k].Feature[5] = 1.0;
		if (Pattern[k].Feature[5] == 0.83) Pattern[k].Feature[5] = 2.0;
		if (!strcmp(Label, "CYT")) Pattern[k].Feature[InputAttributes] = 0.0;
		if (!strcmp(Label, "NUC")) Pattern[k].Feature[InputAttributes] = 1.0;
		if (!strcmp(Label, "MIT")) Pattern[k].Feature[InputAttributes] = 2.0;
		if (!strcmp(Label, "ME3")) Pattern[k].Feature[InputAttributes] = 3.0;
		if (!strcmp(Label, "ME2")) Pattern[k].Feature[InputAttributes] = 4.0;
		if (!strcmp(Label, "ME1")) Pattern[k].Feature[InputAttributes] = 5.0;
		if (!strcmp(Label, "EXC")) Pattern[k].Feature[InputAttributes] = 6.0;
		if (!strcmp(Label, "VAC")) Pattern[k].Feature[InputAttributes] = 7.0;
		if (!strcmp(Label, "POX")) Pattern[k].Feature[InputAttributes] = 8.0;
		if (!strcmp(Label, "ERL")) Pattern[k].Feature[InputAttributes] = 9.0;
	}

	LingvisticAttributes[4] = 2; //  0.5   1.0
	LingvisticAttributes[5] = 3; //  0.0   0.5  0.83
	return 1;
}

// --------------------------   ReadCrispFile - WINE    ----------------------
int DataSets::read_crisp_file_wine(FILE* fp) 
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		//1,14.2,1.76,2.45,15.2,112,3.27,3.39,.34,1.97,6.75,1.05,2.85,1450
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		       &Pattern[k].Feature[13],
		       &Pattern[k].Feature[0],
		       &Pattern[k].Feature[1],
		       &Pattern[k].Feature[2],
		       &Pattern[k].Feature[3],
		       &Pattern[k].Feature[4],
		       &Pattern[k].Feature[5],
		       &Pattern[k].Feature[6],
		       &Pattern[k].Feature[7],
		       &Pattern[k].Feature[8],
		       &Pattern[k].Feature[9],
		       &Pattern[k].Feature[10],
		       &Pattern[k].Feature[11],
		       &Pattern[k].Feature[12]);

		--Pattern[k].Feature[InputAttributes]; //  InputAttributes == 13
	}
	return 1;
}


// --------------------------   ReadCrispFile  - SKIN  --------------------------
int DataSets::read_crisp_file_skin(FILE* fp) 
{
	//70	81	119	1
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f	%f	%f	%f",
		       &Pattern[k].Feature[0],
		       &Pattern[k].Feature[1],
		       &Pattern[k].Feature[2],
		       &Pattern[k].Feature[3]);

		--Pattern[k].Feature[3]; //   Normalization from 0 till OutputIntervals-1
	}
	return 1;
}

// --------------------------   ReadCrispFile  - Seeds   -----------------------
int DataSets::read_crisp_file_seeds(FILE* fp) 
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f  %f  %f  %f  %f  %f  %f  %f",
		       &Pattern[k].Feature[0],
		       &Pattern[k].Feature[1],
		       &Pattern[k].Feature[2],
		       &Pattern[k].Feature[3],
		       &Pattern[k].Feature[4],
		       &Pattern[k].Feature[5],
		       &Pattern[k].Feature[6],
		       &Pattern[k].Feature[7]);

		Pattern[k].Feature[7]--;
	}
	return 1;
}

//
//// --------------------------   ReadCrispFile  - WINERED & WINEWHITE --------------------------
//int DataSets::ReadCrispFileWineQuality(FILE* fp) 
//{
//	for (unsigned long k = 0; k < DatasetSize; k++)
//	{
//		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
//		       &Pattern[k].Feature[0],
//		       &Pattern[k].Feature[1],
//		       &Pattern[k].Feature[2],
//		       &Pattern[k].Feature[3],
//		       &Pattern[k].Feature[4],
//		       &Pattern[k].Feature[5],
//		       &Pattern[k].Feature[6],
//		       &Pattern[k].Feature[7],
//		       &Pattern[k].Feature[8],
//		       &Pattern[k].Feature[9],
//		       &Pattern[k].Feature[10],
//		       &Pattern[k].Feature[11]);
//
//		Pattern[k].Feature[11] -= 3;
//	}
//	return 1;
//}


// --------------------------   ReadCrispFile  - HEART  --------------------------
int DataSets::read_crisp_file_heart_short(FILE* fp) 
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f	%f	%f	%f	%f	%f",
			&Pattern[k].Feature[0],
			&Pattern[k].Feature[1],
			&Pattern[k].Feature[2],
			&Pattern[k].Feature[3],
			&Pattern[k].Feature[4],
			&Pattern[k].Feature[5] 
				);
		--Pattern[k].Feature[5];
	}
	return 1;
}