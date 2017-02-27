#ifndef _FUZZY_ENTROPY_H_
#define _FUZZY_ENTROPY_H_

#include <vector>
#include "dataset_interface.h"
#include "membership_function.h"
#include "k_means.h"


struct sFuzzyEntropyResult
{
  CMembershipFunction membership_function;
  float entropy;
};

class CFuzzyEntropy
{
  private:
    float result;

  public:
    CFuzzyEntropy();
    ~CFuzzyEntropy();

    struct sFuzzyEntropyResult process(unsigned int attribute_id, class CKameans &kmeans, class CDatasetInterface *dataset);

    float get();

  private:
    //create subset from dataset containing only the class_id class
    std::vector<struct sDatasetItem> make_subset(unsigned int class_id, class CDatasetInterface *dataset);

};


#endif
