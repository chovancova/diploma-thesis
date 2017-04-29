#pragma once

#include "Fuzzification.h"
#include <vector>
#include <cmath>


	class FuzzificationEntropy : public FuzzificationLibrary::Fuzzification
	{
	public:
		virtual ~FuzzificationEntropy()
		{
		}

		FuzzificationEntropy(DataSets* dataToTransform);
		std::vector<double> DeterminationIntervalsLocation(int dimension, int intervals) override;
	protected:
		double ComputeTotalFuzzyEntropy(int dimension) override;

	private:
		std::vector<double> CMeansClustering(int numberOfIntervals, int dimension);

		static bool DoesAnyCenterChange(std::vector<double>& result, std::vector<double>& centers);

		std::vector<double> RecomputeClusterCenters(int numberOfIntervals, std::vector<std::vector<double>>& centers);

		std::vector<std::vector<double>> AssignClusterLabelToEachInterval(int numberOfIntervals, int dimension, std::vector<double>& c);

		std::vector<double> InitializeUniformCenters(int dimension, int q);

		double ComputeEuclidDistance(double a, double b);
	};
