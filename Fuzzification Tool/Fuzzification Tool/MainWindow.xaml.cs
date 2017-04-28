using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Datasets;
using FuzzificationLibrary;

namespace Fuzzification_Tool
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            Fuzzification fuzzy = null;
            DataSets data = null;
            switch (datasets.Text)
            {
                case "1  - Heart":
                    data = DatasetChooser.ReadDatasetFromFile(DatasetType.Heart, "heart.data");
                    break;
                case "2  - Iris":
                    data = DatasetChooser.ReadDatasetFromFile(DatasetType.Iris, "iris.data");
                    break;
                case "3  - Seeds":
                    data = DatasetChooser.ReadDatasetFromFile(DatasetType.Seeds, "seeds.data");
                    break;
                case "4  - Wine":
                    data = DatasetChooser.ReadDatasetFromFile(DatasetType.Wine, "wine.data");
                    break;
                case "5  - Yeast":
                    data = DatasetChooser.ReadDatasetFromFile(DatasetType.Yeast, "yeast.data");
                    break;
                case "6  - Test":
                    data = DatasetChooser.ReadDatasetFromFile(DatasetType.Test, "test.data");
                    break;
                default:
                    MessageBox.Show("Choose again dataset.", "My App", MessageBoxButton.OK, MessageBoxImage.Information);
                    break;
            }


            switch (algorithms.Text)
            {
                case "1  - Fuzzification with Entropy":
                    fuzzy = new FuzzificationEntropy(data);
                    break;
                case "2  - Fuzzification with Waged Entropy":
                    fuzzy = new FuzzificationWagedEntropy(data);
                    break;
                case "3  - Fuzzification with Waged Entropy and FCM clastering":
                    fuzzy = new FuzzificationWagedFcMclastering(data);
                    break;
                case "4  - Fuzzification with Hierarchical Entropy":
                    fuzzy = new FuzzificationHierarchicalEntropy(data);
                    break;
                default:
                    MessageBox.Show("Choose again algorithm.", "My App", MessageBoxButton.OK, MessageBoxImage.Information);
                    break;
            }
            var volba = datasets.SelectedIndex;
            var volba2 = algorithms.SelectedIndex;

            if (data != null && fuzzy != null)
            {
                fuzzy.RunFuzzification();
                data.WriteInfoToFile("dataset-information-" + volba + "-" + volba2 + ".txt");
                fuzzy.WriteToFile("fuzzification-information-" + volba + "-" + volba2 + ".txt");
                fuzzy.WriteResultsToFile("fuzzification-results-" + volba + "-" + volba2 + ".txt");
                MessageBox.Show("Done.", "My App", MessageBoxButton.OK, MessageBoxImage.Information);
            }
        }
    }
}
