#ifndef _MEMBERSHIP_FUNCTION_H_
#define _MEMBERSHIP_FUNCTION_H_

#include <vector>

class CMembershipFunction
{
private:
	std::vector<float> centers;

public:
	std::vector<float> result;

public:
	CMembershipFunction();

	CMembershipFunction(std::vector<float> &centers_);
	~CMembershipFunction();

	void process(float x);

	void print_result();

protected:
	float abs(float x);

};

#endif
