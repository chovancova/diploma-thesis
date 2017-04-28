using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationWagedEntropy : FuzzificationEntropy
    {public FuzzificationWagedEntropy(DataSets dataToTransform) : base(dataToTransform){}
        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {
        double totalEntropy = 0;
            var countIntervalsInDimension = Intervals[dimension];
            var countM = new int[countIntervalsInDimension];
            for (var i = 0; i < countIntervalsInDimension; i++)
                countM[i] = 0;
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
         double max = 0;
            var classM = 0;
            double temp = 0;
            for (var i = 0; i < DataToTransform.DatasetSize; i++)
            {
                max = Results[dimension][0][i];
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
                for (var j = 0; j < countIntervalsInDimension; j++)
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++) //OutputIntervals???
                        mu[classM][j][k] += Results[dimension][j][i]*Results[DataToTransform.InputAttributes][k][i];
            }
            double sum = 0;
            for (var i = 0; i < countM.Length; i++)
            {
                sum += countM[i];
            }

            for (var j = 0; j < countIntervalsInDimension; j++)
                for (var k = 0; k < countIntervalsInDimension; k++)
                    for (var l = 0; l < DataToTransform.OutputIntervals; l++)
                        sumMu[j][k] += mu[j][k][l];

            double matchDegreeDj = 0;
            for (var i = 0; i < countIntervalsInDimension; i++)
            {
                double newEntropy = 0;
                for (var j = 0; j < countIntervalsInDimension; j++)
                    for (var k = 0; k < DataToTransform.OutputIntervals; k++)
                    {
                        matchDegreeDj = sumMu[i][j] < 0.000001 ? 0 : mu[i][j][k]/sumMu[i][j]; //proti deleniu nulov
                        if (Math.Abs(matchDegreeDj) > 0.0000001)
                            if (Math.Abs(mu[i][j][k]) > 0.00001)
                                newEntropy -= matchDegreeDj*Math.Log(matchDegreeDj, 2);
                    }
                totalEntropy += newEntropy*countM[i]/DataToTransform.DatasetSize;
            }

            ClassesInInterval[dimension] = countM;
            return totalEntropy;
        }
    }
}