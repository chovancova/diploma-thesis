using System;
using System.IO;

namespace Datasets
{
    public abstract class DataSets
    {
        protected DataSets(int datasetSize, int inputAttributes, int outputIntervals, string filename)
        {
            DatasetSize = datasetSize;Attributes = inputAttributes + 1;InputAttributes = inputAttributes;OutputAttributes = 1;OutputIntervals = outputIntervals;
            Filename = filename;InitialError = -1;Dataset = new double[datasetSize][];
            for (var i = 0; i < datasetSize; i++)
                Dataset[i] = new double[Attributes];

            LingvisticAttribute = new int[Attributes];
            for (var i = 0; i < LingvisticAttribute.Length; i++)
                LingvisticAttribute[i] = 0;
            LingvisticAttribute[inputAttributes] = outputIntervals;
        }

        public int DatasetSize { get; protected set; }public int Attributes { get; protected set; }public int InputAttributes { get; protected set; }public int OutputAttributes { get; protected set; }public int OutputIntervals { get; protected set; }public string Filename { get; protected set; }
        public double[][] Dataset { get; set; }public int[] LingvisticAttribute { get; set; }public double InitialError { get; set; }public void ClearDataset()
        {
            DatasetSize = 0;InputAttributes = 0;OutputAttributes = 0;OutputIntervals = 0;InitialError = -1;Filename = "text.txt";Dataset = null;LingvisticAttribute = null;
        }
        public abstract int InitializeDataset();
        public void NormalizeDataset()
        {
            var min = new double[InputAttributes];
            var max = new double[InputAttributes];

            for (var i = 0; i < InputAttributes; i++)
                if (LingvisticAttribute[i] == 0)
                {
                    min[i] = Dataset[0][i];
                    max[i] = Dataset[0][i];
                    for (var k = 1; k < DatasetSize; k++)
                    {
                        if (Dataset[k][i] < min[i]) min[i] = Dataset[k][i];
                        if (Dataset[k][i] > max[i]) max[i] = Dataset[k][i];
                    }
                    for (var k = 0; k < DatasetSize; k++)
                        Dataset[k][i] = (Dataset[k][i] - min[i])/(max[i] - min[i]);
                }
        }

        
        public double ComputeInitialError()
        {
            InitialError = 0.0;int max;
                var classes = new int[OutputIntervals];

                for (var i = 0; i < OutputIntervals; i++)
                    classes[i] = 0;

                for (var x = 0; x < DatasetSize; x++)
                    classes[Convert.ToInt32(Dataset[x][InputAttributes])]++;

                max = classes[0];
                for (var i = 0; i < OutputIntervals; i++)
                    if (classes[i] > max)
                        max = classes[i];
                InitialError = 1 - max*1.0f/DatasetSize;
          
            return InitialError;
        }

        public override string ToString()
        {
            var basic = "Dataset Size: \t\t\t\t" + DatasetSize + "\n" +
                        "Attributes: \t\t\t\t\t" + Attributes + "\n" +
                        "Input Attributes: \t\t" + InputAttributes + "\n" +
                        "Output Attributes: \t\t" + OutputAttributes + "\n" +
                        "Output Intervals: \t\t" + OutputIntervals + "\n" +
                        "Initial Error: \t\t\t\t" + InitialError + "\n" +
                        "Filename: \t\t\t\t\t\t" + Filename + "\n";

            basic += "LingvisticAttribute: \t";
            for (var i = 0; i < LingvisticAttribute.Length; i++)
                basic += LingvisticAttribute[i] + "\t";
            basic += "\n";


            basic += "Dataset:\n";
            foreach (var x in Dataset)
            {
                foreach (var y in x)
                    basic += Math.Round(y, 4).ToString("0.0000") + "\t";
                basic += "\n";
            }
            return basic;
        }

        public void WriteToFile(string filename = "dataset.txt")
        {
            using (var w = new StreamWriter(filename))
            {
                foreach (var x in Dataset)
                {
                    foreach (var y in x)
                        w.Write(Math.Round(y, 4).ToString("0.0000") + "\t");
                    w.WriteLine();
                }
            }
        }

        public void WriteInfoToFile(string filename = "dataset-info.txt")
        {
            using (var w = new StreamWriter(filename))
            {
                w.WriteLine(ToString());
            }
        }

        public void RandomizeArray()
        {
            new Random().Shuffle(Dataset);
        }


        public void ShrinkDataset(int size)
        {
            if (size < DatasetSize)
            {
                var shrinked = new double[size][];
                DatasetSize = size;

                for (var i = 0; i < Dataset.Length; i++)
                    if (i < size)
                        shrinked[i] = Dataset[i];
                Dataset = shrinked;
            }
            ComputeInitialError();
            NormalizeDataset();
        }
    }

    internal static class RandomExtensions
    {
        public static void Shuffle<T>(this Random rng, T[] array){var n = array.Length;while (n > 1){var k = rng.Next(n--);var temp = array[n];array[n] = array[k];array[k] = temp;}
        }
    }
}