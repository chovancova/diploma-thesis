using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationEntropy : Fuzzification
    {
        private Random _rand;

        public FuzzificationEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
        }

        public override double[] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            return CMeansClustering(intervals, dimension);
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


        // [][0] - closest center
        // [][1] - closest distance
        // [][2] - closest index
        // [][3] - data
        /// <summary>
        ///     [] center of konkretnehoo data bodu
        /// </summary>
        private double[] CMeansClustering(int numberOfIntervals, int dimension)
        {
            var count = 0;
            double[][] centersForDataset;
            bool doesAnyCenterChange;
            var result = new double[numberOfIntervals];
            //Step 2) Set initial centers of clusters.
            var centers = InitializeUniformCenters(dimension, numberOfIntervals);
            do
            {
                //Step 3) Assign cluster label to each element.
                centersForDataset = AssignClusterLabelToEachInterval(numberOfIntervals, dimension,
                    centers);
                //Step 4) Recompute the cluster centers.
                result = RecomputeClusterCenters(numberOfIntervals, centersForDataset);
                //Step 5) Does any center change?
                //If each cluster center is determined appropriately, the
                //recomputed center in Step 4 would not change.
                //If so, stop the determination of interval centers, otherwise go to Step 3.
                doesAnyCenterChange = DoesAnyCenterChange(result, centers);

                if (!doesAnyCenterChange) break;
                count++;
                centers = result;
            } while (count < 500);
            return result;
        }

        //If each cluster center is determined appropriately, the recomputed center in Step 4 would not change.
        //If so, stop the determination of interval centers, otherwise go to Step 3.
        private static bool DoesAnyCenterChange(double[] result, double[] centers)
        {
            //ak bola nejaka zmena v umiestneni - tak false, inak true
            for (var i = 0; i < result.Length; i++)
                if (result[i] != centers[i])
                    return true;

            return false;
        }

        private double[] RecomputeClusterCenters(int numberOfIntervals, double[][] centers)
        {
            var result = new double[numberOfIntervals];
            for (var i = 0; i < numberOfIntervals; i++)
            {
                double Nq = 0;
                double sumNq = 0;
                for (var j = 0; j < DataToTransform.DatasetSize; j++)
                    if (Math.Abs(centers[j][0] - i) < 0.000001)
                    {
                        Nq++;
                        sumNq += centers[j][1];
                    }
                result[i] = sumNq/Nq;
            }
            return result;
        }

        private double[][] AssignClusterLabelToEachInterval(int numberOfIntervals, int dimension, double[] c)
        {
            double[][] centers;
            var closest = 999999999.0;
            var distance = 0.0;
            var closestIndex = 0;
            var data = 0.0;
            centers = new double[DataToTransform.DatasetSize][];

            for (var i = 0; i < DataToTransform.DatasetSize; i++)
            {
                data = DataToTransform.Dataset[i][dimension];
                centers[i] = new double[6];
                closest = 999999999.0;
                closestIndex = 0;

                for (var j = 0; j < numberOfIntervals; j++)
                {
                    distance = ComputeEuclidDistance(data, c[j]);
                    if (distance < closest)
                    {
                        closest = distance;
                        closestIndex = j;
                    }
                }

                // 0 - closest index
                // 1 - data
                centers[i][0] = closestIndex;
                centers[i][1] = data;
            }
            return centers;
        }

        private double[] InitializeUniformCenters(int dimension, int q)
        {
            var c = new double[q];
            var indexData = new int[q];
            var notSame = false;
            double temp;
            for (var i = 1; i <= q; i++)
                c[i - 1] = (double) (i - 1)/(q - 1);

            return c;
        }

        private double ComputeEuclidDistance(double a, double b)
        {
            return Math.Sqrt((a - b)*(a - b));
        }
    }
}