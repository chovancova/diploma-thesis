#pragma once
class Statistics
{
public:
	static double my95CI(bool side, double mean, double stDev, int N);
	static double specStDev(unsigned long valPow2, unsigned long val, unsigned long N, unsigned long m);
private:
	Statistics()
	{
	}
};
