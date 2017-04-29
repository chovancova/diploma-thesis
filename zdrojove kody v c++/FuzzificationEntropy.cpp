#include "FuzzificationEntropy.h"
#include "DataSets.h"

using namespace Datasets;

namespace FuzzificationLibrary
{
	FuzzificationEntropy::FuzzificationEntropy(DataSets* dataToTransform) : Fuzzification(dataToTransform)
	{
	}

	std::vector<double> FuzzificationEntropy::DeterminationIntervalsLocation(int dimension, int intervals)
	{
		return CMeansClustering(intervals, dimension);
	}

	double FuzzificationEntropy::ComputeTotalFuzzyEntropy(int dimension)
	{
		double totalEntropy = 0;
		auto intervals = getIntervals()[dimension];

		auto classM = 0;

		auto countM = std::vector<int>(intervals);
		for (int i = 0; i < intervals; i++)
		{
			countM[i] = 0;
		}
		auto mu = std::vector<std::vector<std::vector<double>>>(intervals);
		auto sumMu = std::vector<std::vector<double>>(intervals);
		for (int i = 0; i < intervals; i++)
		{
			mu[i] = std::vector<std::vector<double>>(intervals);
			sumMu[i] = std::vector<double>(intervals);
			for (int j = 0; j < intervals; j++)
			{
				mu[i][j] = std::vector<double>(getDataToTransform()->getOutputIntervals());
				sumMu[i][j] = 0;
				for (int k = 0; k < getDataToTransform()->getOutputIntervals(); k++)
				{
					mu[i][j][k] = 0;
				}
			}
		}
		for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
		{
			auto max = getResults()[dimension][0][i];
			for (int j = 0; j < intervals; j++)
			{
				auto temp = getResults()[dimension][j][i];
				if (max <= temp)
				{
					classM = j;
					max = temp;
				}
			}
			countM[classM]++;
			for (int j = 0; j < intervals; j++)
			{
				for (int k = 0; k < getDataToTransform()->getOutputIntervals(); k++)
				{
					mu[classM][j][k] += getResults()[dimension][j][i] * getResults()[getDataToTransform()->getInputAttributes()][k][i];
				}
			}
		}
		double sum = 0;
		for (int i = 0; i < countM.size(); i++)
		{
			sum += countM[i];
		}

		for (int j = 0; j < intervals; j++)
		{
			for (int k = 0; k < intervals; k++)
			{
				for (int l = 0; l < getDataToTransform()->getOutputIntervals(); l++)
				{
					sumMu[j][k] += mu[j][k][l];
				}
			}
		}


		double matchDegreeDj = 0;
		for (int i = 0; i < intervals; i++)
		{
			double newEntropy = 0;
			for (int j = 0; j < intervals; j++)
			{
				for (int k = 0; k < getDataToTransform()->getOutputIntervals(); k++)
				{
					matchDegreeDj = sumMu[i][j] < 0.000001 ? 0 : mu[i][j][k] / sumMu[i][j]; //proti deleniu nulov
					if (std::abs(matchDegreeDj) > 0.0000001)
					{
						if (std::abs(mu[i][j][k]) > 0.00001)
						{
							newEntropy -= matchDegreeDj * log2(matchDegreeDj);
						}
					}
				}
			}
			totalEntropy += newEntropy;
		}
		getClassesInInterval()[dimension] = countM;
		return totalEntropy;
	}

	std::vector<double> FuzzificationEntropy::CMeansClustering(int numberOfIntervals, int dimension)
	{
		auto count = 0;
		std::vector<std::vector<double>> centersForDataset;
		bool doesAnyCenterChange;
		auto result = std::vector<double>(numberOfIntervals);
		auto centers = InitializeUniformCenters(dimension, numberOfIntervals);
		do
		{
			centersForDataset = AssignClusterLabelToEachInterval(numberOfIntervals, dimension, centers);
			result = RecomputeClusterCenters(numberOfIntervals, centersForDataset);
			doesAnyCenterChange = DoesAnyCenterChange(result, centers);
			if (!doesAnyCenterChange)
			{
				break;
			}
			count++;
			centers = result;
		}
		while (count < 500);
		return result;
	}

	bool FuzzificationEntropy::DoesAnyCenterChange(std::vector<double>& result, std::vector<double>& centers)
	{
		for (int i = 0; i < result.size(); i++)
		{
			if (result[i] != centers[i])
			{
				return true;
			}
		}

		return false;
	}

	std::vector<double> FuzzificationEntropy::RecomputeClusterCenters(int numberOfIntervals, std::vector<std::vector<double>>& centers)
	{
		auto result = std::vector<double>(numberOfIntervals);
		for (int i = 0; i < numberOfIntervals; i++)
		{
			double Nq = 0;
			double sumNq = 0;
			for (int j = 0; j < getDataToTransform()->getDatasetSize(); j++)
			{
				if (std::abs(centers[j][0] - i) < 0.000001)
				{
					Nq++;
					sumNq += centers[j][1];
				}
			}
			result[i] = sumNq / Nq;
		}
		return result;
	}

	std::vector<std::vector<double>> FuzzificationEntropy::AssignClusterLabelToEachInterval(int numberOfIntervals, int dimension, std::vector<double>& c)
	{
		std::vector<std::vector<double>> centers;
		auto closest = 999999999.0;
		auto distance = 0.0;
		auto closestIndex = 0;
		auto data = 0.0;
		centers = std::vector<std::vector<double>>(getDataToTransform()->getDatasetSize());

		for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
		{
			data = getDataToTransform()->getDataset()[i][dimension];
			centers[i] = std::vector<double>(6);
			closest = 999999999.0;
			closestIndex = 0;

			for (int j = 0; j < numberOfIntervals; j++)
			{
				distance = ComputeEuclidDistance(data, c[j]);
				if (distance < closest)
				{
					closest = distance;
					closestIndex = j;
				}
			}
			centers[i][0] = closestIndex;
			centers[i][1] = data;
		}
		return centers;
	}

	std::vector<double> FuzzificationEntropy::InitializeUniformCenters(int dimension, int q)
	{
		auto c = std::vector<double>(q);
		auto indexData = std::vector<int>(q);
		auto notSame = false;
		double temp;
		for (int i = 1; i <= q; i++)
		{
			c[i - 1] = static_cast<double>(i - 1) / (q - 1);
		}

		return c;
	}

	double FuzzificationEntropy::ComputeEuclidDistance(double a, double b)
	{
		return std::sqrt((a - b) * (a - b));
	}
}
