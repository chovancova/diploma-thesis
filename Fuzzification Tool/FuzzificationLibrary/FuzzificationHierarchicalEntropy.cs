using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Datasets;

namespace FuzzificationLibrary
{
    public class FuzzificationHierarchicalEntropy : FuzzificationEntropy
    {
        public FuzzificationHierarchicalEntropy(DataSets dataToTransform) : base(dataToTransform)
        {
        }


        public override void LastStepInFuzzification(int dimension, int interval)
        {
            double MeanFE = (double)TotalEntropy[dimension][interval] / DataToTransform.DatasetSize;
            //AK fuzzy entropia pre rozhodovaciu oblast je vacsia kao stredna hodnta fuzzy entropie, 
            //oblast sa stane nezavislym pod priestorom a Krok 1 - 7 su vykonavane znova na urcenie
            //rozhodovacich oblasti pre kazdy podpriestor. 
            //inak rozhodovacia oblast bude pridelena oznaceniu triedy
        }
        public double Treshold { get; set; }
        //Percento maximalnej celkovej fuzzy entropie z I-2 intervalov
        public const double Theta = 0.01; 
        protected override bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious)
        {
           Treshold = -Math.Log((double)1/DataToTransform.OutputIntervals)*(Intervals[dimension] - 1)*Theta;
            Console.WriteLine("Treshold = " + Treshold);
            //ak celkova fuzzy entropia I intervalu je viac ako prahov8 hodnota Threshold, tak sa znova rozdeluje
            return ((totalEntropyI > totalEntropyIPrevious) || Math.Abs(totalEntropyI) < 0.00000001 || totalEntropyI < Treshold);
        }
        
    }


}
