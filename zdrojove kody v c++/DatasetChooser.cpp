#include "DatasetChooser.h"
#include "DataSets.h"
#include "DatasetIris.h"

Datasets::DataSets* Datasets::DatasetChooser::ReadDatasetFromFile(DatasetType type, int datasetSize, int inputAttributes, int outputIntervals, const std::wstring& filename)
	{
		DataSets* dataset = nullptr;
		switch (type)
		{
		case Datasets::DatasetType::Iris:
			dataset = new DatasetIris(datasetSize, inputAttributes, outputIntervals, filename);
			break;
		default:
			return nullptr;
		}

		dataset->InitializeDataset();
		dataset->NormalizeDataset();
		return dataset;
	}

Datasets::DataSets* Datasets::DatasetChooser::ReadDatasetFromFile(Datasets::DatasetType type, const std::wstring& filename)
	{
		DataSets* dataset = nullptr;
		switch (type)
		{
		case Datasets::DatasetType::Iris:
			dataset = new DatasetIris(filename);
			break;
		default:
			return nullptr;
		}

		dataset->InitializeDataset();
		dataset->NormalizeDataset();
		return dataset;
	}

