#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "DataSets.h"
#include <iostream>
#include "TempFunctions.h"
#include <ctime>

void DataSets::initialize_attributes(unsigned id_dataset, unsigned& attributes, unsigned& input_attributes, unsigned& output_attributes, unsigned& output_intervals, unsigned long& size_dataset)
{
	input_attributes = 0;
	output_attributes = 0;
	output_intervals = 0;
	size_dataset = 0;

	switch (id_dataset)
	{
	case _HEART: strcpy(NameDataset, "heart");
		size_dataset = 270;
		input_attributes = 13;
		output_attributes = 1;
		output_intervals = 2;
		break;
	case _IRIS: strcpy(NameDataset, "iris");
		size_dataset = 150;
		input_attributes = 4;
		output_attributes = 1;
		output_intervals = 3;
		break;
	case _YEAST: strcpy(NameDataset, "yeast");
		size_dataset = 1484;
		input_attributes = 8;
		output_attributes = 1;
		output_intervals = 10;
		break;
	case _SKIN: strcpy(NameDataset, "skin");
		size_dataset = 245057;
		input_attributes = 3;
		output_attributes = 1;
		output_intervals = 2;
		break;
	case _SEEDS: strcpy(NameDataset, "seeds");
		size_dataset = 210;
		input_attributes = 7;
		output_attributes = 1;
		output_intervals = 3;
		break;
	case _WINE: strcpy(NameDataset, "wine");
		size_dataset = 178;
		input_attributes = 13;
		output_attributes = 1;
		output_intervals = 3;
		break;
		/*case _WINERED: strcpy(NameDataset, "winequalityred");
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
		break;*/
	default:
		{
			std::cout << "Dataset not found.";
			break;
		}
	}
}

DataSets::DataSets(unsigned int id_dataset)
{
	unsigned attributes;
	unsigned input_attributes;
	unsigned output_attributes;
	unsigned output_intervals;
	unsigned long size_dataset;
	initialize_attributes(id_dataset, attributes, input_attributes, output_attributes, output_intervals, size_dataset);
	attributes = input_attributes + output_attributes;
	DatasetSize = size_dataset;
	Attributes = attributes;
	InputAttributes = input_attributes;
	OutputAttributes = output_attributes;
	OutputIntervals = output_intervals;

	//alocation of Features polygon
	Features = static_cast<instance*>(new instance[DatasetSize]);
	if (!Features)
	{
		MyError("Bad allocation of Features in DataSets().");
	}

	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		Features[k].Dimension = static_cast<float*>(new float[Attributes]);
		if (!Features[k].Dimension)
		{
			MyError("Bad allocation Features[k].Dimension in DataSets()");
		}
	}

	LingvisticAttributes = newUnInt(Attributes, 0, "LingvisticAttributes in DataSets()");
	LingvisticAttributes[input_attributes] = output_intervals;
	min_ = newFloat(InputAttributes, 0, "min_ in DataSets()");
	max_ = newFloat(InputAttributes, 0, "max_ in DataSets()");
}

DataSets::~DataSets()
{
	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		delete[] Features[k].Dimension;
	}
	delete[] Features;
	delete[] LingvisticAttributes;
	delete[] min_;
	delete[] max_;
}

int DataSets::get_dataset_file(unsigned id_dataset, FILE* file, bool& returns) const
{
	returns = false;
	switch (id_dataset)
	{
	case _IRIS: read_crisp_file_iris(file);
		return 1;
	case _HEART: read_crisp_file_heart(file);
		return 1;
	case _SEEDS: read_crisp_file_seeds(file);
		return 1;
	case _SKIN: read_crisp_file_skin(file);
		return 1;
	case _WINE: read_crisp_file_wine(file);
		return 1;
		/*case _WINERED: ReadCrispFileWineQuality(file);
			return 1;
		case _WINEWHITE: ReadCrispFileWineQuality(file);
			return 1;*/
	case _YEAST: read_crisp_file_yeast(file);
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
	char file_name[200];

	FILE* fp;
	strcpy(file_name, PATH_OUTPUT_FOLDER);

	time_t rawtime;
	std::tm* timeinfo;
	char buffer[20];
	time(&rawtime);
	timeinfo = std::localtime(&rawtime);
	std::strftime(buffer, 20, "%Y-%m-%d-%H-%M-%S", timeinfo);
	std::puts(buffer);
	strcat(file_name, NameDataset);
	strcat(file_name, "_");
	strcat(file_name, buffer);

	strcat(file_name, ".crisp.txt");
	fp = fopen(file_name, "a+");
	if (fp == nullptr)
	{
		printf("Error FileName in WriteCrispFile()");
		getchar();
		return 0;
	};

	for (unsigned int i = 0; i < Attributes; i++)
		fprintf(fp, "%d ", LingvisticAttributes[i]);
	fprintf(fp, "\n");

	for (unsigned long k = 0; k < DatasetSize; k++)
	{
		fprintf(fp, "k=%ld  ", k);
		for (unsigned int i = 0; i < Attributes; i++)
			fprintf(fp, "%f ", Features[k].Dimension[i]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "End of Crisp File");
	fclose(fp);
	return 1;
}

float DataSets::InitialError() const
{
	try
	{
		unsigned long *class_number_output_intervals, maxClass;
		unsigned int jb;

		class_number_output_intervals = newUnLong(OutputIntervals, 0l, " classNoOI from InitialErrorDS");
		for (unsigned long x = 0; x < DatasetSize; x++)
		{
			jb = Features[x].Dimension[InputAttributes];
			class_number_output_intervals[jb]++;
		}
		maxClass = class_number_output_intervals[0];
		for (jb = 0; jb < OutputIntervals; jb++)
		{
			printf("classNoOI[jb=%d]=%d\n", jb, class_number_output_intervals[jb]);
			if (class_number_output_intervals[jb] > maxClass) maxClass = class_number_output_intervals[jb];
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
	for (unsigned int i = 0; i < InputAttributes; i++)
	{
		if (LingvisticAttributes[i] == 0)
		{
			min_[i] = Features[0].Dimension[i];
			max_[i] = Features[0].Dimension[i];
			for (unsigned long k = 1; k < DatasetSize; k++)
			{
				if (Features[k].Dimension[i] < min_[i]) min_[i] = Features[k].Dimension[i];
				if (Features[k].Dimension[i] > max_[i]) max_[i] = Features[k].Dimension[i];
			}
			for (unsigned long k = 0; k < DatasetSize; k++)
				Features[k].Dimension[i] = (Features[k].Dimension[i] - min_[i]) / (max_[i] - min_[i]);
		}
	}
}
