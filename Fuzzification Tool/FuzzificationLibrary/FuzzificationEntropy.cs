using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationEntropy : Fuzzification
    {
        private readonly CMeansClusteringMethod CMeansClustering;

        public FuzzificationEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
            CMeansClustering = new CMeansClusteringMethod(this);
        }

        public override double[][] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            double[][] temp = CMeansClustering.DeterminationIntervalsLocation(dimension, intervals);

           Centers =  CMeansClustering.ReturnCenters();
            return temp;
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
            int rightIndex = Centers[dimension].Length -1;

            for (int i = 0; i < DataToTransform.DatasetSize; i++)
            {
                x = DataToTransform.Dataset[i][dimension];
                //most left membership function
                c1 = Centers[dimension][leftIndex];
                c2 = Centers[dimension][leftIndex + 1];
                if (x <= c1)
                {
                    membershipValue = 1; //alternativa
                  //  membershipValue = (c1 + x)/2*c1;
                }
                else
                {
                    membershipValue = Math.Max(0, (1 - Math.Abs(c1 - x)/Math.Abs(c2 - c1)));
                }

                Results[dimension][leftIndex][i] = membershipValue;

                //most right membership function

                c4 = Centers[dimension][rightIndex];
                c3 = Centers[dimension][rightIndex - 1];
                if (x <= c4)
                {
                    membershipValue = Math.Max(0, (1 - (Math.Abs(c4 - x)/Math.Abs(c4 - c3))));
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
                        membershipValue = Math.Max(0, (1 - (Math.Abs(c3 - x)/Math.Abs(c3 - c2))));
                    }
                    else
                    {
                        membershipValue = Math.Max(0, (1 - (Math.Abs(c3 - x)/Math.Abs(c4 - c3))));
                    }
                    Results[dimension][j][i] = membershipValue;

                }
            }
            }


        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {
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

           // Console.WriteLine("II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ - sum mu ");
            for (int j = 0; j < countIntervalsInDimension; j++)
                for (int k = 0; k < countIntervalsInDimension; k++)
                    for (int l = 0; l < DataToTransform.OutputIntervals; l++)
                    {
                        sumMu[j][k] += mu[j][k][l];
                    }


            //---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
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
                        //Console.WriteLine(matchDegreeDj);
                        if (Math.Abs(matchDegreeDj) > 0.0000001)
                        {
                             if ((Math.Abs(mu[i][j][k]) > 0.00001))
                            newEntropy -= matchDegreeDj * Math.Log(matchDegreeDj, 2);
                        }
                    }
                }
                //---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
                //Console.WriteLine("Entropy on FEA - " + newEntropy * countM[i] / DataToTransform.DatasetSize);

                totalEntropy += newEntropy;
            }
           // Console.WriteLine();
           // Console.WriteLine("Total Entropy - "+ totalEntropy);
           // Console.WriteLine();
            return totalEntropy;
        }


        /// <summary>
        /// Does the total fuzzy entropy decrease?
        /// If the total fuzzy entropy of I intervals is less than that
        /// of I - 1 intervals. return true else false;
        /// </summary>
        /// <param name="dimension"></param>
        /// <param name="totalEntropyI"></param>
        /// <param name="totalEntropyIPrevious"></param>
        /// <returns></returns>
        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious)
        {
            return (totalEntropyI > totalEntropyIPrevious);
        }





        //protected override double ComputeTotalFuzzyEntropy(int dimension, int interval)
        //{
        //   double totalEntropyI=0;
        //    double[] X = DataToTransform.Dataset[dimension];
        //    double[] C = Centers[dimension];
        //    double[][] SC = IntervalCentersAndWidth[dimension];
        //    int countClass = DataToTransform.OutputIntervals;
        //    //subsset with only j-th class form dataset
        //    double[] SCj = new double[countClass]; 
        //    double[] Dj = new double[interval];//membership degree


        //    int countClasters = Centers[dimension].Length;

        //    double temp1, temp2, classj;
        //    //for all classer
        //    for (int classJ = 0; classJ < countClass; classJ++)
        //    {
        //        SCj[classJ] = ComputeSubsetClass(classJ, SC, dimension);
        //    }

        //    for (int i = 0; i < interval; i++)
        //    {
        //        Dj[i] = 0;
        //        totalEntropyI = 1; 

        //        //for (int j = 0; j < UPPER; j++)
        //        {

        //        }



        //    }



        //    return totalEntropyI;
        //}

        private double ComputeSubsetClass(int classJ, double[][] SC, int dimension)
        {
            double SCj = 0;
            int temp = 0; 
            for (int i = 0; i < SC.Length; i++)
            {
                temp = (int)SC[i][2];
                if (temp == classJ)
                {
                    SCj += Results[i][dimension][temp];
                }
            }

            return SCj;
        }
        
        private double ComputeSetClass(int classJ, double[][] SC)
        {
            double SCj = 0;
            int temp = 0;
            for (int i = 0; i < SC.Length; i++)
            {
               // temp = (int)SC[i][2];
                if (DataToTransform.OutputAttributes == classJ)
                {
                    SCj += SC[i][3];
                }
            }

            return SCj;
        }

    }
}