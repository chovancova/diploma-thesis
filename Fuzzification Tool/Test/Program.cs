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
            string volba = "";
            string volba2 = "";
            bool valid = true;
            Console.WriteLine("Fuzzification Tool \n");
            Console.WriteLine();
            Console.WriteLine("Available datasets: \n");
            Console.WriteLine("ID - Dataset Name");
            Console.WriteLine("-------------------------");
            Console.WriteLine("1  - Heart");
            Console.WriteLine("2  - Iris");
            Console.WriteLine("3  - Seeds");
            Console.WriteLine("4  - Wine");
            Console.WriteLine("5  - Yeast");
            Console.WriteLine("6  - Test");
            Console.WriteLine();
            DataSets data = null;
            while (data == null)
            {
                Console.WriteLine("Choose dataset: ");
                volba = Console.ReadLine();
                switch (volba)
                {
                    case "1":
                        data = DatasetChooser.ReadDatasetFromFile(DatasetType.Heart, "heart.data");
                        break;
                    case "2":
                        data = DatasetChooser.ReadDatasetFromFile(DatasetType.Iris, "iris.data");
                        break;
                    case "3":
                        data = DatasetChooser.ReadDatasetFromFile(DatasetType.Seeds, "seeds.data");
                        break;
                    case "4":
                        data = DatasetChooser.ReadDatasetFromFile(DatasetType.Wine, "wine.data");
                        break;
                    case "5":
                        data = DatasetChooser.ReadDatasetFromFile(DatasetType.Yeast, "yeast.data");
                        break;
                    case "6":
                        data = DatasetChooser.ReadDatasetFromFile(DatasetType.Test, "test.data");
                        break;
                    default:
                        data = null;
                        break;
                }
            }
            Fuzzification fuzzy = null;
            Console.WriteLine();
            Console.WriteLine("Available fuzzification algorithms: ");
            Console.WriteLine("ID - Algorithm Name");
            Console.WriteLine("-------------------------");
            Console.WriteLine("1  - Fuzzification with Entropy");
            Console.WriteLine("2  - Fuzzification with Waged Entropy");
            Console.WriteLine("3  - Fuzzification with Waged Entropy and FCM clastering");
            Console.WriteLine("4  - Fuzzification with Hierarchical Entropy");
            Console.WriteLine();
            while (fuzzy == null)
            {
                Console.WriteLine("Choose algorithm: ");
                 volba2 = Console.ReadLine();
                switch (volba2)
                {
                    case "1":
                        fuzzy = new FuzzificationEntropy(data);
                        break;
                    case "2":
                        fuzzy = new FuzzificationWagedEntropy(data);
                        break;
                    case "3":
                        fuzzy = new FuzzificationWagedFcMclastering(data);
                        break;
                    case "4":
                        fuzzy = new FuzzificationHierarchicalEntropy(data);
                        break;
                    default:
                        valid = false;
                        break;
                }
            }

            Console.WriteLine("Available operations: ");
            Console.WriteLine("1 - Fuzzificate data");
            Console.WriteLine("2 - Write information about dataset to file");
            Console.WriteLine("3 - Write information about fuzzification to file");
            Console.WriteLine("4 - Write result to file");
            Console.WriteLine("0 - Exit application");

            while (true)
            {
                Console.WriteLine("Choose operation: ");
                volba = Console.ReadLine();
                switch (volba)
                {
                    case "1":
                        fuzzy.RunFuzzification();
                        break;
                    case "2":
                        data.WriteInfoToFile("dataset-information-"+volba+"-"+volba2+".txt");
                        break;
                    case "3":
                        fuzzy.WriteToFile("fuzzification-information-" + volba + "-" + volba2 + ".txt");
                        break;
                    case "4":
                        fuzzy.WriteResultsToFile("fuzzification-results-" + volba + "-" + volba2 + ".txt");
                        break;
                    case "0":
                        return;
                   }
            }
        }
    }
}