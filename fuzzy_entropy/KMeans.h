#pragma once
#include <vector>
#include "IDataset.h"

struct KMeansResult
{
	std::vector<float> distances;
	unsigned int cluster_id;
	std::vector<float> label;
};

class KMeans
{
private:
	std::vector<struct DataItem> centers;

	struct KMeansResult result;

public:
	KMeans(unsigned int centers_count, unsigned int features_count, unsigned int classes_count);
	~KMeans();
	/*
	  Step B. Determination of the Interval Locations 
	*		(Determinig the center and width of each interval)
	* Step 1) Set the initial number of clusters, I.
	* Step 2) Set initial centers of clusters.
	* Step 3) Assign cluster label to each element.  
	* Step 4) Recompute the cluster centers. 
	* Step 5) Does any center change? Yes, Stop, Otherwise go to Step 3. 
	 */
	float process(struct DataItem &item, float learning_rate = 0.0);
	struct KMeansResult get();
	unsigned int getSize();
	unsigned getCenterItemSize();
	void setCenter(DataItem center, unsigned index);
	struct DataItem get_center(unsigned int index);


	void print_result();

protected:
	virtual float distance(std::vector<float> &v1, std::vector<float> &v2);
	float rnd();

};

