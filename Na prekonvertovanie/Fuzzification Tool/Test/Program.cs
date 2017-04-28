using System;
using Datasets;
using FuzzificationLibrary;

namespace Test
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            var data2 = DatasetChooser.ReadDatasetFromFile(DatasetType.Iris, "iris.data");
            var fcw2 = new FuzzificationWagedEntropy(data2);
            var fc2 = new FuzzificationEntropy(data2);
            var fcc2 = new FuzzificationWagedFcMclastering(data2);
            var fhe = new FuzzificationHierarchicalEntropy(data2);
           fcw2.RunFuzzification();fcw2.WriteToFile("iris-results-vazena2.txt");fc2.RunFuzzification();fc2.WriteToFile("iris-results-normalna2.txt");
            fcc2.RunFuzzification();fcc2.WriteToFile("iris-results-vazenaFCM2.txt");fhe.RunFuzzification();fhe.WriteToFile("iris-results-fhe2.txt");
            Console.ReadKey();
        }
    }
}