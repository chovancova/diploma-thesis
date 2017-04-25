using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Datasets;

namespace FuzzificationLibrary
{
    class FuzzyClassifierHierarchicalFuzzyEntropy : FuzzyClassifier
    {
        public FuzzyClassifierHierarchicalFuzzyEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
        }

      




        protected override double ComputeTotalFuzzyEntropy(int dimension)
        {



            return 0;
        }

        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious)
        {
            throw new NotImplementedException();
        }

        public override double[][] DeterminationIntervalsLocation(int dimension, int intervals)
        {
            throw new NotImplementedException();
        }

        public override void MembershipFunctionAssignment(int dimension, int interval)
        {
            throw new NotImplementedException();
        }
    }


}
