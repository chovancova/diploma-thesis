#include "QuickSort.h"

/*-------------------------- QuickSort ----------------------------------------------
Triedenie pomocneho pola sortArray
------------------------------------------------------------------------------------*/
void Sort::QuickSort(double** sort_Array, unsigned long start, unsigned long end, unsigned long total_sets)
{
	unsigned long i, j;
	double median, exchange_vekt_k, exchange_value, exchange_class_value;
	i = start;
	j = end;
	median = sort_Array[1][(start + end) / 2];
	do
	{
		while ((sort_Array[1][i] < median) && (i < total_sets)) i++;
		while ((sort_Array[1][j] > median) && (j >= 0)) j--;
		if (i < j)
		{
			exchange_vekt_k = sort_Array[0][i];
			exchange_value = sort_Array[1][i];
			exchange_class_value = sort_Array[2][i];

			sort_Array[0][i] = sort_Array[0][j];
			sort_Array[1][i] = sort_Array[1][j];
			sort_Array[2][i] = sort_Array[2][j];

			sort_Array[0][j] = exchange_vekt_k;
			sort_Array[1][j] = exchange_value;
			sort_Array[2][j] = exchange_class_value;
			i++;
			j--;
		}
		else
		{
			if (i == j)
			{
				i++;
				if (j != 0) j--;
			}
		}
	}
	while (i <= j);

	if (start < j)
		QuickSort(sort_Array, start, j, total_sets);
	if (i < end)
		QuickSort(sort_Array, i, end, total_sets);
}

/**** quicksort2A ****/
void Sort::QuickSort(double* array, unsigned long start, unsigned long end, unsigned long total_sets)
{
	unsigned long i, j;
	double median, exchange_value;
	i = start;
	j = end;
	median = array[(start + end) / 2];
	do
	{
		while ((array[i] < median) && (i < total_sets)) i++;
		while ((array[j] > median) && (j >= 0)) j--;
		if (i < j)
		{
			exchange_value = array[i];
			array[i] = array[j];
			array[j] = exchange_value;
			i++;
			j--;
		}
		else
		{
			if (i == j)
			{
				i++;
				if (j != 0) j--;
			}
		}
	}
	while (i <= j);
	if (start < j) QuickSort(array, start, j, total_sets);
	if (i < end) QuickSort(array, i, end, total_sets);
}

// Specialny quicksort, ktory triedi dve polia arrayMinor a arrayMain.
// 	Triedi sa podla hodnot arrayMain.  ArrayMinor sa meni tak aby sa aj po pretriedeni zachovala jeho suvislost s arrayMain.
//  Ak mam napr. v arrayMain mesiace a v arrayMinor pocty dni, tak po pretriedeni, budu pocty dni v arrayMinor[1] stale odpovedat
//	prisluchajucemu mesiacu arrayMain[1].
// Parametre: 	arrayMinor - vedlajsie pole
//				arrayMain  - hlavne pole
//				size  	   - velkost poli arrayMinor, arrayMain (musia byt rovnako velke)
//				start 	   - Od ktoreho indexu pola sa ma zacat triedit. (Ak sa ma pretriedit cele pole, treba nastavit na zaciatku na nulu)
//				end		   - po ktory index sa ma pole pretriedit. (Ak sa ma pretriedit cele pole, treba nastavit na zaciatku na size-1)
void Sort::quicksort2A(double* minor_array, double* main_array, unsigned long size, unsigned long start, unsigned long end)
{
	unsigned long i, j;
	double median, exchange_var_vekt, exchange_var;

	i = start;
	j = end;
	median = main_array[(start + end) / 2];
	do
	{
		while ((main_array[i] < median) && (i < size)) i++;
		while ((main_array[j] > median) && (j >= 0)) j--;

		if (i < j)
		{
			exchange_var = main_array[i];
			exchange_var_vekt = minor_array[i];

			main_array[i] = main_array[j];
			minor_array[i] = minor_array[j];

			main_array[j] = exchange_var;
			minor_array[j] = exchange_var_vekt;
			i++;
			j--;
		}
		else if (i == j)
		{
			i++;
			if (j != 0) j--;
		}
	}
	while (i <= j);
	if (start < j) quicksort2A(minor_array, main_array, size, start, j);
	if (i < end) quicksort2A(minor_array, main_array, size, i, end);
}
