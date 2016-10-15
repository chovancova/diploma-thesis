#include "TempFunctions.h"
#include "data_sets/DataSets.h"
#include "fuzzy.h"

void run_data_sets()
{

  unsigned int numDB = _IRIS;
  float        error;

  DataSets initialData(numDB);
  initialData.ReadDataSets(numDB);
  initialData.WriteCrispFile();     // ********* Check of initial data

  // initialData.InitialError(numDB) - > nie je definovana
  /*
  error = initialData.InitialError(numDB);

  printf("Press any key... TotalSets = %d   InitialError =%f", initialData.ReturnTotalSets(), error);

  getchar();
  getchar();
  */
}


void run_fuzzy()
{
  unsigned int numDB = _IRIS ;// ********* Number of DataBase

    Fuzzy newA(numDB); // Fuzzy        newA      (numDB);
  newA.ReadDataSets(numDB);
  newA.WriteCrispFile();
    newA.StartFuzzification(numDB);
    printf("Fuzzyfication is finished.  Press any key...");
}


int main()
{
  run_data_sets();
  run_fuzzy();

  getchar();

  return 0;
}
