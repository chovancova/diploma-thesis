#include <stdio.h>
#include <time.h>
#include "dataset_interface.h"
#include "dataset_iris.h"


#include "k_means.h"
#include "fuzzy_entropy.h"


int main()
{
  srand(time(NULL));

  class CDatasetInterface *dataset;
  dataset = new CDatasetIris((char*)"iris_dataset.txt");
  printf("dataset loaded\n");


  unsigned int features_count = dataset->get_input_size();
  unsigned int centers_max_count = 8;

  printf("features count %u\n", features_count);

  std::vector<class CMembershipFunction> membership_functions;

  for (unsigned int feature = 0; feature < features_count; feature++)
  {
    struct sFuzzyEntropyResult fuzzy_entropy_result_best;
    fuzzy_entropy_result_best.entropy = 10000000.0;

    for (unsigned int centers_count = 2; centers_count < centers_max_count; centers_count++)
    {
      //create new k-means with specified centers count, inputs count and output vector size
      class CKameans kmeans(centers_count, features_count, dataset->get_output_size());

      //train k-means, 1000 iterations
      for (unsigned int i = 0; i < 10000; i++)
      {
        //select random item from dataset
        struct sDatasetItem item = dataset->get(rand()%dataset->get_size());

        //train
        kmeans.train(item.input, item.output);
      }


      class CFuzzyEntropy fuzzy_entropy;
      struct sFuzzyEntropyResult fuzzy_entropy_result;
      fuzzy_entropy_result = fuzzy_entropy.process(feature, kmeans, dataset);

    //  printf("feature %u centers count %u entropy %f\n", feature, centers_count, fuzzy_entropy_result.entropy);

      if (fuzzy_entropy_result_best.entropy > fuzzy_entropy_result.entropy)
      {
        fuzzy_entropy_result_best = fuzzy_entropy_result;
        // break;
      }
    }


    membership_functions.push_back(fuzzy_entropy_result_best.membership_function);
  }


  for (unsigned int item_idx = 0; item_idx < dataset->get_size(); item_idx++)
  {
    struct sDatasetItem item = dataset->get(item_idx);
    for (unsigned int feature = 0; feature < membership_functions.size(); feature++)
    {
      membership_functions[feature].process(item.input[feature]);
      membership_functions[feature].print_result();
      printf(", ");
    }

    printf("\n");
  }


  delete dataset;

  printf("program dome\n");
  return 0;
}
