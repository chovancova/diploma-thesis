using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationWagedEntropy : FuzzificationEntropy
    {
        public FuzzificationWagedEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
        }

        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {
            //1) Let X = {r1, ... , rn} be a universal set with elements ri distributed in pattern space where i = 1..n. 
            //2) Let A be a fuzzy set defined on a interval of pattern space which kontains k elements (k < n). 

            double totalEntropy = 0;
            var countIntervalsInDimension = Intervals[dimension];
            var countM = new int[countIntervalsInDimension];
            for (var i = 0; i < countIntervalsInDimension; i++)
                countM[i] = 0;
            //---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
            var mu = new double[countIntervalsInDimension][][];
            var sumMu = new double[countIntervalsInDimension][];
            for (var i = 0; i < countIntervalsInDimension; i++)
            {
                mu[i] = new double[countIntervalsInDimension][];
                sumMu[i] = new double[countIntervalsInDimension];
                for (var j = 0; j < countIntervalsInDimension; j++)
                {
                    mu[i][j] = new double[DataToTransform.OutputIntervals];
                    sumMu[i][j] = 0;
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++)
                        mu[i][j][k] = 0;
                }
            }
            //---------------------------II.C.----STEP 2 - SET FUZZY SET A CONTAINS K ELEMENTS ---------------------------
            //---------------------------II.C.----STEP 3 - SET ARRAY REPRESENTING M CLASSES INTO WHICH THE N ELEMENTS ARE DEVIDED -------
            double max = 0;
            var classM = 0;
            double temp = 0;
            for (var i = 0; i < DataToTransform.DatasetSize; i++)
            {
                max = Results[dimension][0][i];
                //---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
                // Console.WriteLine("II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X ");
                for (var j = 0; j < countIntervalsInDimension; j++)
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
                for (var j = 0; j < countIntervalsInDimension; j++)
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++) //OutputIntervals???
                        mu[classM][j][k] += Results[dimension][j][i]*Results[DataToTransform.InputAttributes][k][i];
                //toto priradi to kde patri do akej triedy
            }
            Console.WriteLine("number of class in intervals ");
            double sum = 0;
            for (var i = 0; i < countM.Length; i++)
            {
                Console.WriteLine(i + "\t (" + countM[i] + ")");
                sum += countM[i];
            }
            Console.WriteLine("Sum: " + sum);
            Console.WriteLine();

            for (var j = 0; j < countIntervalsInDimension; j++)
                for (var k = 0; k < countIntervalsInDimension; k++)
                    for (var l = 0; l < DataToTransform.OutputIntervals; l++)
                        sumMu[j][k] += mu[j][k][l];


            //---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
            //---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
            //Console.WriteLine("II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A ");
            //  Fuzzy Entropy Calculation
            // The fuzzy entropy FE on the universal uset X for the elements within an interval 
            double matchDegreeDj = 0;
            for (var i = 0; i < countIntervalsInDimension; i++)
            {
                double newEntropy = 0;
                for (var j = 0; j < countIntervalsInDimension; j++)
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++)
                    {
                        //---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
                        matchDegreeDj = sumMu[i][j] < 0.000001 ? 0 : mu[i][j][k]/sumMu[i][j]; //proti deleniu nulov
                        //---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------

                        if (Math.Abs(matchDegreeDj) > 0.0000001)
                            if (Math.Abs(mu[i][j][k]) > 0.00001)
                                newEntropy -= matchDegreeDj*Math.Log(matchDegreeDj, 2);
                    }
                //---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
                totalEntropy += newEntropy*countM[i]/DataToTransform.DatasetSize;
            }

            ClassesInInterval[dimension] = countM;
            return totalEntropy;
        }
    }
}