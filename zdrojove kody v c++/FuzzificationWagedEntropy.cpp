#include "FuzzificationWagedEntropy.h"
#include "DataSets.h"

using namespace Datasets;

namespace FuzzificationLibrary
{
	FuzzificationWagedEntropy::FuzzificationWagedEntropy(DataSets* dataToTransform) : FuzzificationEntropy(dataToTransform)
	{
	}

	double FuzzificationWagedEntropy::ComputeTotalFuzzyEntropy(int dimension)
	{
		double totalEntropy = 0;
		auto countIntervalsInDimension = getIntervals()[dimension];
		auto countM = std::vector<int>(countIntervalsInDimension);
		for (int i = 0; i < countIntervalsInDimension; i++)
		{
			countM[i] = 0;
		}
		auto mu = std::vector<std::vector<std::vector<double>>>(countIntervalsInDimension);
		auto sumMu = std::vector<std::vector<double>>(countIntervalsInDimension);
		for (int i = 0; i < countIntervalsInDimension; i++)
		{
			mu[i] = std::vector<std::vector<double>>(countIntervalsInDimension);
			sumMu[i] = std::vector<double>(countIntervalsInDimension);
			for (int j = 0; j < countIntervalsInDimension; j++)
			{
				mu[i][j] = std::vector<double>(getDataToTransform()->getOutputIntervals());
				sumMu[i][j] = 0;
				for (int k = 0; k < getDataToTransform()->getOutputIntervals(); k++)
				{
					mu[i][j][k] = 0;
				}
			}
		}
		double max = 0;
		auto classM = 0;
		double temp = 0;
		for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
		{
			max = getResults()[dimension][0][i];
			for (int j = 0; j < countIntervalsInDimension; j++)
			{
				temp = getResults()[dimension][j][i];
				if (max <= temp)
				{
					classM = j;
					max = temp;
				}
			}
			countM[classM]++;
			for (int j = 0; j < countIntervalsInDimension; j++)
			{
				for (int k = 0; k < getDataToTransform()->getOutputIntervals(); k++) //getOutputIntervals()???
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

		for (int j = 0; j < countIntervalsInDimension; j++)
		{
			for (int k = 0; k < countIntervalsInDimension; k++)
			{
				for (int l = 0; l < getDataToTransform()->getOutputIntervals(); l++)
				{
					sumMu[j][k] += mu[j][k][l];
				}
			}
		}

		double matchDegreeDj = 0;
		for (int i = 0; i < countIntervalsInDimension; i++)
		{
			double newEntropy = 0;
			for (int j = 0; j < countIntervalsInDimension; j++)
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
			totalEntropy += newEntropy * countM[i] / getDataToTransform()->getDatasetSize();
		}

		getClassesInInterval()[dimension] = countM;
		return totalEntropy;
	}
}
