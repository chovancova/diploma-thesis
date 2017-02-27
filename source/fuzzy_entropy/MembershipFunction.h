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
	/*
	* Step C. Assign a membership function for each interval.
	* Case I) The left-most interval.
	* Case II) The right-most interval.
	* Case III) The internal intervals.
	*/
	void process(std::vector<float> input);
	float sum();
	std::vector<std::vector<float>> get();
	void print();

private:
	float mu(float x, int c, int c_left, int c_right, unsigned int dimension);
	int get_left_center(int center_index, unsigned int dimension);
	int get_right_center(int center_index, unsigned int dimension);

	float max(float a, float b);
};

