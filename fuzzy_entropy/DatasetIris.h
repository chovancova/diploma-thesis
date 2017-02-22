#pragma once
#include "Dataset.h"

class DatasetIris :
	public Dataset
{
public:
	DatasetIris();
	~DatasetIris();

	int load(const std::string& filename) override;
};

