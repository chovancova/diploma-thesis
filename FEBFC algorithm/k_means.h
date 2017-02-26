#ifndef _K_MEANS_H_
#define _K_MEANS_H_

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>

struct sKmeansItem
{
  std::vector<float> input;
  std::vector<float> output;
};

class CKameans
{
  public:
    std::vector<sKmeansItem> centers;

    unsigned int used_centers;

  public:
    CKameans(unsigned int centers_count, unsigned int inputs_count, unsigned int outputs_count);
    ~CKameans();

    void train(std::vector<float> &input, std::vector<float> &required_output);

    //return cluster ID
    unsigned int process(std::vector<float> &input);

  protected:
    float distance(std::vector<float> &a, std::vector<float> &b);
    float rnd();
};

#endif
