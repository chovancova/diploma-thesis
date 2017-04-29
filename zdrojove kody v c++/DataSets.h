#pragma once

#include <string>
#include <vector>
#include <cmath>


namespace Datasets
{
	class DataSets
	{
	private:
		int _datasetSize = 0;
		int _attributes = 0;
		int _inputAttributes = 0;
		int _outputAttributes = 0;
		int _outputIntervals = 0;
		std::wstring _filename;
		std::vector<std::vector<double>> _dataset;
		std::vector<int> _lingvisticAttribute;
		double _initialError = 0;

	protected:
		DataSets(int datasetSize, int inputAttributes, int outputIntervals, const std::wstring &filename);

	public:
		int getDatasetSize() const;
		void setDatasetSize(const int &value);
		int getAttributes() const;
		void setAttributes(const int &value);
		int getInputAttributes() const;
		void setInputAttributes(const int &value);
		int getOutputAttributes() const;
		void setOutputAttributes(const int &value);
		int getOutputIntervals() const;
		void setOutputIntervals(const int &value);
		std::wstring getFilename() const;
		void setFilename(const std::wstring &value);
		std::vector<std::vector<double>> getDataset() const;
		void setDataset(const std::vector<std::vector<double>>& value);
		std::vector<int> getLingvisticAttribute() const;
		void setLingvisticAttribute(const std::vector<int>& value);
		double getInitialError() const;
		void setInitialError(const double &value);
		void ClearDataset();
		virtual int InitializeDataset() = 0;
		void NormalizeDataset();

		double ComputeInitialError();
		void ShrinkDataset(int size);
	};

	class RandomExtensions final
	{
	public:
		template<typename T>
		static void Shuffle(std::vector<T> &array_Renamed);
	};
}
