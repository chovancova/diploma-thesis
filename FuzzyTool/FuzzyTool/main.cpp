#include <iostream>
#include <string>
#include "main.h"

#include "DataSets.h"
#include "Fuzzyfication.h"
using namespace std;

int LoadDatasetIdFromConsole();
bool InitializeDataset(int id_dataset);

void RunFuzzy(int id_dataset);

int main(int argc, char* argv[])
{
	int end = 0;

	while (true)
	{
		int id_dataset = LoadDatasetIdFromConsole();
		bool isDatasetLoaded = InitializeDataset(id_dataset);

		RunFuzzy(id_dataset);
		cout << "Press 1 to exit application. \n" << flush;
		cout << "Press 0 key to show menu. \n" << flush;
		cin >> end;
		if (end == 1) { return 1; }
		//getchar();
	}
}

bool InitializeDataset(int id_dataset)
{
	if (id_dataset >= 0)
	{
		float error;
		DataSets initialData(id_dataset);
		int result = initialData.ReadDataSets(id_dataset);
		if (result < 0)
		{
			cout << "Press any key to exit application. ";
			getchar();
			getchar();
			return false;
		}

		error = initialData.InitialError(id_dataset);
		cout << "Write crisp data to file. ";
		/*getchar();
		initialData.WriteCrispFile();     
		cout << "Normalize crisp data. ";
		getchar();
		initialData.Normalization();
		cout << "Write crisp data to file. ";
		getchar();
		initialData.WriteCrispFile();*/

		printf("Total values in dataset = %d  \nInitial Error =%f", initialData.GetSizeOfDataset(), error);
		return true;
	}
	return false;
}

int LoadDatasetIdFromConsole()
{
	int id_dataset = 0;
	cout << "Fuzzification Tool \n";
	cout << "\n";
	cout << "Available datasets: \n"
		<< "ID - Dataset Name\n"
		<< "-------------------------\n"
		<< "1  - Heart\n"
		<< "2  - Iris\n"
		<< "3  - Seeds\n"
		<< "4  - Skin\n"
		<< "5  - Wine\n"
	/*	<< "6  - Wine quality red\n"
		<< "7  - Wine equality white\n"*/
		<< "6  - Yeast\n"
		<< "0  - None\n"
		<< "\n";

	while (id_dataset == 0)
	{
		cout << "\nEnter Dataset ID: " << flush;
		cin >> id_dataset;
		if (id_dataset == 0) { break; }
		if (id_dataset > 8 || id_dataset < 0)
		{
			cout << "Wrong Input.\n";
			id_dataset = 0;
		}
	}
	return id_dataset;
}

void RunFuzzy(int id_dataset)
{
	Fuzzyfication fuzzy(id_dataset);
	cout << "Read Data Sets.\n";
	fuzzy.ReadDataSets(id_dataset);
	cout << "Write Crisp File.\n";
	fuzzy.WriteCrispFile();
	cout << "Run Fuzzification.\n";
	fuzzy.RunFuzzification();

	printf("Fuzzyfication is done.");
}
