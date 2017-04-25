using System;
using System.Collections.Concurrent;
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
            
            //stredny

            for (int i = 0; i < DataToTransform.DatasetSize; i++)
            {
                x = IntervalCentersAndWidth[dimension][i][3];
                //pravy 
                for (int q = 0; q < interval; q++)
             {
                if (q == 0)
                {
                    c1 = Centers[dimension][0];
                        c2 = Centers[dimension][1];
                       
                    if (x <= c1)
                    {
                        Results[dimension][0][i] = 1;
                    }else if (c1 < x && x <= c2)
                    {
                        Results[dimension][0][i] = (c2 - x)/(c2 - c1);
                    }
                    else
                    {
                        Results[dimension][0][i] = 0;
                    }
                }
                else if (q > 0 && q < interval-1)
                 {
                     c2 = Centers[dimension][q - 1];
                     c3 = Centers[dimension][q];
                     c4 = Centers[dimension][q + 1];

                     if (x <= c2)
                     {
                         Results[dimension][q][i] = 0;
                     }
                     else if (c2 < x && x <= c3)
                     {
                         Results[dimension][q][i] = (x - c2)/(c3 - c2);
                     }
                     else if (c3 < x && x <= c4)
                     {
                         Results[dimension][q][i] = (c4 - x)/(c4 - c3);
                     }
                     else
                     {
                         Results[dimension][q][i] = 0;
                     }


                 }
                 else
                 {

                        c1 = Centers[dimension][interval-2];//predposledny
                        c2 = Centers[dimension][interval-1];//posledny

                        if (x <= c1)
                        {
                            Results[dimension][interval-1][i] = 0;
                        }
                        else if (c1 < x && x <= c2)
                        {
                            Results[dimension][interval-1][i] = (x - c2) / (c2 - c1);
                        }
                        else
                        {
                            Results[dimension][interval-1][i] = 1;
                        }
                    }
          
            } }



            ////for (int i = 0; i < DataToTransform.DatasetSize; i++)
            ////{
            ////    x = IntervalCentersAndWidth[dimension][i][3];

            ////    for (int j = 0; j < interval - 1; j++)
            ////    {
            ////        c4 = Centers[dimension][j + 1];
            ////        c3 = Centers[dimension][j];
            ////        if (x >= c3
            ////            && x <= c4)
            ////        {
            ////            Results[dimension][j][i] = (c4 - x)/(c4 - c3);
            ////            Results[dimension][j + 1][i] = (x - c3)/(c4 - c3);
            ////        }
            ////    }

            ////    c1 = Centers[dimension][0];
            ////    c2 = Centers[dimension][interval - 1];
            ////    if (x < c1)
            ////    {
            ////        Results[dimension][0][i] = 1;
            ////    }
            ////    if (x > c2)
            ////    {
            ////        Results[dimension][interval - 1][i] = 1;
            ////    }
            ////}
        }

        private int count = 0; 
        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI,
            double totalEntropyIPrevious)
        {
            bool secondCondition = true;
            var numberOfElements = CountNumberOfElements(dimension);
            //  if (Intervals[dimension] == numberOfElements) secondCondition =  true; 
            count++;
            return (totalEntropyI <= totalEntropyIPrevious);
        }

        public int CountNumberOfElements(int dimension)
        {
            return 0;
        }

        //public override double[][] DeterminationIntervalsLocation(int dimension, int intervals)
        //{

        //    //Krok 4. Nové centrá I sú urcené pre každý interval ako aritmetický priemer hodnôt prvkov xi, patriacich do týchto intervalov



        //    return null;

        //}





    }
}
