#include "DatasetIris.h"
#include "KMeans.h"

int main()
{
	DatasetIris iris;

	iris.normalise();
	iris.print();

	KMeans k_means(8, iris.get(0).features.size());


	unsigned iterations_max = 100000;
	float learning_rate = 0.01;

	for (unsigned iterations = 0; iterations < iterations_max; iterations++)
	{
		unsigned int idx = rand() % iris.getSize();
		struct DataItem item = iris.get(idx);
		k_means.process(item, learning_rate);
	}


	 

	printf("\n");
	for (unsigned i = 0; i < k_means.getSize(); i++)
	{
		struct DataItem item = k_means.get_center(i);
		for (unsigned j = 0; j < item.features_normalised.size(); j++)
			printf("%f \t", item.features_normalised[j]);

		printf("\n");

	}

	for (unsigned idx = 0; idx < iris.getSize(); idx++)
	{
		iris.print(idx);

		k_means.process(iris.get(idx), 0.0);

		k_means.print_result();
		printf("\n");
	}


	 
	printf("program done\n");
	getchar();

	return 0;
}
