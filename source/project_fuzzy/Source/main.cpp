#include "TempFunctions.h"
#include "DataSets/DataSets.h"
#include "Fuzzy/fuzzy.h"

void run_data_sets(unsigned int numDB)
{
	float        error;
	DataSets initialData(numDB);
	initialData.ReadDataSets(numDB);
//	initialData.WriteCrispFile();     // ********* Check of initial data

	error = initialData.InitialError(numDB);

	printf("Press any key... TotalSets = %d   InitialError =%f", initialData.ReturnTotalSets(), error);

	getchar();
	getchar();
}


void run_fuzzy(unsigned int numDB)
{
	Fuzzy newA(numDB); 
	newA.ReadDataSets(numDB);
	newA.WriteCrispFile();
	newA.StartFuzzification(numDB);
	printf("Fuzzyfication is finished.  Press any key...");
}

int main()
{
	unsigned int numDB = _IRIS;
	run_data_sets(numDB);
	run_fuzzy(numDB);
	
	unsigned int numDB2 = _HEART;
	run_data_sets(numDB2);
	run_fuzzy(numDB2);

	getchar();

	return 0;
}
