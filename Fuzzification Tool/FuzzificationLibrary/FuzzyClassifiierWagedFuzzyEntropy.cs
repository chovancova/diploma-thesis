using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Management.Instrumentation;
using System.Text;
using System.Threading.Tasks;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzyClassifiierWagedFuzzyEntropy : FuzzyClassifierFuzzyEntropy
    {
        public FuzzyClassifiierWagedFuzzyEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
        }
        

        public override void MembershipFunctionAssignment(int dimension, int interval)
        {
            double membershipValue = 0;
            double c1 = 0.0;
            double c2 = 0.0;
            double c3 = 0.0;
            double c4 = 0.0;
            double x = 0.0;
            int leftIndex = 0;
            int rightIndex = Centers[dimension].Length - 1;

            for (int i = 0; i < DataToTransform.DatasetSize; i++)
            {
                x = IntervalCentersAndWidth[dimension][i][3];

                for (int j = 0; j < interval - 1; j++)
                {
                    c4 = Centers[dimension][j + 1];
                    c3 = Centers[dimension][j];
                    if (x >= c3
                        && x <= c4)
                    {
                        Results[dimension][j][i] = (c4 - x)/(c4 - c3);
                        Results[dimension][j + 1][i] = (x - c3)/(c4 - c3);
                    }
                }

                c1 = Centers[dimension][0];
                c2 = Centers[dimension][interval - 1];
                if (x < c1)
                {
                    Results[dimension][0][i] = 1;
                }
                if (x > c2)
                {
                    Results[dimension][interval - 1][i] = 1;
                }
            }
        }

        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI,
            double totalEntropyIPrevious)
        {
            bool secondCondition = true;
            var numberOfElements = CountNumberOfElements(dimension);
            //  if (Intervals[dimension] == numberOfElements) secondCondition =  true; 

            return (totalEntropyI <= totalEntropyIPrevious);
        }

        public int CountNumberOfElements(int dimension)
        {
            return 0;
        }

        public override double[][] DeterminationIntervalsLocation(int dimension, int intervals)
        {

            //Krok 4. Nové centrá I sú urcené pre každý interval ako aritmetický priemer hodnôt prvkov xi, patriacich do týchto intervalov





        }





    }
}
