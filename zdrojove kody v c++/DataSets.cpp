#include "DataSets.h"
#include <ctime>


namespace Datasets
{
	DataSets::DataSets(int datasetSize, int inputAttributes, int outputIntervals, const std::wstring& filename)
	{
		srand(time(NULL));
		setDatasetSize(datasetSize);
		setAttributes(inputAttributes + 1);
		setInputAttributes(inputAttributes);
		setOutputAttributes(1);
		setOutputIntervals(outputIntervals);
		setFilename(filename);
		setInitialError(-1);
		setDataset(std::vector<std::vector<double>>(datasetSize));
		for (int i = 0; i < datasetSize; i++)
		{
			getDataset()[i] = std::vector<double>(getAttributes());
		}

		setLingvisticAttribute(std::vector<int>(getAttributes()));
		for (int i = 0; i < getLingvisticAttribute().size(); i++)
		{
			getLingvisticAttribute()[i] = 0;
		}
		getLingvisticAttribute()[inputAttributes] = outputIntervals;
	}

	int DataSets::getDatasetSize() const
	{
		return _datasetSize;
	}

	void DataSets::setDatasetSize(const int& value)
	{
		_datasetSize = value;
	}

	int DataSets::getAttributes() const
	{
		return _attributes;
	}

	void DataSets::setAttributes(const int& value)
	{
		_attributes = value;
	}

	int DataSets::getInputAttributes() const
	{
		return _inputAttributes;
	}

	void DataSets::setInputAttributes(const int& value)
	{
		_inputAttributes = value;
	}

	int DataSets::getOutputAttributes() const
	{
		return _outputAttributes;
	}

	void DataSets::setOutputAttributes(const int& value)
	{
		_outputAttributes = value;
	}

	int DataSets::getOutputIntervals() const
	{
		return _outputIntervals;
	}

	void DataSets::setOutputIntervals(const int& value)
	{
		_outputIntervals = value;
	}

	std::wstring DataSets::getFilename() const
	{
		return _filename;
	}

	void DataSets::setFilename(const std::wstring& value)
	{
		_filename = value;
	}

	std::vector<std::vector<double>> DataSets::getDataset() const
	{
		return _dataset;
	}

	void DataSets::setDataset(const std::vector<std::vector<double>>& value)
	{
		_dataset = value;
	}

	std::vector<int> DataSets::getLingvisticAttribute() const
	{
		return _lingvisticAttribute;
	}

	void DataSets::setLingvisticAttribute(const std::vector<int>& value)
	{
		_lingvisticAttribute = value;
	}

	double DataSets::getInitialError() const
	{
		return _initialError;
	}

	void DataSets::setInitialError(const double& value)
	{
		_initialError = value;
	}

	void DataSets::ClearDataset()
	{
		setDatasetSize(0);
		setInputAttributes(0);
		setOutputAttributes(0);
		setOutputIntervals(0);
		setInitialError(-1);
		setFilename(L"text.txt");
		getDataset().clear();
		getLingvisticAttribute().clear();
	}

	void DataSets::NormalizeDataset()
	{
		auto min = std::vector<double>(getInputAttributes());
		auto max = std::vector<double>(getInputAttributes());

		for (int i = 0; i < getInputAttributes(); i++)
		{
			if (getLingvisticAttribute()[i] == 0)
			{
				min[i] = getDataset()[0][i];
				max[i] = getDataset()[0][i];
				for (int k = 1; k < getDatasetSize(); k++)
				{
					if (getDataset()[k][i] < min[i])
					{
						min[i] = getDataset()[k][i];
					}
					if (getDataset()[k][i] > max[i])
					{
						max[i] = getDataset()[k][i];
					}
				}
				for (int k = 0; k < getDatasetSize(); k++)
				{
					getDataset()[k][i] = (getDataset()[k][i] - min[i]) / (max[i] - min[i]);
				}
			}
		}
	}

	double DataSets::ComputeInitialError()
	{
		setInitialError(0.0);
		int max;
		auto classes = std::vector<int>(getOutputIntervals());

		for (int i = 0; i < getOutputIntervals(); i++)
		{
			classes[i] = 0;
		}

		for (int x = 0; x < getDatasetSize(); x++)
		{
			classes[static_cast<int>(getDataset()[x][getInputAttributes()])]++;
		}

		max = classes[0];
		for (int i = 0; i < getOutputIntervals(); i++)
		{
			if (classes[i] > max)
			{
				max = classes[i];
			}
		}
		setInitialError(1 - max * 1.0f / getDatasetSize());

		return getInitialError();
	}


	void DataSets::ShrinkDataset(int size)
	{
		if (size < getDatasetSize())
		{
			auto shrinked = std::vector<std::vector<double>>(size);
			setDatasetSize(size);

			for (int i = 0; i < getDataset().size(); i++)
			{
				if (i < size)
				{
					shrinked[i] = getDataset()[i];
				}
			}
			setDataset(shrinked);
		}
		ComputeInitialError();
		NormalizeDataset();
	}

	template <typename T>
	void RandomExtensions::Shuffle(std::vector<T>& array_Renamed)
	{
		auto n = array_Renamed.size();
		while (n > 1)
		{
			auto k = rand % (n--);
			auto temp = array_Renamed[n];
			array_Renamed[n] = array_Renamed[k];
			array_Renamed[k] = temp;
		}
	}
}
