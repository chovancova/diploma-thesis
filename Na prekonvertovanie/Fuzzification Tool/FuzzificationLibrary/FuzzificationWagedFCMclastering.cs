using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationWagedFcMclastering : Fuzzification
    {
        private readonly Random _rand;

        public FuzzificationWagedFcMclastering(DataSets dataToTransform) : base(dataToTransform)
        {
            _rand = new Random();
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
                        classM = j; //todo debugg
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

            return totalEntropy;
        }

        /// <summary>
        ///     Membership function for dimension -
        /// </summary>
        public override double[] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            return FCMeansClustering(intervals, dimension, 2); //m=2 default 
        }

        /// <summary>
        ///     Return Centers in datasets
        /// </summary>
        /// <param name="numberOfIntervals"></param>
        /// <param name="dimension"></param>
        /// <param name="m"></param>
        /// <returns></returns>
        private double[] FCMeansClustering(int numberOfIntervals, int dimension, int m = 2)
        {
            //Krok 1.Náhodne sa inicializuje kluster hodnoty príslušnosti, μij.
            Centers[dimension] = InitializeRandomCenters(dimension, numberOfIntervals);

            for (var i = 0; i < DataToTransform.DatasetSize; i++)
                for (var j = 0; j < numberOfIntervals; j++)
                    Results[dimension][j][i] = Centers[dimension][j];

            do
            {
                // Krok 2. Vypočítanie centier klastra c_j =  sum{ i = 1}^ D \mu_{ ij}^ m * x_i   deleno sum{ i = 1}^ D \mu_{ ij}^ m
                var mu = new double[numberOfIntervals];
                double sum1 = 0;
                double sum2 = 0;
                for (var j = 0; j < numberOfIntervals; j++)
                {
                    for (var i = 0; i < DataToTransform.DatasetSize; i++)
                    {
                        sum1 += Math.Pow(Results[dimension][j][i], m)*DataToTransform.Dataset[i][dimension];
                        sum2 += Math.Pow(Results[dimension][j][i], m);
                    }
                    mu[j] = sum1/sum2;
                }

                // Krok 3.Aktualizácia μij podla nasledujúceho vztahu μij = 1 / ( suma (od k = 1 do N) (absolutna hodnota (xi-cj) / absol(xi-ck)) a to cele na 2/(m1) )
                var sum3 = new double[numberOfIntervals];
                for (var j = 0; j < numberOfIntervals; j++)
                    for (var k = 0; k < numberOfIntervals; k++)
                        for (var i = 0; i < DataToTransform.DatasetSize; i++)
                            sum3[j] += Math.Abs(DataToTransform.Dataset[i][dimension] - Centers[dimension][j])/
                                       Math.Abs(DataToTransform.Dataset[i][dimension] - Centers[dimension][k]);
                for (var j = 0; j < numberOfIntervals; j++)
                    for (var i = 0; i < DataToTransform.DatasetSize; i++)
                        if (sum3[j] != 0)
                            Results[dimension][j][i] = Math.Pow(1/sum3[j], 2/(m - 1));
                // Krok 4.Vypocítanie účelovej funkcie Jm.
                // Jm = suma (od i=1 do Datovych bodov) suma (od j = 1 do N pocet klastrov) μij ^ m absolutan hodnota (xi - cj)^2
                var Jm = new double[m];
                for (var k = 0; k < m; k++)
                    for (var j = 0; j < numberOfIntervals; j++)
                        for (var i = 0; i < DataToTransform.DatasetSize; i++)
                            Jm[k] += Math.Pow(Results[dimension][j][i], m)*
                                     Math.Pow(
                                         Math.Abs(DataToTransform.Dataset[i][dimension] - Centers[dimension][j]),
                                         2);

                //Krok 5. Opakovanie krokov 2-4 až pokým Jm sa zlepší o menej než stanovená minimálna
                // prahová hodnota alebo po uplynutí urcitého maximálneho poctu iterácií.
            } while (false);

            return Centers[dimension];
        }

        private double[] InitializeRandomCenters(int dimension, int q)
        {
            var c = new double[q];
            var indexData = new int[q];
            var notSame = false;
            for (var i = 0; i < q; i++)
                do
                {
                    indexData[i] = _rand.Next(DataToTransform.DatasetSize);
                    c[i] = DataToTransform.Dataset[indexData[i]][dimension];
                    notSame = false;
                    for (var j = 0; j < i; j++)
                        if (Math.Abs(c[i] - c[j]) < 0.00000001)
                            notSame = true;
                } while (notSame);

            Array.Sort(c);
            return c;
        }
    }
}