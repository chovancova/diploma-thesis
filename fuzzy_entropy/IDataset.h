#pragma once
#include <vector>
struct DataItem
{
	std::vector<float> features;
	std::vector<float> features_normalised;
	int label;
};

class IDataset 
{
	protected:
		std::vector<struct DataItem> items;
	public: 
		IDataset();
		~IDataset();

	unsigned int getSize();
	unsigned int getFeatureSize();
	struct DataItem get(unsigned int index);
	
	void print(bool print_original = false);
	void print(unsigned int index, bool print_original = false);
	inline DataItem IDataset::rndFromArray();
	void normalise();
};

inline IDataset::IDataset()
{
}

inline IDataset::~IDataset()
{
}

inline unsigned IDataset::getSize() 
{
	return items.size();
}

inline unsigned IDataset::getFeatureSize()
{
	return items[0].features.size();
}

inline DataItem IDataset::get(unsigned int index)
{
	return items[index];
}


inline void IDataset::print(bool print_original)
{
	for (unsigned int i = 0; i < items.size(); i++)
		print(i, print_original);
}

inline void IDataset::print(unsigned index, bool print_original)
{
	printf_s("%5i :", index);

	if (print_original)
	{
		for (unsigned int i = 0; i < items[index].features.size(); i++)
			printf_s("%6.3f ", items[index].features[i]);
	}
	else
	{
		for (unsigned int i = 0; i < items[index].features_normalised.size(); i++)
			printf_s("%6.3f ", items[index].features_normalised[i]);
	}

	printf_s(" => %i \n", items[index].label);
}

inline void IDataset::normalise()
{
	unsigned int i, j;

	for (j = 0; j < items.size(); j++)
	{
		items[j].features_normalised.clear();
		for (i = 0; i < items[j].features.size(); i++)
			items[j].features_normalised.push_back(items[j].features[i]);
	}

	for (i = 0; i < items[0].features.size(); i++)
	{
		float min = items[0].features[i];
		float max = items[0].features[i];
	
		for (j = 0; j < items.size(); j++)
		{
			if (items[j].features[i] < min)
				min = items[j].features[i];

			if (items[j].features[i] > max)
				max = items[j].features[i];
		}

		float k = 1.0;
		
		if (max > min)
			k = (1.0f - (-1.0f)) / (max - min);

		float q = 1.0f - k*max;


		
		for (j = 0; j < items.size(); j++)
			items[j].features_normalised[i] = k*items[j].features[i] + q;
	}
}
inline DataItem IDataset::rndFromArray()
{
	int randIdex = rand() % items.size();
		return	items[randIdex];
}