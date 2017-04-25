using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Datasets
{
    public enum DatasetType
    {
        Heart, Iris, Seeds, Skin, Wine, Yeast, Bupa, Balance, Vowel, Pima, Venicle, Wpbc, Wdbc
    }

    public static class DatasetChooser
    {
        public static DataSets ReadDatasetFromFile(DatasetType type, int datasetSize, int attributes, int inputAttributes, int outputAttributes, int outputIntervals, string filename)
        {
            DataSets dataset = null;
            switch (type)
            {
                case DatasetType.Iris:
                    dataset = (DataSets) new DatasetIris( datasetSize, attributes,  inputAttributes,  outputAttributes,  outputIntervals,  filename);
                    break;
                default:
                    return null;
            }

            dataset.InitializeDataset();
            dataset.NormalizeDataset();
            dataset.WriteInfoToFile();
            return dataset;
        }
        public static DataSets ReadDatasetFromFile(DatasetType type, string filename)
        {
            DataSets dataset = null;
            switch (type)
            {
                case DatasetType.Iris:
                    dataset = (DataSets) new DatasetIris( filename);
                    break;
                default:
                    return null;
            }

            dataset.InitializeDataset();
            dataset.NormalizeDataset();
            dataset.WriteInfoToFile();
            return dataset;
        }
    }

}
