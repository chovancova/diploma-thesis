#include "Fuzzification.h"
#include "DataSets.h"
#include <algorithm>

using namespace Datasets;

namespace FuzzificationLibrary
{

	Fuzzification::Fuzzification(DataSets *dataToTransform)
	{
		setDataToTransform(dataToTransform);
	}

	DataSets *Fuzzification::getDataToTransform() 
	{
		return _dataToTransform;
	}

	void Fuzzification::setDataToTransform(Datasets::DataSets* value)
	{
		_dataToTransform = value;
	}

	std::vector<std::vector<std::vector<double>>> Fuzzification::getResults() 
	{
		return _results;
	}

	void Fuzzification::setResults(std::vector<std::vector<std::vector<double>>>& value)
	{
		_results = value;
	}

	std::vector<int> Fuzzification::getIntervals() const
	{
		return _intervals;
	}

	void Fuzzification::setIntervals(std::vector<int>& value)
	{
		_intervals = value;
	}

	std::vector<std::vector<double>> Fuzzification::getCenters() const
	{
		return _centers;
	}
	int Fuzzification::getCentersSize(int dimension ) const
	{
		return _centers[dimension].size();
	}


	void Fuzzification::setCenters(std::vector<std::vector<double>>& value)
	{
		_centers = value;
	}

	std::vector<std::vector<int>> Fuzzification::getClassesInInterval() const
	{
		return _classesInInterval;
	}

	void Fuzzification::setClassesInInterval(std::vector<std::vector<int>>& value)
	{
		_classesInInterval = value;
	}

	std::vector<std::vector<double>> Fuzzification::getTotalEntropy() const
	{
		return _totalEntropy;
	}

	void Fuzzification::setTotalEntropy(std::vector<std::vector<double>>& value)
	{
		_totalEntropy = value;
	}

	void Fuzzification::Initialize()
	{
		if (getDataToTransform() != nullptr)
		{
			setIntervals(std::vector<int>(getDataToTransform()->getAttributes()));
			setCenters(std::vector<std::vector<double>>(getDataToTransform()->getInputAttributes()));
			setTotalEntropy(std::vector<std::vector<double>>(getDataToTransform()->getInputAttributes()));
			setClassesInInterval(std::vector<std::vector<int>>(getDataToTransform()->getInputAttributes()));
			for (int i = 0; i < getDataToTransform()->getAttributes(); i++)
			{
				if (getDataToTransform()->getLingvisticAttribute()[i] != 0)
				{
					getIntervals()[i] = getDataToTransform()->getLingvisticAttribute()[i];
				}
				else
				{
					getIntervals()[i] = 2;
				}
			}


			setResults(std::vector<std::vector<std::vector<double>>>(getDataToTransform()->getAttributes()));
			for (int i = 0; i < getDataToTransform()->getAttributes(); i++)
			{
				getResults()[i] = std::vector<std::vector<double>>(getIntervals()[i]);

				for (int j = 0; j < getIntervals()[i]; j++)
				{
					getResults()[i][j] = std::vector<double>(getDataToTransform()->getDatasetSize());
					for (int k = 0; k < getDataToTransform()->getDatasetSize(); k++)
					{
						getResults()[i][j][k] = 0;
					}
				}
			}
		}
	}

	void Fuzzification::RunFuzzification()
	{
		Initialize();

		for (int i = 0; i < getDataToTransform()->getAttributes(); i++)
		{
			if (getDataToTransform()->getLingvisticAttribute()[i] != 0)
			{
				getIntervals()[i] = getDataToTransform()->getLingvisticAttribute()[i];
				for (int j = 0; j < getDataToTransform()->getDatasetSize(); j++)
				{
					getResults()[i][static_cast<int>(getDataToTransform()->getDataset()[j][i])][j] = 1.0;
				}
			}
		}

		for (int i = 0; i < getDataToTransform()->getAttributes(); i++)
		{
			if (getDataToTransform()->getLingvisticAttribute()[i] == 0)
			{
				RunFuzzificationInDimension(i);
			}
		}
	}

	void Fuzzification::RunFuzzificationInDimension(int dimension)
	{
		auto interval = SetInitialNumberOfIntervals(dimension);
		getTotalEntropy()[dimension] = std::vector<double>(100);
		getTotalEntropy()[dimension][1] = 99999999999;
		auto does_entropy_decrease = 0;
		bool condition;
		do
		{
			ResizeResultToNewInterval(dimension, interval);
			getCenters()[dimension] = DeterminationIntervalsLocation(dimension, getIntervals()[dimension]);
			MembershipFunctionAssignment(dimension, interval);
		 getTotalEntropy()[dimension][interval] = ComputeTotalFuzzyEntropy(dimension);
	  condition = ConditionForStopingFuzzificationInDimension(dimension, getTotalEntropy()[dimension][interval], getTotalEntropy()[dimension][interval - 1]);
			interval++;
		} while (!condition);
		LastStepInFuzzification(dimension, interval);
	}

	int Fuzzification::SetInitialNumberOfIntervals(int dimension)
	{
		return 2;
	}

	void Fuzzification::LastStepInFuzzification(int dimension, int interval)
	{
		interval = interval - 2;
		ResizeResultToNewInterval(dimension, interval);
		getCenters()[dimension] = DeterminationIntervalsLocation(dimension, interval);
		MembershipFunctionAssignment(dimension, interval);
	}

	bool Fuzzification::ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious)
	{
		return (totalEntropyI > totalEntropyIPrevious) || (totalEntropyI == 0);
	}

	void Fuzzification::MembershipFunctionAssignment(int dimension, int interval)
	{
		auto leftIndex = 0;
		auto rightIndex = getCenters()[dimension].size() - 1;
		for (int i = 0; i < getDataToTransform()->getDatasetSize(); i++)
		{
			auto x = getDataToTransform()->getDataset()[i][dimension];
			//most left membership function
			auto c1 = getCenters()[dimension][leftIndex];
			auto c2 = getCenters()[dimension][leftIndex + 1];
			double membershipValue = 0;
			if (x <= c1)
			{
				membershipValue = 1; //alternativa
			}
			else
			{
				membershipValue = (1 - std::abs(c1 - x) / std::abs(c2 - c1));
				if(membershipValue<0)
				{
					membershipValue = 0; 
				}
			}

			getResults()[dimension][leftIndex][i] = membershipValue;

			//most right membership function

			auto c4 = getCenters()[dimension][rightIndex];
			auto c3 = getCenters()[dimension][rightIndex - 1];
			if (x <= c4)
			{
				membershipValue = ( 1 - std::abs(c4 - x) / std::abs(c4 - c3));
				if (membershipValue<0)
				{
					membershipValue = 0;
				}
			}
			else if (x > c4)
			{
				membershipValue = 1; //ALTERNATIVA
			}
			getResults()[dimension][rightIndex][i] = membershipValue;
			//internal intervals
			for (int j = 1; j < getCentersSize(dimension)-1; j++)
			{
				c2 = getCenters()[dimension][j - 1];
				c3 = getCenters()[dimension][j];
				c4 = getCenters()[dimension][j + 1];

				if (x <= c3)
				{
					membershipValue =  1 - std::abs(c3 - x) / std::abs(c3 - c2);
					if (membershipValue<0)
					{
						membershipValue = 0;
					}
				}
				else
				{
					membershipValue =  1 - std::abs(c3 - x) / std::abs(c4 - c3);
					if (membershipValue<0)
					{
						membershipValue = 0;
					}
				}
				getResults()[dimension][j][i] = membershipValue;
			}
		}
	}

	void Fuzzification::ResizeResultToNewInterval(int dimension, int interval) const
	{
		getIntervals()[dimension] = interval;

		getResults()[dimension].erase(getResults()[dimension].begin());

		getResults()[dimension] = std::vector<std::vector<double>>(getIntervals()[dimension]);

		for (int i = 0; i < getIntervals()[dimension]; i++)
		{
			getResults()[dimension][i] = std::vector<double>(getDataToTransform()->getDatasetSize());
			for (int j = 0; j < getDataToTransform()->getDatasetSize(); j++)
			{
				getResults()[dimension][i][j] = 0.0;
			}
		}
	}

	}
