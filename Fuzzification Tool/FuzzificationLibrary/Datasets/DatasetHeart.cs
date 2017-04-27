using System;
using System.Globalization;
using System.IO;

namespace Datasets
{
    public class DatasetHeart : DataSets
    {
        public DatasetHeart(int datasetSize = 270, int inputAttributes = 13,
            int outputIntervals = 2, string filename = "heart.data")
            : base(datasetSize, inputAttributes, outputIntervals, filename)
        {
        }

        public DatasetHeart(string filename, int datasetSize = 270, int inputAttributes = 13,
            int outputIntervals = 2)
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
                            for (var i = 0; i < Attributes; i++)
                                double.TryParse(data[i], NumberStyles.Any,
                                    CultureInfo.InvariantCulture, out Dataset[j][i]);
                            Dataset[j][2]--;
                            Dataset[j][10]--;
                            Dataset[j][13]--;

                            if (Dataset[j][12] == 3)
                                Dataset[j][12] = 0.0;

                            if (Dataset[j][12] == 6)
                                Dataset[j][12] = 1.0;

                            if (Dataset[j][12] == 7)
                                Dataset[j][12] = 2.0;
                            j++;
                        }
                }
                LingvisticAttribute[1] = 2; // Feature[2] - sex
                LingvisticAttribute[2] = 4; // Feature[3] - chest pain type (1-4)
                LingvisticAttribute[5] = 2; // Feature[6] - fasting blood sugar > 120 mg/dl
                LingvisticAttribute[6] = 3; // Feature[7] - hresting electrocardiographic results (0,1,2)
                LingvisticAttribute[8] = 2; // Feature[9] - exercise induced angina
                LingvisticAttribute[10] = 3; // Feature[11] - the slope of the peak exercise ST segment
                LingvisticAttribute[11] = 4;
                // Feature[12] - number of major vessels (0-3) colored by flourosopy
                LingvisticAttribute[12] = 3;
                // Feature[13] - thal: 0->3 (normal); 1->6 (fixed defect); 2->7 (reversable defect)
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