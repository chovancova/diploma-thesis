using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Datasets;
using FuzzificationLibrary;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            //DatasetIris iris = new DatasetIris(150,5,4,1,3,"iris.data");
            //iris.InitializeDataset();
            //iris.WriteToFile("iris-initialized.txt");
            //iris.NormalizeDataset();
            //iris.WriteToFile("iris-normalized.txt");
            //iris.WriteInfoToFile("iris-info.txt");
            //Console.WriteLine(iris.InitialError);

            //double[][] dataset = iris.Dataset; //ReadDatasets(150,4,1,3, "iris.data", ',');

            //for (int i = 0; i < dataset.Length; i++)
            //{
            //    for (int j = 0; j < dataset[i].Length; j++)
            //    {
            //        Console.Write((Math.Round(dataset[i][j], 4)).ToString("0.0000") + "\t");

            //    }
            //    Console.WriteLine();
            //}

            // DataSets data =  DatasetChooser.ReadDatasetFromFile(DatasetType.Iris, 150, 5, 4, 1, 3, "iris.data");
            //  DataSets data =  DatasetChooser.ReadDatasetFromFile(DatasetType.Iris, "iris.data");
            ////  data.RandomizeArray();
            // // data.WriteInfoToFile("randomized data.txt");
            // FuzzyClassifier fc = new FuzzyClassifierFuzzyEntropy(data);
            //  FuzzyClassifiierWagedFuzzyEntropy fcw = new FuzzyClassifiierWagedFuzzyEntropy(data);

            //  //fc.RunFuzzification();
            //  //fc.WriteToFile("R_fuzzyClassifier-resultData.txt");
            //  fcw.RunFuzzification();
            //  fcw.WriteToFile("R_fuzzyClassifier-resultData-waged.txt");
            //FuzzyCMeansMethod fcm = new FuzzyCMeansMethod(data);
            //fcm.RunFuzzification();
            //fc.WriteToFile("R_fuzzyClassifier-resultData-fcm.txt");



            // data.RandomizeArray();
            // data.ShrinkDataset(20);
            // data.WriteInfoToFile("R_shriked-dataset-iris-before-fuzzification.txt");
            // fc = new FuzzyClassifierFuzzyEntropy(data);
            // fcw = new FuzzyClassifiierWagedFuzzyEntropy(data);
            // fcm = new FuzzyCMeansMethod(data);
            //fc.RunFuzzification();
            //fc.WriteToFile("R_shriked-dataset-iris-after-febfc.txt");
            // fcw.RunFuzzification();
            // fcw.WriteToFile("R_shriked-dataset-iris-after-waged.txt");

            // fcm.RunFuzzification();
            // fcm.WriteToFile("R_shriked-dataset-iris-after-fcm.txt");


            DataSets data = DatasetChooser.ReadDatasetFromFile(DatasetType.Test, "test.data");
            DataSets data2 = DatasetChooser.ReadDatasetFromFile(DatasetType.Iris, "iris.data");
            data.WriteInfoToFile("test-data-info.txt");
            FuzzificationWagedEntropy fcw = new FuzzificationWagedEntropy(data);
            FuzzificationEntropy fc = new FuzzificationEntropy(data);
            FuzzificationWagedEntropy fcw2 = new FuzzificationWagedEntropy(data2);
            FuzzificationEntropy fc2 = new FuzzificationEntropy(data2);
            fcw.RunFuzzification();
            fcw.WriteToFile("test-results-vazena.txt");
            fc.RunFuzzification();
            fc.WriteToFile("test-results-normalna.txt");
            fcw2.RunFuzzification();
            fcw2.WriteToFile("iris-results-vazena.txt");
            fc2.RunFuzzification();
            fc2.WriteToFile("iris-results-normalna.txt");
            Console.ReadKey();
        }

        public static double[][] ReadDatasets(int size,int inputAttributes, int outputAttributes, 
            int outputIntervals,string filename, char deliminator = ',')
        {
            double[][] dataset = new double[size][];
            int j = 0;
            double value = 0.0d;
            try
            {   // Open the text file using a stream reader.
                using (StreamReader sr = new StreamReader(filename))
                {
                    // Read the stream to a string, and write the string to the console.
                    String line;
                    string[] data = new string[inputAttributes];

                    while ((line = sr.ReadLine()) != null)
                    {
                        if (!string.IsNullOrEmpty(line))
                        {
                            data = line.Split(deliminator);
                            dataset[j] = new double[inputAttributes+outputAttributes];
                            for (int i = 0; i < inputAttributes; i++)
                            {
                                // dataset[j][i] = double.Parse(data[i]);//, System.Globalization.CultureInfo.InvariantCulture);
                                //dataset[j][i] = 0.0; 
                                double.TryParse(data[i], NumberStyles.Any, System.Globalization.CultureInfo.InvariantCulture, out dataset[j][i]);
                            }

                            //specific for iris
                            switch (data[inputAttributes])
                            {
                                case "Iris-setosa":
                                    dataset[j][inputAttributes] = 0;
                                    break;
                                case "Iris-versicolor":
                                    dataset[j][inputAttributes] = 1;
                                    break;
                                case "Iris-virginica":
                                    dataset[j][inputAttributes] = 2;
                                    break;
                             }
                            j++;
                        }
                    }
                     
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The file could not be read:");
                Console.WriteLine(e.Message);
            }


            return dataset;
        }
    }
}
