using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationEntropy : Fuzzification
    {
        private readonly CMeansClusteringMethod _cMeansClustering;

        public FuzzificationEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
            _cMeansClustering = new CMeansClusteringMethod(this);
        }

        public override double[] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            return _cMeansClustering.DeterminationIntervalsLocation(dimension, intervals);
        }

        public override void MembershipFunctionAssignment(int dimension, int interval)
        {
            var leftIndex = 0;
            var rightIndex = Centers[dimension].Length - 1;
            for (var i = 0; i < DataToTransform.DatasetSize; i++)
            {
                var x = DataToTransform.Dataset[i][dimension];
                //most left membership function
                var c1 = Centers[dimension][leftIndex];
                var c2 = Centers[dimension][leftIndex + 1];
                double membershipValue = 0;
                if (x <= c1)
                    membershipValue = 1; //alternativa
                else
                    membershipValue = Math.Max(0, 1 - Math.Abs(c1 - x)/Math.Abs(c2 - c1));

                Results[dimension][leftIndex][i] = membershipValue;

                //most right membership function

                var c4 = Centers[dimension][rightIndex];
                var c3 = Centers[dimension][rightIndex - 1];
                if (x <= c4)
                    membershipValue = Math.Max(0, 1 - Math.Abs(c4 - x)/Math.Abs(c4 - c3));
                else if (x > c4)
                    membershipValue = 1; //ALTERNATIVA
                Results[dimension][rightIndex][i] = membershipValue;


                for (var j = 1; j < Centers[dimension].Length - 1; j++)
                {
                    c2 = Centers[dimension][j - 1];
                    c3 = Centers[dimension][j];
                    c4 = Centers[dimension][j + 1];

                    if (x <= c3)
                        membershipValue = Math.Max(0, 1 - Math.Abs(c3 - x)/Math.Abs(c3 - c2));
                    else
                        membershipValue = Math.Max(0, 1 - Math.Abs(c3 - x)/Math.Abs(c4 - c3));
                    Results[dimension][j][i] = membershipValue;
                }
            }
        }

        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {
            double totalEntropy = 0;
            var intervals = Intervals[dimension];

            var classM = 0;

            var countM = new int[intervals];
            for (var i = 0; i < intervals; i++)
                countM[i] = 0;
            //---------------------------II.C.----STEP 1 - SET UNIVERSAL SET X -------------------------------------------
            var mu = new double[intervals][][];
            var sumMu = new double[intervals][];
            for (var i = 0; i < intervals; i++)
            {
                mu[i] = new double[intervals][];
                sumMu[i] = new double[intervals];
                for (var j = 0; j < intervals; j++)
                {
                    mu[i][j] = new double[DataToTransform.OutputIntervals];
                    sumMu[i][j] = 0;
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++)
                        mu[i][j][k] = 0;
                }
            }
            //---------------------------II.C.----STEP 2 - SET FUZZY SET A CONTAINS K ELEMENTS ---------------------------
            //---------------------------II.C.----STEP 3 - SET ARRAY REPRESENTING M CLASSES INTO WHICH THE N ELEMENTS ARE DEVIDED -------

            for (var i = 0; i < DataToTransform.DatasetSize; i++)
            {
                var max = Results[dimension][0][i];
                //---------------------------II.C.----STEP 4 - SET SCJ AS SET OF ELEMENTS OF CLASS J ON X -------------------------------------------
                //pre vsetky intervaly
                for (var j = 0; j < intervals; j++)
                {
                    var temp = Results[dimension][j][i];
                    if (max <= temp)
                    {
                        classM = j;
                        max = temp;
                    }
                }
                countM[classM]++;
                //---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
                for (var j = 0; j < intervals; j++)
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++)
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
            // Console.WriteLine("II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ - sum mu ");
            for (var j = 0; j < intervals; j++)
                for (var k = 0; k < intervals; k++)
                    for (var l = 0; l < DataToTransform.OutputIntervals; l++)
                        sumMu[j][k] += mu[j][k][l];


            //---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
            double matchDegreeDj = 0;
            for (var i = 0; i < intervals; i++)
            {
                double newEntropy = 0;
                for (var j = 0; j < intervals; j++)
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++)
                    {
                        //---------------------------II.C.----STEP 5 - COMPUTE MATCH DEGREE DJ -------------------------------------------
                        matchDegreeDj = sumMu[i][j] < 0.000001 ? 0 : mu[i][j][k]/sumMu[i][j]; //proti deleniu nulov
                        //---------------------------II.C.----STEP 6 - COMPUTE FUZZY ENTROPY FECJ A  -------------------------------------------
                        //Console.WriteLine(matchDegreeDj);
                        if (Math.Abs(matchDegreeDj) > 0.0000001)
                            if (Math.Abs(mu[i][j][k]) > 0.00001)
                                newEntropy -= matchDegreeDj*Math.Log(matchDegreeDj, 2);
                    }
                //---------------------------II.C.----STEP 7 - COMPUTE FUZZY ENTORPY FEA ON X -------------------------------------------
                //Console.WriteLine("Entropy on FEA - " + newEntropy * countM[i] / DataToTransform.DatasetSize);

                totalEntropy += newEntropy;
            }
            // Console.WriteLine();
            // Console.WriteLine("Total Entropy - "+ totalEntropy);
            // Console.WriteLine();
            ClassesInInterval[dimension] = countM;
            return totalEntropy;
        }
    }
}