#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "c:\cpp\MyTempFunction.cpp"
#include "c:\cpp\DataSets\DataSets.cpp"

#define PATHoutFuzzy    "c:\\cpp\\Fuzzy\\db\\"
//#include "c:\cpp\fuzzy\fuzzy.cpp"
#include "c:\cpp\fuzzy\CentersFCM.cpp"

// -----------------------------------------------------------------------------

main()
{ unsigned int numDB = _LENKA_DECERNO;  // ********* Number of DataBase

  Fuzzy newA(numDB); // Fuzzy        newA      (numDB);
//  newA.ReadDataSets(numDB);
//  newA.WriteCrispFile();
  newA.StartFuzzification(numDB);
  printf("Fuzzyfication is finished.  Press any key...");
//  getchar();
}

