#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "DataSets.h"


namespace FuzzificationLibrary
{
	class Fuzzification
	{
	private:
		Datasets::DataSets* _dataToTransform;
		std::vector<std::vector<std::vector<double>>> _results;
		std::vector<int> _intervals;
		std::vector<std::vector<double>> _centers;
		std::vector<std::vector<int>> _classesInInterval;
		std::vector<std::vector<double>> _totalEntropy;

	protected:
		Fuzzification(Datasets::DataSets* dataToTransform);
	public:
		Datasets::DataSets* getDataToTransform() ;
		void setDataToTransform(Datasets::DataSets* value);
		std::vector<std::vector<std::vector<double>>> getResults() ;
		void setResults(std::vector<std::vector<std::vector<double>>>& value);
		std::vector<int> getIntervals() const;
		void setIntervals(std::vector<int>& value);
		std::vector<std::vector<double>> getCenters() const;
		int getCentersSize(int dimension) const;
		void setCenters(std::vector<std::vector<double>>& value);
		std::vector<std::vector<int>> getClassesInInterval() const;
		void setClassesInInterval(std::vector<std::vector<int>>& value);
		std::vector<std::vector<double>> getTotalEntropy() const;
		void setTotalEntropy(std::vector<std::vector<double>>& value);

		void Initialize();


		virtual void RunFuzzification();

		virtual void RunFuzzificationInDimension(int dimension);
		virtual int SetInitialNumberOfIntervals(int dimension);
		virtual void LastStepInFuzzification(int dimension, int interval);
	protected:
		virtual double ComputeTotalFuzzyEntropy(int dimension) = 0;
		virtual bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious);
	public:
		virtual std::vector<double> DeterminationIntervalsLocation(int dimension, int intervals) = 0;
		virtual void MembershipFunctionAssignment(int dimension, int interval);


		void ResizeResultToNewInterval(int dimension, int interval) const;

		virtual void WriteToFile(const std::wstring& filename = L"results.txt");

		virtual void WriteResultsToFile(const std::wstring& filename = L"results.txt");
	};
}
