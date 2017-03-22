#include "TempFunctions.h"

#include <stdlib.h>
#include <stdio.h>

void MyError(char* strErr)
{
	printf("Sorry, we have got an error (%s).\nPls, press any key", strErr);
	getchar();
	getchar();
}

void MyWarning(char* strErr)
{
	printf("Warning: (%s).\n", strErr);
}


unsigned int* newUnInt(unsigned int size, unsigned int value, char* strError)
{
	unsigned int* array;
	array = (unsigned int*) new unsigned int[size];
	if (!array) MyError(strError);
	for (unsigned int i = 0; i < size; i++)
		array[i] = value;
	return (array);
}

unsigned long* newUnLong(unsigned long size, unsigned long value, char* strError)
{
	unsigned long* array;
	array = (unsigned long*) new unsigned long[size];
	if (!array) MyError(strError);
	for (unsigned long k = 0; k < size; k++)
		array[k] = value;
	return (array);
}

unsigned long* newUnLong(unsigned int size, unsigned long value, char* strError)
{
	unsigned long* array;
	array = (unsigned long*) new unsigned int[size];
	if (!array) MyError(strError);
	for (unsigned int k = 0; k < size; k++)
		array[k] = value;
	return (array);
}

float* newFloat(unsigned int size, float value, char* strError)
{
	float* array;
	array = (float*) new float[size];
	if (!array) MyError(strError);
	for (unsigned int i = 0; i < size; i++)
		array[i] = value;
	return (array);
}

float* newFloat(unsigned long size, float value, char* strError)
{
	float* array;
	array = (float*) new float[size];
	if (!array) MyError(strError);
	for (unsigned long k = 0; k < size; k++)
		array[k] = value;
	return (array);
}

double* newDouble(unsigned int size, double value, char* strError)
{
	double* array;
	array = (double*) new double[size];
	if (!array) MyError(strError);
	for (unsigned int i = 0; i < size; i++)
		array[i] = value;
	return (array);
}


double* newDouble(unsigned long size, double value, char* strError)
{
	double* array;
	array = (double*) new double[size];
	if (!array) MyError(strError);
	for (unsigned long k = 0; k < size; k++)
		array[k] = value;
	return (array);
}

bool* newBool(unsigned int size, bool value, char* strError)
{
	bool* array;
	array = (bool*) new bool[size];
	if (!array) MyError(strError);
	for (unsigned int i = 0; i < size; i++)
		array[i] = value;
	return (array);
}

bool* newBool(unsigned long size, bool value, char* strError)
{
	bool* array;
	array = (bool*) new bool[size];
	if (!array) MyError(strError);
	for (unsigned long k = 0; k < size; k++)
		array[k] = value;
	return (array);
}
