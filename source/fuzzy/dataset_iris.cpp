#include "dataset_iris.h"
#include <stdio.h>
#include <stdlib.h>

#include <values_log.h>


CDatasetIris::CDatasetIris(char *file_name)
{
  FILE *f = fopen(file_name,"r");

  if (f == NULL)
  {
    printf("file opening error %s\n", file_name);
    return;
  }

  while (!feof(f))
  {
    struct sDatasetItem result;

    for (unsigned int i = 0; i < 4; i++)
      result.input.push_back(0.0);

    for (unsigned int i = 0; i < 3; i++)
      result.output.push_back(0.0);

    unsigned int type = 0;

    int res;
    res = fscanf(f,"%u %f %f %f %f\n", &type, &(result.input[0]), &(result.input[1]), &(result.input[2]), &(result.input[3]));
    (void)res;

    /*
    for (unsigned int i = 0; i < 20; i++)
      result.input.push_back((rand()%2000)/1000.0 - 2.0);
    */

    for (unsigned int i = 0; i < result.output.size(); i++)
      result.output[i] = -1.0;
    result.output[type] = 1.0;

    items.push_back(result);
  }

  fclose(f);

  normalise();


  for (unsigned int j = 0; j < items.size(); j++)
  {
    struct sDatasetItem result;

    result = items[j];
    printf("%4u >> ", j);

    for (unsigned int i = 0; i < result.input.size(); i++)
      printf("%6.3f ", items[j].input[i]);

    printf(" ----> ");
    for (unsigned int i = 0; i < result.output.size(); i++)
      printf("%6.3f ", items[j].output[i]);

    printf("\n");
  }

}


CDatasetIris::~CDatasetIris()
{

}


void CDatasetIris::export_image()
{
  CValuesLog iris_01((char*)"iris_examples/iris_01.log");
  iris_01.clear();

  CValuesLog iris_02((char*)"iris_examples/iris_02.log");
  iris_02.clear();

  CValuesLog iris_03((char*)"iris_examples/iris_03.log");
  iris_03.clear();

  for (unsigned int j = 0; j < items.size(); j++)
  {
    struct sDatasetItem item = items[j];

    if (item.output[0] > 0.0)
      iris_01.save_values(4, item.input[0], item.input[1], item.input[2], item.input[3]);

    if (item.output[1] > 0.0)
      iris_02.save_values(4, item.input[0], item.input[1], item.input[2], item.input[3]);

    if (item.output[2] > 0.0)
      iris_03.save_values(4, item.input[0], item.input[1], item.input[2], item.input[3]);
  }
}
