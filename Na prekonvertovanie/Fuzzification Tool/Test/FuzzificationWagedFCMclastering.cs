using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationWagedFcMclastering : FuzzificationWagedEntropy
    {
        private readonly Random _rand;
        public FuzzificationWagedFcMclastering(DataSets dataToTransform) : base(dataToTransform){_rand = new Random();}

        public override double[] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            return FCMeansClustering(intervals, dimension, 2); //m=2 default 
        }

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