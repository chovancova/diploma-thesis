using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Datasets
{
  public  class DatasetIris : DataSets
    {
        public override int InitializeDataset()
        {
            try
            {
                // Open the text file using a stream reader.
                using (StreamReader sr = new StreamReader(Filename))
                {
                    int j = 0;
                    double value = 0.0d;
                    // Read the stream to a string, and write the string to the console.
                    String line;
                    string[] data = new string[InputAttributes];

                    while ((line = sr.ReadLine()) != null )
                    {
                        if (!string.IsNullOrEmpty(line))
                        {
                            data = line.Split(',');
                            Dataset[j] = new double[Attributes];
                            for (int i = 0; i < InputAttributes; i++)
                            {
                               double.TryParse(data[i], NumberStyles.Any,
                                    System.Globalization.CultureInfo.InvariantCulture, out Dataset[j][i]);
                            }
                            //specific for iris
                            switch (data[InputAttributes])
                            {
                                case "Iris-setosa":
                                    Dataset[j][InputAttributes] = 0;
                                    break;
                                case "Iris-versicolor":
                                    Dataset[j][InputAttributes] = 1;
                                    break;
                                case "Iris-virginica":
                                    Dataset[j][InputAttributes] = 2;
                                    break;
                            }
                            j++;
                        }
                        }
                }
            }
            catch
                (Exception e)
            {
                Console.WriteLine("Dataset not initialized.");
                Console.WriteLine(e.Message);
                return -1;
            }
            ComputeInitialError();
            return 1; 
        }

        public DatasetIris(int datasetSize=150, int attributes=5, int inputAttributes=4,
            int outputAttributes=1, int outputIntervals=3, string filename = "iris.data") : base(datasetSize, attributes, inputAttributes, outputAttributes, outputIntervals, filename)
        {
        }  public DatasetIris(string filename ,int datasetSize=150, int attributes=5, int inputAttributes=4,
            int outputAttributes=1, int outputIntervals=3) : base(datasetSize, attributes, inputAttributes, outputAttributes, outputIntervals, filename)
        {

        }
    }
}