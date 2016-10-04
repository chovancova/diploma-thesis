#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include "c:\cpp\MyTempFunction.cpp"
#include "c:\cpp\DataSets\DataSets.cpp"

// --------------------   main-DataSets()  ----------------------------------------
main()
{ unsigned int numDB = _PODOFILINI; //SF_KAPUR;
  float        error;

  DataSets initialData(numDB);
  initialData.ReadDataSets(numDB);
  initialData.WriteCrispFile();     // ********* Check of initial data

  error = initialData.InitialError(numDB);

  printf("Press any key... TotalSets = %d   InitialError =%f", initialData.ReturnTotalSets(), error);
  getchar();      getchar();
}

