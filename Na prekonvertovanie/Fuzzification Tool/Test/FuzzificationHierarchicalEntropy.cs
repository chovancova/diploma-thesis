using System;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationHierarchicalEntropy : FuzzificationEntropy
    {
        public const double Theta = 0.01;
        public FuzzificationHierarchicalEntropy(DataSets dataToTransform) : base(dataToTransform){}
        public double Treshold { get; set; }
        public override void LastStepInFuzzification(int dimension, int interval)
        {var MeanFE = TotalEntropy[dimension][interval]/DataToTransform.DatasetSize;}

        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI,
            double totalEntropyIPrevious)
        {
            Treshold = -Math.Log((double) 1/DataToTransform.OutputIntervals)*(Intervals[dimension] - 1)*Theta;
            Console.WriteLine("Treshold = " + Treshold);
            return (totalEntropyI > totalEntropyIPrevious) || (Math.Abs(totalEntropyI) < 0.00000001) ||
                   (totalEntropyI < Treshold);
        }
    }
}