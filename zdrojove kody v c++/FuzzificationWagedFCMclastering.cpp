#include "FuzzificationWagedFCMclastering.h"
#include "DataSets.h"
#include <ctime>

	FuzzificationLibrary::FuzzificationWagedFcMclastering::FuzzificationWagedFcMclastering(DataSets* dataToTransform) : FuzzificationWagedEntropy(dataToTransform)
	{
		/* initialize random seed: */
		srand(time(NULL));
	}

	std::vector<double> FuzzificationLibrary::FuzzificationWagedFcMclastering::DeterminationIntervalsLocation(int dimension, int intervals)
	{
		return FCMeansClustering(intervals, dimension, 2); //m=2 default
	}

	std::vector<double> FuzzificationLibrary::FuzzificationWagedFcMclastering::FCMeansClustering(int numberOfIntervals, int dimension, int m)
	{
		//Krok 1.Náhodne sa inicializuje kluster hodnoty príslušnosti, μij.
		getCenters()[dimension] = InitializeRandomCenters(dimension, numberOfIntervals);

		for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
		{
			for (int j = 0; j < numberOfIntervals; j++)
			{
				getResults()[dimension][j][i] = getCenters()[dimension][j];
			}
		}

		do
		{
			// Krok 2. Vypočítanie centier klastra c_j =  sum{ i = 1}^ D \mu_{ ij}^ m * x_i   deleno sum{ i = 1}^ D \mu_{ ij}^ m
			auto mu = std::vector<double>(numberOfIntervals);
			double sum1 = 0;
			double sum2 = 0;
			for (int j = 0; j < numberOfIntervals; j++)
			{
				for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
				{
					sum1 += std::pow(getResults()[dimension][j][i], m) * getDataToTransform()->getDataset()[i][dimension];
					sum2 += std::pow(getResults()[dimension][j][i], m);
				}
				mu[j] = sum1 / sum2;
			}

			// Krok 3.Aktualizácia μij podla nasledujúceho vztahu μij = 1 / ( suma (od k = 1 do N) (absolutna hodnota (xi-cj) / absol(xi-ck)) a to cele na 2/(m1) )
			auto sum3 = std::vector<double>(numberOfIntervals);
			for (int j = 0; j < numberOfIntervals; j++)
			{
				for (int k = 0; k < numberOfIntervals; k++)
				{
					for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
					{
						sum3[j] += std::abs(getDataToTransform()->getDataset()[i][dimension] - getCenters()[dimension][j]) / std::abs(getDataToTransform()->getDataset()[i][dimension] - getCenters()[dimension][k]);
					}
				}
			}
			for (int j = 0; j < numberOfIntervals; j++)
			{
				for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
				{
					if (sum3[j] != 0)
					{
						getResults()[dimension][j][i] = std::pow(1 / sum3[j], 2 / (m - 1));
					}
				}
			}
			// Krok 4.Vypocítanie účelovej funkcie Jm.
			// Jm = suma (od i=1 do Datovych bodov) suma (od j = 1 do N pocet klastrov) μij ^ m absolutan hodnota (xi - cj)^2
			auto Jm = std::vector<double>(m);
			for (int k = 0; k < m; k++)
			{
				for (int j = 0; j < numberOfIntervals; j++)
				{
					for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
					{
						Jm[k] += std::pow(getResults()[dimension][j][i], m) * std::pow(std::abs(getDataToTransform()->getDataset()[i][dimension] - getCenters()[dimension][j]), 2);
					}
				}
			}

			//Krok 5. Opakovanie krokov 2-4 až pokým Jm sa zlepší o menej než stanovená minimálna
			// prahová hodnota alebo po uplynutí urcitého maximálneho poctu iterácií.
		}
		while (false);

		return getCenters()[dimension];
	}

	std::vector<double> FuzzificationLibrary::FuzzificationWagedFcMclastering::InitializeRandomCenters(int dimension, int q)
	{
		auto c = std::vector<double>(q);
		auto indexData = std::vector<int>(q);
		auto notSame = false;

		for (int i = 0; i < q; i++)
		{
			do
			{
				indexData[i] = rand() % getDataToTransform()->getDatasetSize();;
				c[i] = getDataToTransform()->getDataset()[indexData[i]][dimension];
				notSame = false;
				for (int j = 0; j < i; j++)
				{
					if (std::abs(c[i] - c[j]) < 0.00000001)
					{
						notSame = true;
					}
				}
			}
			while (notSame);
		}

		std::sort(c.begin(), c.end());
		return c;
	}

