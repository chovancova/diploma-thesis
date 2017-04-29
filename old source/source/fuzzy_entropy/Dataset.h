#pragma once
#include <vector>
#include <string>

struct DataItem
{
	std::vector<float> features;
	std::vector<float> features_normalised;
	std::vector<float> label;
};

class Dataset
{
public:

	static Dataset* create(std::string type, std::string filename);

protected:
	std::vector<struct DataItem> items;
public:

	Dataset();
	virtual ~Dataset() {}

	virtual int load(const std::string &filename) = 0;
	

	unsigned int getSize() const { return items.size(); }
	unsigned int getFeatureSize() { return items[0].features.size(); }
	struct DataItem get(unsigned int index) { return items[index]; }

	void print(bool print_original = false);
	void print(unsigned int index, bool print_original = false);
	DataItem rndFromArray();
	void normalise();
};


class DatasetIris :
	public Dataset
{
public:
	DatasetIris() {}
	~DatasetIris() {}

	int load(const std::string& filename) override;
};
