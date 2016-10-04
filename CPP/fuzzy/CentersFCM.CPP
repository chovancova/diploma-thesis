#include "c:\cpp\fuzzy\fuzzy.cpp"
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
