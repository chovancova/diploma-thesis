#include "Dataset.h"

Dataset* Dataset::create(std::string type, std::string filename)
{
	Dataset *ds = nullptr;

	if (type.compare("iris") == 0)
	{
		ds = new DatasetIris();
	}
	else
	{
		printf("Unknown dataset type: %s\n", type.data());
		return nullptr;
	}

	if (ds == nullptr)
	{
		printf("Allocation error. ");
		return nullptr;
	}

	if (ds->load(filename) < 0)
	{
		return nullptr;
	}

	return ds;
}

Dataset::Dataset()
{
}

void Dataset::print(bool print_original)
{
	for (unsigned int i = 0; i < items.size(); i++)
		print(i, print_original);
}

void Dataset::print(unsigned index, bool print_original)
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

	printf_s(" => ");
	for (unsigned int i = 0; i < items[index].label.size(); i++)
		printf_s("%6.3f ", items[index].label[i]);

	printf_s("\n");
}

void Dataset::normalise()
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
DataItem Dataset::rndFromArray()
{
	int randIdex = rand() % items.size();
	return	items[randIdex];
}


int DatasetIris::load(const std::string &filename)
{
	/*Attribute Information:
	1. sepal length in cm
	2. sepal width in cm
	3. petal length in cm
	4. petal width in cm
	5. class :
	--Iris Setosa
	-- Iris Versicolour
	-- Iris Virginica*/
	//5.1, 3.5, 1.4, 0.2, Iris - setosa

	FILE *fp;
	unsigned int count_atributes = 4;

	fopen_s(&fp, filename.data(), "r");
	if (fp == nullptr)
	{
		printf("Failed to open file %s", filename.data());
		perror("");
		return -1;
	}

	char label_name[200] = "";

	struct DataItem tmp;
	for (unsigned int i = 0; i < count_atributes; i++)
		tmp.features.push_back(0.0);

	tmp.label.push_back(0.0);
	tmp.label.push_back(0.0);
	tmp.label.push_back(0.0);

	while (!feof(fp))
	{
		fscanf_s(fp, "%f,%f,%f,%f,%s",
			&tmp.features[0], &tmp.features[1], &tmp.features[2], &tmp.features[3], label_name, sizeof(label_name));

		for (unsigned int i = 0; i < tmp.label.size(); i++)
			tmp.label[i] = 0.0;

		if (!strcmp(label_name, "Iris-setosa"))
			tmp.label[0] = 1.0;
		if (!strcmp(label_name, "Iris-versicolor"))
			tmp.label[1] = 1.0;
		if (!strcmp(label_name, "Iris-virginica"))
			tmp.label[2] = 1.0;

		items.push_back(tmp);
	}

	fclose(fp);
}