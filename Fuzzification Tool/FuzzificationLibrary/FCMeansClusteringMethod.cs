using System;

namespace FuzzificationLibrary
{
    public class FCMeansClusteringMethod 
    {
        private Fuzzification _fc;
        private Random _rand;

        public FCMeansClusteringMethod(Fuzzification fc)
        {
            _rand = new Random();
            _fc = fc;
        }

        public double[] DeterminationIntervalsLocation(int dimension, int intervals, int m = 2)
        {
            return FCMeansClustering(intervals, dimension, m);
        }


        /// <summary>
        /// Return Centers in datasets
        /// </summary>
        /// <param name="numberOfIntervals"></param>
        /// <param name="dimension"></param>
        /// <param name="m"></param>
        /// <returns></returns>
        private double[] FCMeansClustering(int numberOfIntervals, int dimension, int m = 2)
        {
            _rand = new Random();
             
            //Krok 1.Náhodne sa inicializuje kluster hodnoty príslušnosti, μij.
            _fc.Centers[dimension] = InitializeRandomCenters(dimension, numberOfIntervals);
            
            for (int i = 0; i < _fc.DataToTransform.DatasetSize; i++)
            {
                for (int j = 0; j < numberOfIntervals; j++)
                {
                    _fc.Results[dimension][j][i] = _fc.Centers[dimension][j];
                }
            }

            do
            {
                // Krok 2. Vypočítanie centier klastra c_j =  sum{ i = 1}^ D \mu_{ ij}^ m * x_i   deleno sum{ i = 1}^ D \mu_{ ij}^ m
                double[] mu = new double[numberOfIntervals];
                double sum1 = 0;
                double sum2 = 0;
                for (int j = 0; j < numberOfIntervals; j++)
                {
                    for (int i = 0; i < _fc.DataToTransform.DatasetSize; i++)
                    {
                        sum1 += Math.Pow(_fc.Results[dimension][j][i], m)*_fc.DataToTransform.Dataset[i][dimension];
                        sum2 += Math.Pow(_fc.Results[dimension][j][i], m);
                    }
                    mu[j] = sum1/sum2;
                }

                // Krok 3.Aktualizácia μij podla nasledujúceho vztahu μij = 1 / ( suma (od k = 1 do N) (absolutna hodnota (xi-cj) / absol(xi-ck)) a to cele na 2/(m1) )
                double[] sum3 = new double[numberOfIntervals];
                for (int j = 0; j < numberOfIntervals; j++)
                {
                    for (int k = 0; k < numberOfIntervals; k++)
                    {
                        for (int i = 0; i < _fc.DataToTransform.DatasetSize; i++)
                        {
                            sum3[j] += Math.Abs(_fc.DataToTransform.Dataset[i][dimension] - _fc.Centers[dimension][j])/
                                       Math.Abs(_fc.DataToTransform.Dataset[i][dimension] - _fc.Centers[dimension][k]);
                        }
                    }
                }
                for (int j = 0; j < numberOfIntervals; j++)
                {
                    for (int i = 0; i < _fc.DataToTransform.DatasetSize; i++)
                    {
                        if (sum3[j] != 0)
                        {
                            _fc.Results[dimension][j][i] = Math.Pow(1/sum3[j], (2/(m - 1)));
                        }
                    }
                }
                // Krok 4.Vypocítanie účelovej funkcie Jm.
                // Jm = suma (od i=1 do Datovych bodov) suma (od j = 1 do N pocet klastrov) μij ^ m absolutan hodnota (xi - cj)^2
                double[] Jm = new double[m];
                for (int k = 0; k < m; k++)
                {
                    for (int j = 0; j < numberOfIntervals; j++)
                    {
                        for (int i = 0; i < _fc.DataToTransform.DatasetSize; i++)
                        {
                            Jm[k] += Math.Pow(_fc.Results[dimension][j][i], m)*
                                     Math.Pow(Math.Abs(_fc.DataToTransform.Dataset[i][dimension] - _fc.Centers[dimension][j]),2);
                        }
                    }
                }

                //Krok 5. Opakovanie krokov 2-4 až pokým Jm sa zlepší o menej než stanovená minimálna
                // prahová hodnota alebo po uplynutí urcitého maximálneho poctu iterácií.
            } while (false);

            return _fc.Centers[dimension];
        }

        private double[] InitializeRandomCenters(int dimension, int q)
        {
            var c = new double[q];
            var indexData = new int[q];
            var notSame = false;
            for (var i = 0; i < q; i++)
                do
                {
                    indexData[i] = _rand.Next(_fc.DataToTransform.DatasetSize);
                    c[i] = _fc.DataToTransform.Dataset[indexData[i]][dimension];
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