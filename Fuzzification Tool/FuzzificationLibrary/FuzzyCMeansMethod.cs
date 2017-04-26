using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzyCMeansMethod : Fuzzification
    {
        public FuzzyCMeansMethod(DataSets dataToTransform) : base(dataToTransform)
        {
        }

        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {
            return 0;
        }

        public override double[] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            var fc = new FCMeansClusteringMethod(this);
            return fc.DeterminationIntervalsLocation(dimension, intervals);
        }

        public override void MembershipFunctionAssignment(int dimension, int interval)
        {
        }
    }
}