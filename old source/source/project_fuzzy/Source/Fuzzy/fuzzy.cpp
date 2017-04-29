
#include "fuzzy.h"

#include "../TempFunctions.h"

#include <stdlib.h>
#include <string.h>

// ------------------------------------------------------------------------------
Fuzzy::Fuzzy(unsigned int numDB) : DataSets(numDB) //, centerCalc(numDB) , statistic(numDB) ************************
{ minA = newFloat(NumberOfInputAttributes, 0, "minA in Fuzzy()");
  maxA = newFloat(NumberOfInputAttributes, 0, "maxA in Fuzzy()");
  NumberOfIntervals = newUnInt(NumberOfAttributes, 2, "NumberOfIntervals in Fuzzy()");
  char FuzzyNameHlam[99];
  strcpy(FuzzyNameHlam,PATHoutFuzzy); strcat(FuzzyNameHlam,nameDB); strcat(FuzzyNameHlam,".hlam");
  fp_hlam=fopen(FuzzyNameHlam, "w");
  if (fp_hlam == NULL)  MyError("Error fp_hlam in Fuzzy()\n");
}  // ------------------        Start   -------------------------------


void Fuzzy::StartFuzzification(unsigned int numDB)
{ unsigned long *AscN, countAscR;
  unsigned int   ptr;
  int            change, end; // end - used for ++ ++ 4
  char           FuzzyNameDB[99];
  float         *AscR, *c, Hold, Hnew;

  ReadDataSets(numDB);
//   WriteCrispFile();               // for verification DB
  Normalization();

  strcpy(FuzzyNameDB,PATHoutFuzzy); strcat(FuzzyNameDB,nameDB); strcat(FuzzyNameDB,".cm"); // FCM centers
  CreateACube();
fprintf(fp_hlam, "FuzzyNameDB=%s\n", FuzzyNameDB);

  for(unsigned int i=0; i<NumberOfInputAttributes; i++)    // -----  Start i ---
  { printf("i=%d\n", i);
    if (nonNumericAttributes[i] != 0)        //  we have got a Lingvistic Attribute
    { NumberOfIntervals[i] = nonNumericAttributes[i];
      for( unsigned long k=0; k<TotalSets; k++)
      { ptr = (unsigned int)R[k].A[i];
// ----------  ostrava1 db only ------------- this fragment for OSTRAVA1 only
//        if (ptr == 2) { A[i][0][k] = 0.5f;
//                        A[i][1][k] = 0.5f;
//                      }
//        else            A[i][ptr][k] = 1.0f;
         A[i][ptr][k] = 1.0f;
// ----------  ostrava1 db only
      }
    }
    else // (nonNumericAttributes[i] == 0)   //  we have got a Numeric Attribute
    { change    = 0;
end = 0;
      Hnew      = 1000000000.0;
      AscR      = (float*)        newFloat (TotalSets, 0.0, "AscR in TaiwanIdea()");
      AscN      = (unsigned long*)newUnLong(TotalSets,  0L, "AscN in TaiwanIdea()");
      countAscR = CreateAscRAscN(i, AscR, AscN);
fprintf(fp_hlam, "MinA[i]=%f      MaxA[i]=%f\n", minA[i], maxA[i]);
fprintf(fp_hlam, "AscR[q]   AscN[q]\n");
for(unsigned long z=0; z<countAscR; z++) fprintf(fp_hlam, "%lf\t%d\n",AscR[z],AscN[z]);
fprintf(fp_hlam,"countAscR=%ld\n", countAscR);
      do { Hold = Hnew;
           if (change != 0)  ModifyACube(i, change);
		     c =(float*) Center(i, AscR, AscN, countAscR); // fuzzy C-mean centers
           Fuzzification(i, c);
           delete[] c;
           Hnew = EntropyCalculate(i);
fprintf(fp_hlam, "i=%d  NoI[i]=%d  Hnew=%f\n\n",i, NumberOfIntervals[i],   Hnew);
//  ---------------  + 2 intervals ----------------------------------------------------------------
//           if ((end == 1) || (change == -1) || (NumberOfIntervals[i]==countAscR)) break;
//           if (Hnew <= Hold)  change= 1;                // continue  TaiwanIdea
//           else             { change= 1; end = 1; }

             if ((change == -1) || (NumberOfIntervals[i]==countAscR)) break;
             if ((Hnew <= Hold)) change= 1;                // continue  TaiwanIdea // hlam && (NumberOfIntervals[i] < 3)
//             else       change=-1;      break;                  /* izmenit na +1
               else             break;  /* change=-1; */          /* change these operaters for +1  */    // exit from TaiwanIdea

//  ------------------------------------------------------------------------------------
         } while(1);
WriteFuzzyFileHlam();
      delete[] AscR;
      delete[] AscN;
    }
	}  // i
   WriteFuzzyFile(FuzzyNameDB);
   DeleteACube();
}


// ----------------------   Center  -----------------------------------------------
float* Fuzzy::Center(unsigned int i, float *AscR, unsigned long *AscN,unsigned long countAscR)
{ unsigned int  q, *Nq, n_distance, stop, z, itteration;
  float *c, *sum, center, distance;

  c = (float*) new float[NumberOfIntervals[i]];
  c = (float*) CenterFCM(i, NumberOfIntervals[i], 2.0f, 1);
for(z=0;z<NumberOfIntervals[i];z++) fprintf(fp_hlam,"cFCM[%d]=%f ",z,c[z]); fprintf(fp_hlam,"\n");
  itteration = 0;
  do          //**********************************************************
  { sum = newFloat(NumberOfIntervals[i], 0.0, "sum in Center()");
 	 Nq  = newUnInt(NumberOfIntervals[i],   0, "Nq  in Center()");
 	 for(unsigned long k=0; k<countAscR; k++)
 	 { distance = fabs(AscR[k]-c[0]);
 	   for (q=0; q<NumberOfIntervals[i]; q++)    // minimal distance calculate
 		     if (distance >= fabs(AscR[k]-c[q]))
 			    { distance  = fabs(AscR[k]-c[q]);     n_distance = q;}
 	   sum[n_distance] += AscR[k] * AscN[k];
 	   Nq [n_distance] += AscN[k];
 	 }
 	 stop = 1;
 	 for (q=0; q<NumberOfIntervals[i]; q++)      // end of clastering
 	   if (Nq[q] == 0)        MyError("UnReal situation: Nq[q]=0 in Center()");
 	   else
 	   {  center = (float)sum[q]/(float)Nq[q];
 		   if (c[q] != center) { c[q] = center; stop = 0; /* NONStop */   }
         itteration++;                                        // NE ZNAJU ZA CHEM ETA BOTVA
 	   }
 	 for (q=0; q<NumberOfIntervals[i]-1; q++)      // check non-equal centers
  	     if (c[q] == c[q+1])  MyError("UnReal situation: c[q]=c[q+1] in Center()");
    delete[] sum;
	 delete[] Nq;
  } while ((stop==0)  && (itteration<LIMIT_ITTERATION) );
  SortAscendingOrder(c, NumberOfIntervals[i]);
for(z=0;z<NumberOfIntervals[i];z++)fprintf(fp_hlam,"c__2[%d]=%f ",z,c[z]);fprintf(fp_hlam,"\n");
  return(c);
}



// ---------------       Fuzzification   -------------------------------------
void Fuzzy::Fuzzification(unsigned int i, float* c)
{  for (unsigned long k=0; k<TotalSets; k++)
   { for(unsigned int j=0; j<NumberOfIntervals[i]; j++)
              A[i][j][k]=0;
     for(unsigned int j=0; j<NumberOfIntervals[i]-1; j++)
       if ((R[k].A[i]  >=  c[j]) && (R[k].A[i] <= c[j+1]))
   	 {  A[i][j][k]   = (c[j+1] - R[k].A[i])/ (c[j+1] - c[j]);
	 	    A[i][j+1][k] = (R[k].A[i] - c[j])  / (c[j+1] - c[j]);
	 	 }
	  if (R[k].A[i] < c[0])  A[i][0][k] = 1.0;
	  if (R[k].A[i] > c[NumberOfIntervals[i]-1]) A[i][NumberOfIntervals[i]-1][k] = 1.0;
	}  // k
}


// ---------------       Entropy   -----------------------------------------
float Fuzzy::EntropyCalculate(unsigned int i)
{ unsigned int   j, ja, jb, sector;
  unsigned long *countM;
  float       ***M, **sumM, Hnew, Hsum, max, p;

  countM = (unsigned long*) newUnLong(NumberOfIntervals[i], 0L,"countM in EntropyCalc()");
  M      = (float***) new float** [NumberOfIntervals[i]];
  sumM   = (float**)  new float*  [NumberOfIntervals[i]];
  if(!M || !sumM) MyError("Error allocation of (M and sumM) in EntropyCalculate()");
  for(sector=0; sector< NumberOfIntervals[i]; sector++)
  {  sumM[sector] = (float*) newFloat(NumberOfIntervals[i], 0, "sumM(EntropyCalc)");
	  M[sector]    = (float**)new float* [NumberOfIntervals[i]];
     if(!M[sector]) MyError("Error allocation of (M[sector]) in EntropyCalcululate()");
     for(ja=0; ja< NumberOfIntervals[i]; ja++)
      M[sector][ja] =(float*)newFloat(NumberOfOutputIntervals, 0,"M in EntropyCalc()");
  }

  for (unsigned long k=0; k<TotalSets; k++)
  {  max = A[i][0][k];                              // Search Sector
     for (j=0; j<NumberOfIntervals[i]; j++)
   	 if (max <= A[i][j][k]) {  sector = j;   max = A[i][j][k]; }
     countM[sector]++;

     for (ja=0; ja<NumberOfIntervals[i]; ja++)     // Membership Degree Calculation
       for (jb=0; jb<NumberOfOutputIntervals; jb++)
          M[sector][ja][jb] += A[i][ja][k]*A[NumberOfInputAttributes][jb][k];
  } // k

for(sector=0; sector< NumberOfIntervals[i]; sector++)
 for (ja=0; ja<NumberOfIntervals[i]; ja++)         // Membership Degree Calculation
   for (jb=0; jb<NumberOfOutputIntervals; jb++)
     fprintf(fp_hlam, "M[sector=%d][ja=%d][jb=%d]=%f \n", sector, ja, jb, M[sector][ja][jb]);

   for(sector=0; sector< NumberOfIntervals[i]; sector++)// Wage Degree Calculation
  	  for (ja=0; ja<NumberOfIntervals[i]; ja++)
       for (jb=0; jb<NumberOfOutputIntervals; jb++)
          sumM[sector][ja]  += M[sector][ja][jb];

          for (sector=0; sector<NumberOfIntervals[i]; sector++)
fprintf(fp_hlam, "countM[%d]=%d\n", sector, countM[sector]);

	Hsum = 0.0;                            //  Fuzzy Entropy Calculation
	for (sector=0; sector<NumberOfIntervals[i]; sector++)
	{ Hnew = 0.0;
     for (ja=0; ja<NumberOfIntervals[i]; ja++)
		 for (jb=0; jb<NumberOfOutputIntervals; jb++)
       {  p     = (float) (sumM[sector][ja]==0 )? 0: (M[sector][ja][jb]/sumM[sector][ja]);
		 	 Hnew -= (M[sector][ja][jb]==0 )? 0: p*log2(p);
fprintf(fp_hlam, "sector=%d, jb=%d, p=%f Hnew=%f\n", sector, jb, p, Hnew);
       }

     Hsum += Hnew * (float)countM[sector]/TotalSets;

   }
//   Hsum = Hsum/log2((float)(NumberOfIntervals[i]+1));

   // delete M and sumM
  	for(sector=0; sector< NumberOfIntervals[i]; sector++)
   {  for(ja=0; ja< NumberOfIntervals[i]; ja++)
	 		 delete[] M[sector][ja];
      delete[]    M[sector];
      delete[] sumM[sector];
	}
   delete[] M;
   delete[] sumM;
   delete[] countM;
   return(Hsum);
}  // --------------------   CreateACube       ------------------------------------



void Fuzzy::CreateACube()
{ unsigned int i, j;
  for(i=0; i< NumberOfAttributes; i++)
	 if(nonNumericAttributes[i] != 0) NumberOfIntervals[i]=nonNumericAttributes[i];
    else                             NumberOfIntervals[i]=2;
//  NumberOfIntervals[NumberOfInputAttributes] = NumberOfOutputIntervals;

  A = (float***) new float** [NumberOfAttributes];
  if(!A) printf("Error allocation of memory for ***A in CreateACube()");
  for(i=0; i< NumberOfAttributes; i++)
  {  A[i] = (float**) new float* [NumberOfIntervals[i]];
     if(!A[i]) printf("Error allocation of memory for **A[i] in CreateACube()");
	  for(j=0; j< NumberOfIntervals[i]; j++)
	    A[i][j] = (float*) newFloat(TotalSets, 0.0, "A[i][j] in CreateCube()" );
  }
  for(unsigned long k=0; k<TotalSets; k++)    // Initialisation of Output Attribute
   { j = (unsigned int) R[k].A[NumberOfInputAttributes];
     A[NumberOfInputAttributes][j][k] = 1.0;
   }
}


// ----------------   DeleteACube       ------------------------------------
void Fuzzy::DeleteACube()
{ for(unsigned int i=0; i<NumberOfAttributes; i++)
  { for(unsigned int j=0; j<NumberOfIntervals[i]; j++)
		 delete[] A[i][j];
	 delete[] A[i];
  }
  delete[] A;
}


// ----------------   ModifyACube       ------------------------------------
void Fuzzy::ModifyACube(unsigned int i, int ChangeOfInterval)
{ for(unsigned int j=0; j<NumberOfIntervals[i]; j++)
		 delete[] A[i][j];
	 delete[] A[i];

  NumberOfIntervals[i] += ChangeOfInterval;
  A[i] = (float**) new float* [NumberOfIntervals[i]];
  if(!A[i]) MyError("**A[i] in ModifyACube()");
  for(unsigned int j=0; j< NumberOfIntervals[i]; j++)
	    A[i][j] = (float*) newFloat(TotalSets, 0.0, "A[i][j] in ModifyCube()" );
}


// ----------------------  CreateAscRAscN  ------------------------------------
unsigned long Fuzzy::CreateAscRAscN(unsigned int i, float *AscR, unsigned long *AscN)
{ unsigned int  novy;
  unsigned long   = 1;
  AscR[0]    = R[0].A[i];
  AscN[0]    = 1;
  for(unsigned long k=1; k<TotalSets; k++)
  { novy    = 1;
    for(unsigned long q=0; q<countAscR; q++)
       if(R[k].A[i] == AscR[q]) { novy = 0; AscN[q]++;}
    if(novy == 1)   {  AscR[countAscR] = R[k].A[i]; AscN[countAscR]=1; countAscR++;}
  }
  SortAscendingOrder(AscR, AscN, countAscR);
  return(countAscR);
}

// ---------------       SortAscendingOrder   -----------------------------------------
void Fuzzy::SortAscendingOrder(float *AscR, unsigned long *AscN,unsigned long numberOfElements)
{ unsigned long num, index=0L, value;
  float         min;

  do{ min   = AscR[index];
	   num   = index;
	   for(unsigned long k=index+1; k<numberOfElements; k++)
		   if(AscR[k] < min) { min = AscR[k]; num = k;}
	   AscR[num]   = AscR[index];
	   AscR[index] = min;
      value       = AscN[num];
      AscN[num]   = AscN[index];
      AscN[index] = value;
	   index++;
	 } while (index < numberOfElements-1);
}

// ---------------       SortAscendingOrder   -----------------------------------------
void Fuzzy::SortAscendingOrder(float *PointsOfCut, unsigned int numberOfCutPoints)
{ unsigned int i, num, index=0;
  float min;
  do{ min = PointsOfCut[index];
	   num = index;
	   for(i=index+1; i<numberOfCutPoints; i++)
		   if(PointsOfCut[i] < min) { min = PointsOfCut[i]; num = i;}
	   PointsOfCut[num]   = PointsOfCut[index];
	   PointsOfCut[index] = min;
	   index++;
	 } while (index < numberOfCutPoints-1);
}

// ----------------------------   Normalization  ------------------------------
void Fuzzy::Normalization(void)
{ for(unsigned int i=0; i < NumberOfInputAttributes; i++)
    if (nonNumericAttributes[i] == 0)   // we have got a Numeric Attribute
    {  minA[i] = R[0].A[i];
       maxA[i] = R[0].A[i];
       for(unsigned long k=1; k < TotalSets; k++)
       { if(R[k].A[i] < minA[i])   minA[i] = R[k].A[i];
         if(R[k].A[i] > maxA[i])   maxA[i] = R[k].A[i];
       }
       for(unsigned long k=0; k < TotalSets; k++)
           R[k].A[i] = (R[k].A[i] - minA[i])/ (maxA[i] - minA[i]);
    }
}

// --------------------------   WriteFuzzyFile    --------------------------
int Fuzzy::WriteFuzzyFile(char* FileNameOut)
{ FILE *fp;
  fp=fopen(FileNameOut, "w");
  if (fp == NULL)  MyError("Error FileNameOut in Fuzzy::WriteFuzzyFile()\n");

  fprintf(fp,"%ld\n%d %d\n",  TotalSets, NumberOfInputAttributes, NumberOfOutputAttributes) ;
  for (unsigned int i=0; i<NumberOfAttributes; i++)
      fprintf(fp, "%4d ", NumberOfIntervals[i]);      fprintf(fp, "\n");
  for (unsigned int i=0; i<NumberOfInputAttributes; i++)
      fprintf(fp, "%4.2f ", 1.0);      fprintf(fp, "\n");
//    fprintf(fp, "%4.2f ", PriceOfAttributes[i]);      fprintf(fp, "\n");
  for (unsigned long k=0; k<TotalSets; k++)
  { for(unsigned int i=0; i<NumberOfAttributes; i++)
    { for(unsigned int j=0; j<NumberOfIntervals[i]; j++)
        fprintf(fp, "%f ", A[i][j][k]);
      fprintf(fp, "    ");
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 1;
}

// --------------------------   WriteFuzzyFileHlam    --------------------------
int Fuzzy::WriteFuzzyFileHlam(void)
{ fprintf(fp_hlam,"\n\n%ld\n%d %d\n",  TotalSets, NumberOfInputAttributes, NumberOfOutputAttributes) ;
  for (unsigned int i=0; i<NumberOfAttributes; i++)
      fprintf(fp_hlam, "%4d ", NumberOfIntervals[i]);      fprintf(fp_hlam, "\n");
  for (unsigned int i=0; i<NumberOfInputAttributes; i++)
      fprintf(fp_hlam, "%4.2f ", 1.0);      fprintf(fp_hlam, "\n");
  for (unsigned long k=0; k<TotalSets; k++)
  { for(unsigned int i=0; i<NumberOfAttributes; i++)
    { for(unsigned int j=0; j<NumberOfIntervals[i]; j++)
        fprintf(fp_hlam, "%7.4f ", A[i][j][k]);
      fprintf(fp_hlam, "    ");
    }
    fprintf(fp_hlam, "\n");
  }
  return 1;
}


#define EPSILON 0.00001f
//--------------------------------------------------------------------------------------
float Fuzzy::distance(float a, float b, int distType, int p)
{  switch (distType)
   {  case 1 :    /* Euklid */    return sqrt((a-b)*(a-b));
      case 2 :    /* Euklid^2*/   return (a-b)*(a-b);
      case 3 :    /* Mancheten*/  return fabs(a-b);
      case 4 :    /* Minkowski*/  return pow(pow((a-b),p),(1/p));
      default:    /* Euklid*/     return sqrt((a-b)*(a-b));
   }
}
//--------------------------------------------------------------------------------------
float* Fuzzy::CenterFCM(unsigned int Attr, unsigned int NoC, float m, unsigned int distType)
{  double        UikRec, pom1, pom2;
   float        **MembershipFunc, *Centers;
   unsigned int NumberOfIntervals;
	NumberOfIntervals = NoC;
	//-------------------------------------------------------
    Centers = (float*)  newFloat(NumberOfIntervals,          0.0, "Centers[] in FCM()");
    MembershipFunc = (float**) new float* [NumberOfIntervals];
    if(!MembershipFunc) printf("Error allocation of memory for **MembershipFunc in FCM()");
    for(unsigned int j=0; j< NumberOfIntervals; j++)
	         MembershipFunc[j] = (float*) newFloat(TotalSets, 0.0, "U[i][j]   in FCM()");
   //-------------------------------------------------------
		int t = 0;
		bool *assigned;
		assigned = new bool[TotalSets];
		float Jcurr = 0,  Jlast, Jroz; // Jnew - Jold
		float part, minSet=0.0, maxSet=1.0;

//		maxSet = R[0].A[Attr];
//      minSet = R[0].A[Attr];
//		for (unsigned long k=1; k<TotalSets; k++)
//      {	if (R[k].A[Attr] > maxSet)		maxSet = R[k].A[Attr];
//			if (R[k].A[Attr] < minSet) 	minSet = R[k].A[Attr];
//      }
		part = (maxSet-minSet) / NumberOfIntervals*1.0f;

		for (unsigned int i=0; i<NumberOfIntervals; i++)
			Centers[i]=minSet+(i*part);
		Jroz = EPSILON + 1.0f;
		while ((Jroz >= EPSILON) && (t <= LIMIT_ITTERATION) )
		{  for (unsigned long k=0; k<TotalSets; k++)
				assigned[k]=false;
			t++;
			Jlast = Jcurr;
			for (unsigned int i=0; i<NumberOfIntervals; i++)
				for (unsigned long k=0; k<TotalSets; k++)
				{  UikRec = 0;
					for (unsigned int j=0; j<NumberOfIntervals; j++)
						if (assigned[k] == false)
						{  // if element value = center value
							if (distance(R[k].A[Attr],Centers[i],distType,4)!=0 &&
                                         distance(R[k].A[Attr],Centers[j],distType,4)!=0)
							{  UikRec += pow(distance(R[k].A[Attr],Centers[i],distType,4)/
                             distance(R[k].A[Attr],Centers[j],distType,4),((2/(m-1))*1.0f));
/* correct */	 				  MembershipFunc[i][k] = (UikRec==0)? 1.0: 1/UikRec;
							}
							else
								if (distance(R[k].A[Attr],Centers[i],distType,4)==0)
								{ 	for (unsigned int l=0; l<NumberOfIntervals; l++)
										MembershipFunc[l][k] = 0;
									MembershipFunc[i][k] = 1;
									assigned[k] = true;
								}
						}  // endIf
 				} // k
		  // counting new center for every cluster
		  for (unsigned int i=0; i<NumberOfIntervals; i++)
		  {  pom1 = 0;
			  pom2 = 0;
			  for (unsigned long k=0;k<TotalSets;k++)
			  {  pom1 += pow(MembershipFunc[i][k],m) * R[k].A[Attr];
				  pom2 += pow(MembershipFunc[i][k],m);
			  }
           Centers[i] = (pom2 == 0)? 0: pom1/pom2;
		  }
		  Jcurr = 0;                                           // counting J function
		  for (unsigned int i=0; i<NumberOfIntervals; i++)
		    for (unsigned long k=0; k<TotalSets; k++)
				Jcurr += pow(MembershipFunc[i][k], m) *
                    pow(distance(R[k].A[Attr], Centers[i], distType, 4), 2);
		  if (t>1)  Jroz = fabs(Jcurr - Jlast);
		}
   for (unsigned int i=0;i<NumberOfIntervals;i++)
        delete[] MembershipFunc[i];
	delete[] MembershipFunc;
   return(Centers);
}
