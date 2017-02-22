#pragma once
#include <vector>


class IDataset 
{
	protected:
		std::vector<struct DataItem> items;
	public: 
		IDataset();
		~IDataset();


	
	void print(bool print_original = false);
	void print(unsigned int index, bool print_original = false);
	inline DataItem IDataset::rndFromArray();
	void normalise();
};

