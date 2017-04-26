using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationOnlyFCM : Fuzzification
    {
        private readonly FCMeansClusteringMethod _fcm;

        /// <summary>
        /// </summary>
        /// <param name="dataToTransform"></param>
        /// <param name="numberOfInputIntervals">number of intervals for input and output intervals in dataset. </param>
        public FuzzificationOnlyFCM(DataSets dataToTransform, int[] numberOfInputIntervals) : base(dataToTransform)
        {
            _fcm = new FCMeansClusteringMethod(this);
            Intervals = numberOfInputIntervals;
        }

        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {
            return 0;
        }

        public override double[] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            return _fcm.DeterminationIntervalsLocation(dimension, intervals);
        }

        public override void MembershipFunctionAssignment(int dimension, int interval)
        {
        }

        public override void LastStepInFuzzification(int dimension, int interval)
        {
            //do nothing
        }

        public override int SetInitialNumberOfIntervals(int dimension)
        {
            return Intervals[dimension];
        }

        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI,
            double totalEntropyIPrevious)
        {
            return true;
        }
    }
}