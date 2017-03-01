#include <cstdio>
#include "DataSets.h"
#include <cstring>

// --------------------------   ReadCrispFile  - IRIS  -----------------------
int DataSets::ReadCrispFileIris(FILE* fp) const
{
	char Label[20];
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%s",
		       &Features[k].Dimension[0],
		       &Features[k].Dimension[1],
		       &Features[k].Dimension[2],
		       &Features[k].Dimension[3],
		       Label);

		if (!strcmp(Label, "Iris-setosa"))
		{
			Features[k].Dimension[InputAttr] = 0.0;
		}
		if (!strcmp(Label, "Iris-versicolor"))
		{
			Features[k].Dimension[InputAttr] = 1.0;
		}
		if (!strcmp(Label, "Iris-virginica"))
		{
			Features[k].Dimension[InputAttr] = 2.0;
		}
	}
	return 1;
}

// --------------------------   ReadCrispFile  - HEART  --------------------------
int DataSets::ReadCrispFileHeart(FILE* fp) const
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		       &Features[k].Dimension[0],
		       &Features[k].Dimension[1],
		       &Features[k].Dimension[2],
		       &Features[k].Dimension[3],
		       &Features[k].Dimension[4],
		       &Features[k].Dimension[5],
		       &Features[k].Dimension[6],
		       &Features[k].Dimension[7],
		       &Features[k].Dimension[8],
		       &Features[k].Dimension[9],
		       &Features[k].Dimension[10],
		       &Features[k].Dimension[11],
		       &Features[k].Dimension[12],
		       &Features[k].Dimension[13]);

		Features[k].Dimension[2]--;
		Features[k].Dimension[10]--;
		Features[k].Dimension[13]--;

		if (Features[k].Dimension[12] == 3) { Features[k].Dimension[12] = 0.0; }

		if (Features[k].Dimension[12] == 6) { Features[k].Dimension[12] = 1.0; }

		if (Features[k].Dimension[12] == 7) { Features[k].Dimension[12] = 2.0; }
	}

	LingvisticAttr[1] = 2; // Dimension[2] - sex
	LingvisticAttr[2] = 4; // Dimension[3] - chest pain type (1-4)
	LingvisticAttr[5] = 2; // Dimension[6] - fasting blood sugar > 120 mg/dl
	LingvisticAttr[6] = 3; // Dimension[7] - hresting electrocardiographic results (0,1,2)
	LingvisticAttr[8] = 2; // Dimension[9] - exercise induced angina
	LingvisticAttr[10] = 3; // Dimension[11] - the slope of the peak exercise ST segment
	LingvisticAttr[11] = 4; // Dimension[12] - number of major vessels (0-3) colored by flourosopy
	LingvisticAttr[12] = 3; // Dimension[13] - thal: 0->3 (normal); 1->6 (fixed defect); 2->7 (reversable defect)
	return 1;
}


// --------------------------   ReadCrispFile - Yeast    --------------------------
int DataSets::ReadCrispFileYeast(FILE* fp) const
{
	char Label[15], DescriptionTemp[15];
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		//AATC_YEAST  0.51  0.40  0.56  0.17  0.50  0.50  0.49  0.22  CYT
		fscanf(fp, "%s  %f  %f  %f  %f  %f  %f  %f  %f  %s", DescriptionTemp,
		       &Features[k].Dimension[0],
		       &Features[k].Dimension[1],
		       &Features[k].Dimension[2],
		       &Features[k].Dimension[3],
		       &Features[k].Dimension[4],
		       &Features[k].Dimension[5],
		       &Features[k].Dimension[6],
		       &Features[k].Dimension[7],
		       Label);

		if (Features[k].Dimension[4] == 0.50) Features[k].Dimension[4] = 0.0;
		if (Features[k].Dimension[5] == 0.50) Features[k].Dimension[5] = 1.0;
		if (Features[k].Dimension[5] == 0.83) Features[k].Dimension[5] = 2.0;
		if (!strcmp(Label, "CYT")) Features[k].Dimension[InputAttr] = 0.0;
		if (!strcmp(Label, "NUC")) Features[k].Dimension[InputAttr] = 1.0;
		if (!strcmp(Label, "MIT")) Features[k].Dimension[InputAttr] = 2.0;
		if (!strcmp(Label, "ME3")) Features[k].Dimension[InputAttr] = 3.0;
		if (!strcmp(Label, "ME2")) Features[k].Dimension[InputAttr] = 4.0;
		if (!strcmp(Label, "ME1")) Features[k].Dimension[InputAttr] = 5.0;
		if (!strcmp(Label, "EXC")) Features[k].Dimension[InputAttr] = 6.0;
		if (!strcmp(Label, "VAC")) Features[k].Dimension[InputAttr] = 7.0;
		if (!strcmp(Label, "POX")) Features[k].Dimension[InputAttr] = 8.0;
		if (!strcmp(Label, "ERL")) Features[k].Dimension[InputAttr] = 9.0;
	}

	LingvisticAttr[4] = 2; //  0.5   1.0
	LingvisticAttr[5] = 3; //  0.0   0.5  0.83
	return 1;
}

// --------------------------   ReadCrispFile - WINE    ----------------------
int DataSets::ReadCrispFileWine(FILE* fp) const
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		//1,14.2,1.76,2.45,15.2,112,3.27,3.39,.34,1.97,6.75,1.05,2.85,1450
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		       &Features[k].Dimension[13],
		       &Features[k].Dimension[0],
		       &Features[k].Dimension[1],
		       &Features[k].Dimension[2],
		       &Features[k].Dimension[3],
		       &Features[k].Dimension[4],
		       &Features[k].Dimension[5],
		       &Features[k].Dimension[6],
		       &Features[k].Dimension[7],
		       &Features[k].Dimension[8],
		       &Features[k].Dimension[9],
		       &Features[k].Dimension[10],
		       &Features[k].Dimension[11],
		       &Features[k].Dimension[12]);

		--Features[k].Dimension[InputAttr]; //  InputAttr == 13
	}
	return 1;
}


// --------------------------   ReadCrispFile  - SKIN  --------------------------
int DataSets::ReadCrispFileSkin(FILE* fp) const
{
	//70	81	119	1
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f	%f	%f	%f",
		       &Features[k].Dimension[0],
		       &Features[k].Dimension[1],
		       &Features[k].Dimension[2],
		       &Features[k].Dimension[3]);

		--Features[k].Dimension[3]; //   Normalization from 0 till OutputIntervals-1
	}
	return 1;
}

// --------------------------   ReadCrispFile  - Seeds   -----------------------
int DataSets::ReadCrispFileSeeds(FILE* fp) const
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f",
		       &Features[k].Dimension[0],
		       &Features[k].Dimension[1],
		       &Features[k].Dimension[2],
		       &Features[k].Dimension[3],
		       &Features[k].Dimension[4],
		       &Features[k].Dimension[5],
		       &Features[k].Dimension[6],
		       &Features[k].Dimension[7]);

		Features[k].Dimension[7]--;
	}
	return 1;
}
//
//// --------------------------   ReadCrispFile  - WINERED & WINEWHITE --------------------------
//int DataSets::ReadCrispFileWineQuality(FILE* fp) const
//{
//	for (unsigned long k = 0; k < DatasetSize; k++)
//	{
//		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
//		       &Features[k].Dimension[0],
//		       &Features[k].Dimension[1],
//		       &Features[k].Dimension[2],
//		       &Features[k].Dimension[3],
//		       &Features[k].Dimension[4],
//		       &Features[k].Dimension[5],
//		       &Features[k].Dimension[6],
//		       &Features[k].Dimension[7],
//		       &Features[k].Dimension[8],
//		       &Features[k].Dimension[9],
//		       &Features[k].Dimension[10],
//		       &Features[k].Dimension[11]);
//
//		Features[k].Dimension[11] -= 3;
//	}
//	return 1;
//}
