using System;
using System.Globalization;
using System.IO;
using Datasets;

namespace FuzzificationLibrary.Datasets
{
    public class DatasetWine : DataSets
    {
        public DatasetWine(int datasetSize = 178, int inputAttributes = 13,
            int outputIntervals = 3, string filename = "wine.data")
            : base(datasetSize, inputAttributes, outputIntervals, filename)
        {
        }

        public DatasetWine(string filename, int datasetSize = 178, int inputAttributes = 13,
            int outputIntervals = 3)
            : base(datasetSize, inputAttributes, outputIntervals, filename)
        {
        }

        public override int InitializeDataset()
        {
            try
            {
                // Open the text file using a stream reader.
                using (var sr = new StreamReader(Filename))
                {
                    var j = 0;
                    var value = 0.0d;
                    // Read the stream to a string, and write the string to the console.
                    string line;
                    var data = new string[InputAttributes];

                    while ((line = sr.ReadLine()) != null)
                        if (!string.IsNullOrEmpty(line))
                        {
                            data = line.Split(',');
                            Dataset[j] = new double[Attributes];
                            //"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f"
                            
                             double.TryParse(data[0], NumberStyles.Any, CultureInfo.InvariantCulture, out Dataset[j][13]);
                            for (var i = 1; i < Attributes; i++)
                                double.TryParse(data[i], NumberStyles.Any,
                                    CultureInfo.InvariantCulture, out Dataset[j][i-1]);

                            Dataset[j][InputAttributes]--;//  InputAttributes == 13

                            j++;
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
    }
}