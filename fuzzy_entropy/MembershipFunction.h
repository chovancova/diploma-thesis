#pragma once
#include <vector>
#include "KMeans.h"

class MembershipFunction
{
	private:
		std::vector<std::vector<float>> centers;
		std::vector<std::vector<float>> result;
		class KMeans *kmeans;

public:
	MembershipFunction(class KMeans *kmeans);
	~MembershipFunction();

	void process(std::vector<float> input);

	std::vector<std::vector<float>> get();

private:
	float mu(float x, float c, float c_left, float c_right);
};

