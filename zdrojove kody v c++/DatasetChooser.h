#pragma once

#include <string>

namespace Datasets
{
	class DataSets;
}

namespace Datasets
{
	enum class DatasetType
	{
		Heart,
		Iris,
		Seeds,
		Skin,
		Wine,
		Yeast,
		Bupa,
		Balance,
		Vowel,
		Pima,
		Venicle,
		Wpbc,
		Wdbc,
		Test
	};

	class DatasetChooser final
	{
	public:
		static DataSets* ReadDatasetFromFile(DatasetType type, int datasetSize, int inputAttributes, int outputIntervals, const std::wstring& filename);

		static DataSets* ReadDatasetFromFile(DatasetType type, const std::wstring& filename);
	};
}
