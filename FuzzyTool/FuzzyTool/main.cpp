#include <iostream>
#include <string>
#include "main.h"

#include "DataSets.h"
#include "Fuzzyfication.h"
#include <sstream>
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
		bool is_dataset_loaded = InitializeDataset(id_dataset);
		if(is_dataset_loaded)
		{
			RunFuzzy(id_dataset);
		}
		cout << "Press 1 to exit application. \n" << flush;
		cout << "Press any key to show menu. \n" << flush;
		cin >> end;
		if (end == 1)
		{
			return 1;
		}
		
		//
	}
}

bool InitializeDataset(int id_dataset)
{
	if (id_dataset > 0)
	{
		float error;
		DataSets initial_data(id_dataset);
		int result = initial_data.ReadDataSets(id_dataset);
		if (result < 0)
		{
			cout << "Press any key to exit application. ";
			getchar();
			getchar();
			return false;
		}

		error = initial_data.InitialError(id_dataset);
		cout << "Write crisp data to file. ";
		/*getchar();
		initialData.WriteCrispFile();     
		cout << "Normalize crisp data. ";
		getchar();
		initialData.Normalization();
		cout << "Write crisp data to file. ";
		getchar();
		initialData.WriteCrispFile();*/

		printf("Total values in dataset = %d  \nInitial Error =%f", initial_data.GetDatasetSize(), error);
		return true;
	}
	return false;
}

int LoadDatasetIdFromConsole()
{
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
	// How to get a number.
	int id_dataset = 0;
	string input = "";
	cout << "\nEnter Dataset ID: " << flush;

	getline(cin, input);
	cout << "You entered: " << input << endl << endl;
	
	while(true)
	{
		if (id_dataset < 7 && id_dataset > 0)
		{
			break;
		}
		while (true) {
			cout << "Please enter a valid number: ";
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream myStream(input);
			if (myStream >> id_dataset)
			{
				break;
			}
			cout << "Invalid number, please try again" << endl;
			cout << "You entered: " << id_dataset << endl << endl;
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
