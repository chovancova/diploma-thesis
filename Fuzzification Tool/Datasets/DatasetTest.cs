using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Datasets
{
    public class DatasetTest : DataSets
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

                    while ((line = sr.ReadLine()) != null)
                    {
                        if (!string.IsNullOrEmpty(line))
                        {
                            data = line.Split(',');
                            Dataset[j] = new double[Attributes];
                            for (int i = 0; i < Attributes; i++)
                            {
                                double.TryParse(data[i], NumberStyles.Any,
                                    System.Globalization.CultureInfo.InvariantCulture, out Dataset[j][i]);

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

        public DatasetTest(int datasetSize=15, int attributes=2, int inputAttributes=1, int outputAttributes=1, int outputIntervals=3, string filename="test.data") : base(datasetSize, attributes, inputAttributes, outputAttributes, outputIntervals, filename)
        {
        } public DatasetTest(string filename="test.data", int datasetSize=15, int attributes=2, int inputAttributes=1, int outputAttributes=1, int outputIntervals=3) : base(datasetSize, attributes, inputAttributes, outputAttributes, outputIntervals, filename)
        {
        }
    }
}
