#include "DatasetIris.h"


namespace Datasets
{
	DatasetIris::DatasetIris(int datasetSize, int inputAttributes, int outputIntervals, const std::wstring& filename) : DataSets(datasetSize, inputAttributes, outputIntervals, filename)
	{
	}

	DatasetIris::DatasetIris(const std::wstring& filename, int datasetSize, int inputAttributes, int outputIntervals) : DataSets(datasetSize, inputAttributes, outputIntervals, filename)
	{
	}

	int DatasetIris::InitializeDataset()
	{
		try
		{
			// Open the text file using a stream reader.

			{
				//auto sr = new StreamReader(getFilename());
				auto j = 0;
				auto value = 0.0;
				// Read the stream to a string, and write the string to the console.
				std::wstring line;
				auto data = std::vector<std::wstring>(getInputAttributes());

				//while ((line = sr->ReadLine()) != L"")
				{
					if (!line.empty())
					{
						data = StringHelper::split(line, L',');
						getDataset()[j] = std::vector<double>(getAttributes());
						for (int i = 0; i < getInputAttributes(); i++)
						{
							//	double::TryParse(data[i], NumberStyles::Any, CultureInfo::InvariantCulture, getDataset()[j][i]);
						}
						//specific for iris
						//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
						//						switch (data[InputAttributes])
						//ORIGINAL LINE: case "Iris-setosa":
						if (data[getInputAttributes()] == L"Iris-setosa")
						{
							getDataset()[j][getInputAttributes()] = 0;
						}
						//ORIGINAL LINE: case "Iris-versicolor":
						else if (data[getInputAttributes()] == L"Iris-versicolor")
						{
							getDataset()[j][getInputAttributes()] = 1;
						}
						//ORIGINAL LINE: case "Iris-virginica":
						else if (data[getInputAttributes()] == L"Iris-virginica")
						{
							getDataset()[j][getInputAttributes()] = 2;
						}
						j++;
					}
				}
				//delete sr;
			}
		}
		catch (const std::exception& e)
		{
			std::wcout << L"Dataset not initialized." << std::endl;
			std::wcout << e.what() << std::endl;
			return -1;
		}
		ComputeInitialError();
		return 1;
	}
}
