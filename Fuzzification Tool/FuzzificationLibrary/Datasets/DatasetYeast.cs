using System;
using System.Globalization;
using System.IO;
using Datasets;

namespace FuzzificationLibrary.Datasets
{
    public class DatasetYeast : DataSets
    {
        public DatasetYeast(int datasetSize = 1484, int inputAttributes = 8,
            int outputIntervals = 10, string filename = "yeast.data")
            : base(datasetSize, inputAttributes, outputIntervals, filename)
        {
        }

        public DatasetYeast(string filename, int datasetSize = 1484, int inputAttributes = 8,
            int outputIntervals = 10)
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
                           
                            //"%s  %f  %f  %f  %f  %f  %f  %f  %f  %s"
                            for (var i = 1; i < Attributes; i++)
                                double.TryParse(data[i], NumberStyles.Any,
                                    CultureInfo.InvariantCulture, out Dataset[j][i-1]);

                            if (Dataset[j][4] == 0.50) Dataset[j][4] = 0.0;
                            if (Dataset[j][5] == 0.50) Dataset[j][5] = 1.0;
                            if (Dataset[j][5] == 0.83) Dataset[j][5] = 2.0;
                            //specific for iris
                            switch (data[Attributes])
                            {
                                case "CYT":
                                    Dataset[j][InputAttributes] = 0;
                                    break;
                                case "NUC":
                                    Dataset[j][InputAttributes] = 1;
                                    break;
                                case "MIT":
                                    Dataset[j][InputAttributes] = 2;
                                    break;
                                case "ME3":
                                    Dataset[j][InputAttributes] = 3;
                                    break;
                                case "ME2":
                                    Dataset[j][InputAttributes] = 4;
                                    break;
                                case "ME1":
                                    Dataset[j][InputAttributes] = 5;
                                    break;
                                case "EXC":
                                    Dataset[j][InputAttributes] = 6;
                                    break;
                                case "VAC":
                                    Dataset[j][InputAttributes] = 7;
                                    break;
                                case "POX":
                                    Dataset[j][InputAttributes] = 8;
                                    break;
                                case "ERL":
                                    Dataset[j][InputAttributes] = 9;
                                    break;
                            }
                            j++;
                        }
                    LingvisticAttribute[4] = 2; //  0.5   1.0
                    LingvisticAttribute[5] = 3; //  0.0   0.5  0.83
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