#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "DataSets.h"
#include <iostream>
#include "TempFunctions.h"
#include <ctime>

DataSets::DataSets(unsigned int id_dataset)
{
	unsigned int attributes;
	unsigned int inputAttributes = 0;
	unsigned int outputAttributes = 0;
	unsigned int outputIntervals = 0;
	unsigned long size_dataset = 0; //Number of Instances

	switch (id_dataset)
	{
	case _HEART: strcpy(NameDataset, "heart");
		size_dataset = 270;
		inputAttributes = 13;
		outputAttributes = 1;
		outputIntervals = 2;
		break;
	case _IRIS: strcpy(NameDataset, "iris");
		size_dataset = 150;
		inputAttributes = 4;
		outputAttributes = 1;
		outputIntervals = 3;
		break;
	case _YEAST: strcpy(NameDataset, "yeast");
		size_dataset = 1484;
		inputAttributes = 8;
		outputAttributes = 1;
		outputIntervals = 10;
		break;
	case _SKIN: strcpy(NameDataset, "skin");
		size_dataset = 245057;
		inputAttributes = 3;
		outputAttributes = 1;
		outputIntervals = 2;
		break;
	case _SEEDS: strcpy(NameDataset, "seeds");
		size_dataset = 210;
		inputAttributes = 7;
		outputAttributes = 1;
		outputIntervals = 3;
		break;
	case _WINE: strcpy(NameDataset, "wine");
		size_dataset = 178;
		inputAttributes = 13;
		outputAttributes = 1;
		outputIntervals = 3;
		break;
	case _WINERED: strcpy(NameDataset, "winequalityred");
		size_dataset = 1599;
		inputAttributes = 11;
		outputAttributes = 1;
		outputIntervals = 6;
		break;
	case _WINEWHITE: strcpy(NameDataset, "winequalitywhite");
		size_dataset = 4898;
		inputAttributes = 11;
		outputAttributes = 1;
		outputIntervals = 7;
		break;
	default:
		{
			std::cout << "Dataset not found.";
			break;
		}
	}
	attributes = inputAttributes + outputAttributes;
	DatasetSize = size_dataset;
	Attributes = attributes;
	InputAttr = inputAttributes;
	OutputAttr = outputAttributes;
	OutputIntervals = outputIntervals;

	//alocation of Items polygon
	Items = static_cast<instance*>(new instance[DatasetSize]);
	if (!Items)
	{
		MyError("Bad allocation of Items in DataSets().");
	}

	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		Items[k].Dimension = static_cast<float*>(new float[Attributes]);
		if (!Items[k].Dimension)
		{
			MyError("Bad allocation Items[k].Dimension in DataSets()");
		}
	}

	LingvisticAttr = newUnInt(Attributes, 0, "LingvisticAttr in DataSets()");
	LingvisticAttr[inputAttributes] = outputIntervals;
	Min = newFloat(InputAttr, 0, "Min in DataSets()");
	Max = newFloat(InputAttr, 0, "Max in DataSets()");
}

DataSets::~DataSets()
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		delete[] Items[k].Dimension;
	}
	delete[] Items;
	delete[] LingvisticAttr;
	delete[] Min;
	delete[] Max;
}

int DataSets::get_dataset_file(unsigned datasetId, FILE* file, bool& returns) const
{
	returns = false;
	switch (datasetId)
	{
	case _IRIS: ReadCrispFileIris(file);
		return 1;
	case _HEART: ReadCrispFileHeart(file);
		return 1;
	case _SEEDS: ReadCrispFileSeeds(file);
		return 1;
	case _SKIN: ReadCrispFileSkin(file);
		return 1;
	case _WINE: ReadCrispFileWine(file);
		return 1;
	case _WINERED: ReadCrispFileWineQuality(file);
		return 1;
	case _WINEWHITE: ReadCrispFileWineQuality(file);
		return 1;
	case _YEAST: ReadCrispFileYeast(file);
		return 1;
	default:
		{
			fclose(file);
			std::cout << "Dataset not found.";
			returns = true;
			return 0;
		}
	};
}

int DataSets::ReadDataSets(unsigned int datasetId) const
{
	FILE* file = nullptr;
	try
	{
		char file_name[99];
		strcpy(file_name, PATH_INPUT_FOLDER);
		strcat(file_name, NameDataset);
		strcat(file_name, ".data");

		printf("Reading dataset from file - %s\n", file_name);

		file = fopen(file_name, "r");
		if (file == nullptr)
		{
			std::cout << "Dataset file was not found. \n";
			return -1;
		}
		bool returns;
		int value1 = get_dataset_file(datasetId, file, returns);
		if (returns) return value1;
		fclose(file);
		return 1;
	}
	catch (int e)
	{
		if (file != nullptr) fclose(file);
		std::cout << "An exception occurred. Exception Nr. " << e << '\n';
		return -1;
	}
}

int DataSets::WriteCrispFile(void) const
{
	char FileName[200];

	FILE* fp;
	strcpy(FileName, PATH_OUTPUT_FOLDER);

	time_t rawtime;
	std::tm* timeinfo;
	char buffer[20];
	time(&rawtime);
	timeinfo = std::localtime(&rawtime);
	std::strftime(buffer, 20, "%Y-%m-%d-%H-%M-%S", timeinfo);
	std::puts(buffer);
	
	strcat(FileName, buffer);
	strcat(FileName, "_");
	strcat(FileName, NameDataset);
	strcat(FileName, ".crisp.txt");
	fp = fopen(FileName, "w");
	if (fp == nullptr)
	{
		printf("Error FileName in WriteCrispFile()");
		getchar();
		return 0;
	};

	for (unsigned int i = 0; i < Attributes; i++)
		fprintf(fp, "%d ", LingvisticAttr[i]);
	fprintf(fp, "\n");

	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fprintf(fp, "k=%ld  ", k);
		for (unsigned int i = 0; i < Attributes; i++)
			fprintf(fp, "%f ", Items[k].Dimension[i]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "End of Crisp File");
	fclose(fp);
	return 1;
}

float DataSets::InitialError(unsigned int id_dataset) const
{
	try
	{
		unsigned long *classNoOI, maxClass;
		unsigned int jb;

		classNoOI = newUnLong(OutputIntervals, 0l, " classNoOI from InitialErrorDS");
		for (unsigned long k = 0; k < DatasetSize; k++)
		{
			jb = Items[k].Dimension[InputAttr];
			classNoOI[jb]++;
		}
		maxClass = classNoOI[0];
		for (jb = 0; jb < OutputIntervals; jb++)
		{
			printf("classNoOI[jb=%d]=%d\n", jb, classNoOI[jb]);
			if (classNoOI[jb] > maxClass) maxClass = classNoOI[jb];
		}
		return (1 - float(maxClass) * 1.0f / DatasetSize);
	}
	catch (int e)
	{
		std::cout << "An exception occurred. Exception Nr. " << e << '\n';
	}
	return 0.0f;
}

void DataSets::Normalization() const
{
	for (unsigned int i = 0; i < InputAttr; i++)
	{
		if (LingvisticAttr[i] == 0)
		{
			Min[i] = Items[0].Dimension[i];
			Max[i] = Items[0].Dimension[i];
			for (unsigned long k = 1; k < DatasetSize; k++)
			{
				if (Items[k].Dimension[i] < Min[i]) Min[i] = Items[k].Dimension[i];
				if (Items[k].Dimension[i] > Max[i]) Max[i] = Items[k].Dimension[i];
			}
			for (unsigned long k = 0; k < DatasetSize; k++)
				Items[k].Dimension[i] = (Items[k].Dimension[i] - Min[i]) / (Max[i] - Min[i]);
		}
	}
}
