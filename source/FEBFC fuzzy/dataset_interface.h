#ifndef _DATASET_INTERFACE_H_
#define _DATASET_INTERFACE_H_

#include <vector>
#include <stdio.h>
#include <math.h>

struct sDatasetItem
{
	std::vector<float> input;
	std::vector<float> output;
};

class CDatasetInterface
{
protected:
	std::vector<struct sDatasetItem> items;

public:
	CDatasetInterface()
	{

	}

	virtual ~CDatasetInterface()
	{


	}

	struct sDatasetItem get(unsigned int idx)
	{
		return items[idx];
	}

	unsigned int get_size()
	{
		return items.size();
	}

	unsigned int get_input_size()
	{
		return items[0].input.size();
	}

	unsigned int get_output_size()
	{
		return items[0].output.size();
	}

	unsigned int compare_sign(unsigned int idx, std::vector<float> &output)
	{
		for (unsigned int i = 0; i < items[idx].output.size(); i++)
		{
			if ((items[idx].output[i] > 0.0) && (output[i] < 0.0))
				return 0;

			if ((items[idx].output[i] < 0.0) && (output[i] > 0.0))
				return 0;
		}

		return 1;
	}

	float compare_distance(unsigned int idx, std::vector<float> &output)
	{
		float res = 0.0;
		for (unsigned int i = 0; i < items[idx].output.size(); i++)
		{
			res += (items[idx].output[i] - output[i])*(items[idx].output[i] - output[i]);
		}

		return sqrt(res);
	}

	void normalise()
	{
		for (unsigned int j = 0; j < items[0].input.size(); j++)
		{
			float min = 100000000.0;
			float max = -min;

			for (unsigned int i = 0; i < items.size(); i++)
			{
				if (items[i].input[j] < min)
					min = items[i].input[j];

				if (items[i].input[j] > max)
					max = items[i].input[j];
			}

			if (max > min)
			{
				// y = kx + q
				float k = (1.0 - (-1.0)) / (max - min);
				float q = 1.0 - k*max;

				for (unsigned int i = 0; i < items.size(); i++)
					items[i].input[j] = k*items[i].input[j] + q;
			}
		}
	}

	virtual void export_image(unsigned int idx)
	{
		(void)idx;
	}
};


#endif
