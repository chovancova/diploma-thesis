#pragma once

#include "FuzzificationEntropy.h"
#include <vector>
#include <cmath>

namespace Datasets
{
	class DataSets;
}

using namespace Datasets;

namespace FuzzificationLibrary
{
	class FuzzificationWagedEntropy : public FuzzificationEntropy
	{
	public:
		FuzzificationWagedEntropy(DataSets* dataToTransform);
	protected:
		double ComputeTotalFuzzyEntropy(int dimension) override;
	};
}
