#pragma once

#include "DataSets.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "stringhelper.h"



	class DatasetIris : public Datasets::DataSets
	{
	public:
		DatasetIris(int datasetSize = 150, int inputAttributes = 4, int outputIntervals = 3, const std::wstring& filename = L"iris.data");

		DatasetIris(const std::wstring& filename, int datasetSize = 150, int inputAttributes = 4, int outputIntervals = 3);

		int InitializeDataset() override;
	};
