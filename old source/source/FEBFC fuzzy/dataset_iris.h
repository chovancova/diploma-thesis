#ifndef _DATASET_IRIS_H_
#define _DATASET_IRIS_H_

#include "dataset_interface.h"

class CDatasetIris : public CDatasetInterface
{
public:
	CDatasetIris(char *file_name);
	~CDatasetIris();

	void export_image();
};

#endif
