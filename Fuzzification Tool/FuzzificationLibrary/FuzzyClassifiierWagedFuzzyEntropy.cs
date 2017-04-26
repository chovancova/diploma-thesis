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
    public class FuzzyClassifiierWagedFuzzyEntropy : FuzzyClassifierFuzzyEntropy
    {
        public FuzzyClassifiierWagedFuzzyEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
        
        }
        
        //public override void MembershipFunctionAssignment(int dimension, int interval)
        //{
        //    double membershipValue = 0;
        //    double c1 = 0.0;
        //    double c2 = 0.0;
        //    double c3 = 0.0;
        //    double c4 = 0.0;
        //    double x = 0.0;
        //    int leftIndex = 0;
        //    int rightIndex = Centers[dimension].Length - 1;

        //    //stredny

        //    //for (int i = 0; i < DataToTransform.DatasetSize; i++)
        //    //{
        //    //    x = IntervalCentersAndWidth[dimension][i][3];
        //    //    //pravy 
        //    //    for (int q = 0; q < interval; q++)
        //    //    {
        //    //        if (q == 0)
        //    //        {
        //    //            c1 = Centers[dimension][0];
        //    //            c2 = Centers[dimension][1];

        //    //            if (x <= c1)
        //    //            {
        //    //                Results[dimension][0][i] = 1;
        //    //            }
        //    //            else if (c1 < x && x <= c2)
        //    //            {
        //    //                Results[dimension][0][i] = (c2 - x) / (c2 - c1);
        //    //            }
        //    //            else
        //    //            {
        //    //                Results[dimension][0][i] = 0;
        //    //            }
        //    //        }
        //    //        else if (q > 0 && q < interval - 1)
        //    //        {
        //    //            c2 = Centers[dimension][q - 1];
        //    //            c3 = Centers[dimension][q];
        //    //            c4 = Centers[dimension][q + 1];

        //    //            if (x <= c2)
        //    //            {
        //    //                Results[dimension][q][i] = 0;
        //    //            }
        //    //            else if (c2 < x && x <= c3)
        //    //            {
        //    //                Results[dimension][q][i] = (x - c2) / (c3 - c2);
        //    //            }
        //    //            else if (c3 < x && x <= c4)
        //    //            {
        //    //                Results[dimension][q][i] = (c4 - x) / (c4 - c3);
        //    //            }
        //    //            else
        //    //            {
        //    //                Results[dimension][q][i] = 0;
        //    //            }


        //    //        }
        //    //        else
        //    //        {

        //    //            c1 = Centers[dimension][interval - 2];//predposledny
        //    //            c2 = Centers[dimension][interval - 1];//posledny

        //    //            if (x <= c1)
        //    //            {
        //    //                Results[dimension][interval - 1][i] = 0;
        //    //            }
        //    //            else if (c1 < x && x <= c2)
        //    //            {
        //    //                Results[dimension][interval - 1][i] = (x - c2) / (c2 - c1);
        //    //            }
        //    //            else
        //    //            {
        //    //                Results[dimension][interval - 1][i] = 1;
        //    //            }
        //    //        }

        //    //    }
        //    //}



        //    for (int i = 0; i < DataToTransform.DatasetSize; i++)
        //    {
        //        x = IntervalCentersAndWidth[dimension][i][3];

        //        for (int j = 0; j < interval - 1; j++)
        //        {
        //            c4 = Centers[dimension][j + 1];
        //            c3 = Centers[dimension][j];
        //            if (x >= c3
        //                && x <= c4)
        //            {
        //                Results[dimension][j][i] = (c4 - x) / (c4 - c3);
        //                Results[dimension][j + 1][i] = (x - c3) / (c4 - c3);
        //            }
        //        }

        //        c1 = Centers[dimension][0];
        //        c2 = Centers[dimension][interval - 1];
        //        if (x < c1)
        //        {
        //            Results[dimension][0][i] = 1;
        //        }
        //        if (x > c2)
        //        {
        //            Results[dimension][interval - 1][i] = 1;
        //        }
        //    }
        //}

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




    }
}
