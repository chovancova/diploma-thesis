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
            DataSets data = DatasetChooser.ReadDatasetFromFile(DatasetType.Test, "test.data");
            DataSets data2 = DatasetChooser.ReadDatasetFromFile(DatasetType.Iris, "iris.data");
            data.WriteInfoToFile("test-data-info.txt");
            FuzzificationWagedEntropy fcw = new FuzzificationWagedEntropy(data);
            FuzzificationEntropy fc = new FuzzificationEntropy(data);
            FuzzificationWagedEntropy fcw2 = new FuzzificationWagedEntropy(data2);
            FuzzificationEntropy fc2 = new FuzzificationEntropy(data2);
            FuzzificationWagedFcMclastering fcc2 = new FuzzificationWagedFcMclastering(data2);
            FuzzificationOnlyFCM fcofcm = new FuzzificationOnlyFCM(data2);
            FuzzificationHierarchicalEntropy fhe = new FuzzificationHierarchicalEntropy(data2);
            fcw.RunFuzzification();
            fcw.WriteToFile("test-results-vazena2.txt");
            fc.RunFuzzification();
            fc.WriteToFile("test-results-normalna2.txt");
            fcw2.RunFuzzification();
            fcw2.WriteToFile("iris-results-vazena2.txt");
            fc2.RunFuzzification();
            fc2.WriteToFile("iris-results-normalna2.txt");
            fcc2.RunFuzzification();
            fcc2.WriteToFile("iris-results-vazenaFCM2.txt");
            fcofcm.RunFuzzification();
            fcofcm.WriteToFile("iris-results-onlyFCM2.txt");
            fhe.RunFuzzification();
            fhe.WriteToFile("iris-results-fhe2.txt");
            Console.ReadKey();
        }

       
    }
}
