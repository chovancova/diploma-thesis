#pragma once

#include "FuzzificationWagedEntropy.h"
#include <vector>
#include <algorithm>
#include <cmath>

namespace Datasets
{
	class DataSets;
}

using namespace Datasets;

namespace FuzzificationLibrary
{
	class FuzzificationWagedFcMclastering : public FuzzificationWagedEntropy
	{
	public:
		virtual ~FuzzificationWagedFcMclastering()
		{
		}

		FuzzificationWagedFcMclastering(DataSets* dataToTransform);

		std::vector<double> DeterminationIntervalsLocation(int dimension, int intervals) override;

	private:
		std::vector<double> FCMeansClustering(int numberOfIntervals, int dimension, int m = 2);

		std::vector<double> InitializeRandomCenters(int dimension, int q);
	};
}
