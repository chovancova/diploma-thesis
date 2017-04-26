using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Management.Instrumentation;
using System.Text;
using System.Threading.Tasks;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationWagedEntropy : FuzzificationEntropy
    {
        public FuzzificationWagedEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
        
        }
       
        private int count = 0; 
        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI,
            double totalEntropyIPrevious)
        {
            return (totalEntropyI > totalEntropyIPrevious);
        }

        public int CountNumberOfElements(int dimension)
        {
            return 0;
        }

        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {
            //1) Let X = {r1, ... , rn} be a universal set with elements ri distributed in pattern space where i = 1..n. 
            //2) Let A be a fuzzy set defined on a interval of pattern space which kontains k elements (k < n). 

            double totalEntropy = 0;
            int countIntervalsInDimension = Intervals[dimension];
            int[] countM = new int[countIntervalsInDimension];
            for (int i = 0; i < countIntervalsInDimension; i++)
            {
                countM[i] = 0;
            }
            //---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
            double[][][] mu = new double[countIntervalsInDimension][][];
            double[][] sumMu = new double[countIntervalsInDimension][];
            for (int i = 0; i < countIntervalsInDimension; i++)
            {
                mu[i] = new double[countIntervalsInDimension][];
                sumMu[i] = new double[countIntervalsInDimension];
                for (int j = 0; j < countIntervalsInDimension; j++)
                {
                    mu[i][j] = new double[DataToTransform.OutputIntervals];
                    sumMu[i][j] = 0;
                    for (int k = 0; k < DataToTransform.OutputIntervals; k++)
                    {
                        mu[i][j][k] = 0;
                    }
                }
            }
            //---------------------------II.C.----STEP 2 - SET FUZZY SET A CONTAINS K ELEMENTS ---------------------------
            //---------------------------II.C.----STEP 3 - SET ARRAY REPRESENTING M CLASSES INTO WHICH THE N ELEMENTS ARE DEVIDED -------
            double max = 0;
            int classM = 0;
            double temp = 0;
            for (int i = 0; i < DataToTransform.DatasetSize; i++)
            {
                max = Results[dimension][0][i];
                //---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
                // Console.WriteLine("II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X ");
                for (int j = 0; j < countIntervalsInDimension; j++)
                {
                    temp = Results[dimension][j][i];
                    if (max <= temp)
                    {
                        classM = j;
                        max = temp;
                    }
                }
                countM[classM]++;
                //---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
                for (int j = 0; j < countIntervalsInDimension; j++)
                    for (int k = 0; k < DataToTransform.OutputIntervals; k++) //OutputIntervals???
                    {
                        mu[classM][j][k] += Results[dimension][j][i] * Results[DataToTransform.InputAttributes][k][i]; //toto priradi to kde patri do akej triedy
                    }
            }

            for (int j = 0; j < countIntervalsInDimension; j++)
                for (int k = 0; k < countIntervalsInDimension; k++)
                    for (int l = 0; l < DataToTransform.OutputIntervals; l++)
                    {
                        sumMu[j][k] += mu[j][k][l];
                    }


            //---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
            //---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
            //Console.WriteLine("II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A ");
            //  Fuzzy Entropy Calculation
            // The fuzzy entropy FE on the universal uset X for the elements within an interval 
            double matchDegreeDj = 0;
            for (int i = 0; i < countIntervalsInDimension; i++)
            {
                double newEntropy = 0;
                for (int j = 0; j < countIntervalsInDimension; j++)
                {
                    for (int k = 0; k < DataToTransform.OutputIntervals; k++)
                    {
                        //---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
                        matchDegreeDj = (sumMu[i][j] < 0.000001) ? 0 : (mu[i][j][k] / sumMu[i][j]); //proti deleniu nulov
                        //---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
                                                                                                  
                        if (Math.Abs(matchDegreeDj) > 0.0000001)
                        {
                            if ((Math.Abs(mu[i][j][k]) > 0.00001))
                                newEntropy -= matchDegreeDj * Math.Log(matchDegreeDj, 2);
                        }
                    }
                }
                //---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
               totalEntropy += newEntropy * countM[i] / DataToTransform.DatasetSize;
                
            }
         return totalEntropy;
        }




        public override void MembershipFunctionAssignment(int dimension, int interval)
        {
            double membershipValue = 0;
            double c1 = 0.0;
            double c2 = 0.0;
            double c3 = 0.0;
            double c4 = 0.0;
            double x = 0.0;
            int leftIndex = 0;
            int rightIndex = Centers[dimension].Length - 1;

            for (int i = 0; i < DataToTransform.DatasetSize; i++)
            {
                x = DataToTransform.Dataset[i][dimension];
                //most left membership function
                c1 = Centers[dimension][leftIndex];
                c2 = Centers[dimension][leftIndex + 1];
                if (x <= c1)
                {
                    membershipValue = 1; //alternativa
                    //membershipValue = (c1 + x)/2*c1;
                }
                else
                {
                    membershipValue = Math.Max(0, (1 - Math.Abs(c1 - x) / Math.Abs(c2 - c1)));
                }

                Results[dimension][leftIndex][i] = membershipValue;

                //most right membership function

                c4 = Centers[dimension][rightIndex];
                c3 = Centers[dimension][rightIndex - 1];
                if (x <= c4)
                {
                    membershipValue = Math.Max(0, (1 - (Math.Abs(c4 - x) / Math.Abs(c4 - c3))));
                }
                else if (x > c4)
                {
                    membershipValue = 1; //ALTERNATIVA
                    //membershipValue = (2 - x - c4)/(2 - (1 - c4));
                }
                Results[dimension][rightIndex][i] = membershipValue;


                for (int j = 1; j < Centers[dimension].Length - 1; j++)
                {
                    c2 = Centers[dimension][j - 1];
                    c3 = Centers[dimension][j];
                    c4 = Centers[dimension][j + 1];

                    if (x <= c3)
                    {
                        membershipValue = Math.Max(0, (1 - (Math.Abs(c3 - x) / Math.Abs(c3 - c2))));
                    }
                    else
                    {
                        membershipValue = Math.Max(0, (1 - (Math.Abs(c3 - x) / Math.Abs(c4 - c3))));
                    }
                    Results[dimension][j][i] = membershipValue;

                }
            }
        }


    }
}
