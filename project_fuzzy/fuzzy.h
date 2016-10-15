#ifndef _FUZZY_H_
#define _FUZZY_H_

#include "data_sets/DataSets.h"


#define PATHoutFuzzy    "..\\project_fuzzy\\data_sets\\db_all\\"


#define LIMIT_ITTERATION  100



class Fuzzy : public DataSets
{
  public:
    unsigned int *NumberOfIntervals;
    float***      A;
    float        *minA, *maxA;

    FILE*    fp_hlam;


  public:
   Fuzzy(unsigned int numDB);
  ~Fuzzy(){ delete[] NumberOfIntervals;  delete[] minA; delete[] maxA; fclose(fp_hlam);}

   void   StartFuzzification(unsigned int numDB);
   int    WriteFuzzyFile    (char* FileNameOut);
   int    WriteFuzzyFileHlam(void);
   void   Normalization     (void);
   void   SortAscendingOrder(float *PointsOfCut, unsigned int numberOfCutPoints);
   void   SortAscendingOrder(float *AscR, unsigned long *AscN, unsigned long numberOfElements);
  private:
   float *Center        (unsigned int i,float *AscR,unsigned long *AscN,unsigned long countAscR);
   float  EntropyCalculate (unsigned int i);
   void   Fuzzification    (unsigned int i, float* c);
   void   CreateACube      (void);
   void   DeleteACube      (void);
   void   ModifyACube      (unsigned int i, int ChangeOfInterval);   // nie see
   unsigned long CreateAscRAscN(unsigned int i, float *AscR, unsigned long *AscN);
   float  log2(float x)    {return (float)log(x)/log(2); }

   float *CenterFCM(unsigned int attr, unsigned int NoC, float m, unsigned int distType);
   float  distance (float a, float b, int distType, int p);
};

#endif
