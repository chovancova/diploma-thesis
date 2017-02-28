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
			&Items[k].Dimension[0],
			&Items[k].Dimension[1],
			&Items[k].Dimension[2],
			&Items[k].Dimension[3],
			Label);

		if (!strcmp(Label, "Iris-setosa"))
		{
			Items[k].Dimension[InputAttr] = 0.0;
		}
		if (!strcmp(Label, "Iris-versicolor"))
		{
			Items[k].Dimension[InputAttr] = 1.0;
		}
		if (!strcmp(Label, "Iris-virginica"))
		{
			Items[k].Dimension[InputAttr] = 2.0;
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
			&Items[k].Dimension[0],
			&Items[k].Dimension[1],
			&Items[k].Dimension[2],
			&Items[k].Dimension[3],
			&Items[k].Dimension[4],
			&Items[k].Dimension[5],
			&Items[k].Dimension[6],
			&Items[k].Dimension[7],
			&Items[k].Dimension[8],
			&Items[k].Dimension[9],
			&Items[k].Dimension[10],
			&Items[k].Dimension[11],
			&Items[k].Dimension[12],
			&Items[k].Dimension[13]);

		Items[k].Dimension[2]--;
		Items[k].Dimension[10]--;
		Items[k].Dimension[13]--;

		if (Items[k].Dimension[12] == 3) { Items[k].Dimension[12] = 0.0; }

		if (Items[k].Dimension[12] == 6) { Items[k].Dimension[12] = 1.0; }

		if (Items[k].Dimension[12] == 7) { Items[k].Dimension[12] = 2.0; }

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
			&Items[k].Dimension[0],
			&Items[k].Dimension[1],
			&Items[k].Dimension[2],
			&Items[k].Dimension[3],
			&Items[k].Dimension[4],
			&Items[k].Dimension[5],
			&Items[k].Dimension[6],
			&Items[k].Dimension[7],
			Label);

		if (Items[k].Dimension[4] == 0.50) Items[k].Dimension[4] = 0.0;
		if (Items[k].Dimension[5] == 0.50) Items[k].Dimension[5] = 1.0;
		if (Items[k].Dimension[5] == 0.83) Items[k].Dimension[5] = 2.0;
		if (!strcmp(Label, "CYT")) Items[k].Dimension[InputAttr] = 0.0;
		if (!strcmp(Label, "NUC")) Items[k].Dimension[InputAttr] = 1.0;
		if (!strcmp(Label, "MIT")) Items[k].Dimension[InputAttr] = 2.0;
		if (!strcmp(Label, "ME3")) Items[k].Dimension[InputAttr] = 3.0;
		if (!strcmp(Label, "ME2")) Items[k].Dimension[InputAttr] = 4.0;
		if (!strcmp(Label, "ME1")) Items[k].Dimension[InputAttr] = 5.0;
		if (!strcmp(Label, "EXC")) Items[k].Dimension[InputAttr] = 6.0;
		if (!strcmp(Label, "VAC")) Items[k].Dimension[InputAttr] = 7.0;
		if (!strcmp(Label, "POX")) Items[k].Dimension[InputAttr] = 8.0;
		if (!strcmp(Label, "ERL")) Items[k].Dimension[InputAttr] = 9.0;
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
			&Items[k].Dimension[13],
			&Items[k].Dimension[0],
			&Items[k].Dimension[1],
			&Items[k].Dimension[2],
			&Items[k].Dimension[3],
			&Items[k].Dimension[4],
			&Items[k].Dimension[5],
			&Items[k].Dimension[6],
			&Items[k].Dimension[7],
			&Items[k].Dimension[8],
			&Items[k].Dimension[9],
			&Items[k].Dimension[10],
			&Items[k].Dimension[11],
			&Items[k].Dimension[12]);

		--Items[k].Dimension[InputAttr]; //  InputAttr == 13
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
			&Items[k].Dimension[0],
			&Items[k].Dimension[1],
			&Items[k].Dimension[2],
			&Items[k].Dimension[3]);

		--Items[k].Dimension[3]; //   Normalization from 0 till OutputIntervals-1
	}
	return 1;
}

// --------------------------   ReadCrispFile  - Seeds   -----------------------
int DataSets::ReadCrispFileSeeds(FILE* fp) const
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f",
			&Items[k].Dimension[0],
			&Items[k].Dimension[1],
			&Items[k].Dimension[2],
			&Items[k].Dimension[3],
			&Items[k].Dimension[4],
			&Items[k].Dimension[5],
			&Items[k].Dimension[6],
			&Items[k].Dimension[7]);

		Items[k].Dimension[7]--;
	}
	return 1;
}

// --------------------------   ReadCrispFile  - WINERED & WINEWHITE --------------------------
int DataSets::ReadCrispFileWineQuality(FILE* fp) const
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			&Items[k].Dimension[0],
			&Items[k].Dimension[1],
			&Items[k].Dimension[2],
			&Items[k].Dimension[3],
			&Items[k].Dimension[4],
			&Items[k].Dimension[5],
			&Items[k].Dimension[6],
			&Items[k].Dimension[7],
			&Items[k].Dimension[8],
			&Items[k].Dimension[9],
			&Items[k].Dimension[10],
			&Items[k].Dimension[11]);

		Items[k].Dimension[11] -= 3;
	}
	return 1;
}
