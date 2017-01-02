#pragma once
#include <vector>
#include "IDataset.h"`

struct KMeansResult
{
	std::vector<float> distances;
	unsigned int cluster_id;
	float label;
};

class KMeans
{
private:
	std::vector<struct DataItem> centers;

	struct KMeansResult result;

public:
	KMeans(unsigned int centers_count, unsigned int features_count);
	~KMeans();

	void process(struct DataItem &item, float learning_rate = 0.0);

	struct KMeansResult get();
	unsigned int getSize();
	struct DataItem get_center(unsigned int index);

	void print_result();

protected:
	virtual float distance(std::vector<float> &v1, std::vector<float> &v2);
	float rnd();

};

