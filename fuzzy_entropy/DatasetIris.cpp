#include "DatasetIris.h"



DatasetIris::DatasetIris()
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
	const char filename[] = "iris.data";
	unsigned int count_atributes = 4;

	 fopen_s(&fp, filename, "r");
	if (fp == nullptr)
	{
		printf("cannot open file %s\n", filename);
		return;
	}


	char label_name[200] = "";
	
	struct DataItem tmp;
	for (unsigned int i = 0; i < count_atributes; i++)
		tmp.features.push_back(0.0);
	tmp.label = 0;


	while (!feof(fp))
	{
		fscanf_s(fp, "%f,%f,%f,%f,%s",
			&tmp.features[0], &tmp.features[1], &tmp.features[2], &tmp.features[3], label_name, sizeof(label_name));

		if (!strcmp(label_name, "Iris-setosa")) 
			tmp.label = 0;
		if (!strcmp(label_name, "Iris-versicolor"))
			tmp.label = 1;
		if (!strcmp(label_name, "Iris-virginica")) 
			tmp.label = 2;
		
		items.push_back(tmp);
	}

	fclose(fp);	
}


DatasetIris::~DatasetIris()
{

}
