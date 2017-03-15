#pragma once
class Sort
{
public:
	static void QuickSort(double** sortArray, unsigned long start, unsigned long end, unsigned long TotalSets);
	static void QuickSort(double* array, unsigned long start, unsigned long end, unsigned long TotalSets);
	static void quicksort2A(double* arrayMinor, double* arrayMain, unsigned long size, unsigned long start, unsigned long end);
private:
	Sort()
	{
	};
};
