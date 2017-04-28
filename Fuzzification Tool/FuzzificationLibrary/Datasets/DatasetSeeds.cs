using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Datasets;

namespace FuzzificationLibrary.Datasets
{
    class DatasetSeeds : DataSets
    {
        public DatasetSeeds(int datasetSize = 210, int inputAttributes = 7,
            int outputIntervals = 3, string filename = "seeds.data")
            : base(datasetSize, inputAttributes, outputIntervals, filename)
        {
        }

        public DatasetSeeds(string filename, int datasetSize = 210, int inputAttributes = 7,
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
                            data = line.Split(' ');
                            Dataset[j] = new double[Attributes];
                            //"%f  %f  %f  %f  %f  %f  %f  %f",

                            for (var i = 0; i < Attributes; i++)
                                double.TryParse(data[i], NumberStyles.Any,
                                    CultureInfo.InvariantCulture, out Dataset[j][i]);

                            Dataset[j][InputAttributes]--;

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
   
