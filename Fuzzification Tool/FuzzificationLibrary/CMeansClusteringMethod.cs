using System;

namespace FuzzificationLibrary
{
    public class CMeansClusteringMethod
    {
        private FuzzyClassifier _fc;
        private Random _rand;

        public CMeansClusteringMethod(FuzzyClassifier fc)
        {
            _rand = new Random();
            _fc = fc;
        }

        public double[][] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            return CMeansClustering(intervals, dimension);
        }
        /// <summary>
        /// [] center of konkretnehoo data bodu
        // [][0] - closest center
        // [][1] - closest distance
        // [][2] - closest index
        // [][3] - data
        // [][4] - left center 
        // [][5] - right center
        /// </summary>
        private double[][] CMeansClustering(int numberOfIntervals, int dimension)
        {
            int count = 0; 
            _rand = new Random();
            double[][] centers;
            bool doesAnyCenterChange;
            double[] resultPrevius = null;
            //Step 2) Set initial centers of clusters.
            _fc.Centers[dimension] = InitializeUniformCenters(dimension, numberOfIntervals);
            do
            {
                //Step 3) Assign cluster label to each element.
                centers = AssignClusterLabelToEachInterval(numberOfIntervals, dimension,
                    _fc.Centers[dimension]);
                //Step 4) Recompute the cluster centers.
                var result = RecomputeClusterCenters(numberOfIntervals, centers);
                //Step 5) Does any center change?
                //If each cluster center is determined appropriately, the
                //recomputed center in Step 4 would not change.
                //If so, stop the determination of interval centers, otherwise go to Step 3.
                doesAnyCenterChange = DoesAnyCenterChange(result, centers);
                if (!doesAnyCenterChange) break;
                count++;
            } while (count ==500);

            return centers;
        }

        public double[][] ReturnCenters()
        {
            return _fc.Centers;
        }

        //If each cluster center is determined appropriately, the recomputed center in Step 4 would not change.
        //If so, stop the determination of interval centers, otherwise go to Step 3.
        private static bool DoesAnyCenterChange(double[] result, double[][] centers )
        {
            //ak bola nejaka zmena v umiestneni - tak false, inak true
            for (var i = 0; i < result.Length; i++)
                if (Math.Abs(result[i] - centers[i][0]) < 0.0000001)
                    return false;

            return true; 
        }

        private double[] RecomputeClusterCenters(int numberOfIntervals, double[][] centers)
        {
            var result = new double[_fc.DataToTransform.DatasetSize];
            for (var i = 0; i < numberOfIntervals; i++)
            {
                double Nq = 0;
                double sumNq = 0;
                for (var j = 0; j < _fc.DataToTransform.DatasetSize; j++)
                    if (Math.Abs(centers[j][2] - i) < 0.000001)
                    {
                        Nq++;
                        sumNq += centers[j][3];
                    }
               result[i] = (double) sumNq/Nq;
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
            centers = new double[_fc.DataToTransform.DatasetSize][];

            for (var i = 0; i < _fc.DataToTransform.DatasetSize; i++)
            {
                data = _fc.DataToTransform.Dataset[i][dimension];
                centers[i] = new double[6];
                closest = 999999999.0;
                distance = 0.0;
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
                // 0 - closest center
                // 1 - closest distance
                // 2 - closest index
                // 3 - data
                // 4 - left center 
                // 5 - right center
                centers[i][0] = c[closestIndex];
                centers[i][1] = closest;
                centers[i][2] = closestIndex;
                centers[i][3] = data;
                centers[i][4] = closestIndex == 0 ? c[closestIndex] : c[closestIndex - 1];
                centers[i][5] = closestIndex == numberOfIntervals - 1 ? c[closestIndex] : c[closestIndex + 1];
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
               c[i-1] = (double)(i - 1) / (q - 1);
          
            return c;
        }

        private double ComputeEuclidDistance(double a, double b)
        {
            return Math.Sqrt((a - b)*(a - b));
        }
    }
}