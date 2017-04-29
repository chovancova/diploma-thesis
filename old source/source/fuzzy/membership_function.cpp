#include "membership_function.h"
#include <stdio.h>


CMembershipFunction::CMembershipFunction()
{


}


CMembershipFunction::CMembershipFunction(std::vector<float> &centers_)
{
  for (unsigned int i = 0; i < centers_.size(); i++)
  {
    centers.push_back(centers_[i]);
    result.push_back(0.0);
  }

  //bubble sort centers values
  bool change;
  do
  {
    change = false;
    for (unsigned int i = 0; i < (centers.size()-1); i++)
      if (centers[i] > centers[i+1])
      {
        //swap value
        float tmp = centers[i];
        centers[i] = centers[i+1];
        centers[i+1] = tmp;

        change = true;
      }
  }
  while(change == true);

}

CMembershipFunction::~CMembershipFunction()
{


}

void CMembershipFunction::process(float x)
{
  float tmp = 0.0;

  unsigned int left_idx = 0;
  unsigned int right_idx = centers.size()-1;

  //most left membership function
  if (x <= centers[left_idx])
    tmp = 1.0; //(x + centers[left_idx] + 2.0)/(2.0*centers[left_idx+1] + 2.0); //1.0, variant
  else
    tmp = 1.0 - abs(centers[left_idx] - x) / abs(centers[left_idx+1] - centers[left_idx]);

  if (tmp < 0.0)
    tmp = 0.0;
  result[left_idx] = tmp;


  //most right
  if (x <= centers[right_idx])
    tmp = 1.0 - abs(centers[right_idx] - x)/abs(centers[right_idx] - centers[right_idx-1]);
  else
    tmp = 1.0; //(2.0 - x - centers[right_idx])/(2.0 - 2.0*centers[right_idx]);  //1.0, variant

  if (tmp < 0.0)
    tmp = 0.0;
  result[right_idx] = tmp;


  //center membership function
  for (unsigned int i = 1; i < (centers.size()-1); i++)
  {
    float tmp = 0.0;

    if (x <= centers[i])
      tmp = 1.0 - abs(centers[i] - x) / abs(centers[i] - centers[i-1]);
    else
      tmp = 1.0 - abs(centers[i] - x) / abs(centers[i+1] - centers[i]);

    if (tmp < 0.0)
      tmp = 0.0;

    result[i] = tmp;
  }
}


float CMembershipFunction::abs(float x)
{
  if (x < 0.0)
    x = -x;

  return x;
}


void CMembershipFunction::print_result()
{
/*
  for (unsigned int i = 0; i < centers.size(); i++)
    printf("%8.5f ", centers[i]);

  printf("\n");
*/
  for (unsigned int i = 0; i < result.size(); i++)
    printf("%4.2f ", result[i]);

}
