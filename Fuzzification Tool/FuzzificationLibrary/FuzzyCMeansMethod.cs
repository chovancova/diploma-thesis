using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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

        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious)
        {
            return true;
        }

        public override double[][] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            FCMeansClusteringMethod fc = new FCMeansClusteringMethod(this);
            return fc.DeterminationIntervalsLocation(dimension, intervals);

        }

        public override void MembershipFunctionAssignment(int dimension, int interval)
        {
            return;
        }
    }
}
