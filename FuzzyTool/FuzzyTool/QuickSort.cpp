#include "QuickSort.h"
/*-------------------------- QuickSort ----------------------------------------------
Triedenie pomocneho pola sortArray
------------------------------------------------------------------------------------*/
void Sort::QuickSort(double** sortArray, unsigned long start, unsigned long end, unsigned long TotalSets)
{
	unsigned long i, j;
	double median, exchangeVektK, exchangeValue, exchangeClassValue;
	i = start;
	j = end;
	median = sortArray[1][(start + end) / 2];
	do {
		while ((sortArray[1][i]< median) && (i < TotalSets)) i++;
		while ((sortArray[1][j]> median) && (j >= 0)) j--;
		if (i<j)
		{
			exchangeVektK = sortArray[0][i];
			exchangeValue = sortArray[1][i];
			exchangeClassValue = sortArray[2][i];

			sortArray[0][i] = sortArray[0][j];
			sortArray[1][i] = sortArray[1][j];
			sortArray[2][i] = sortArray[2][j];

			sortArray[0][j] = exchangeVektK;
			sortArray[1][j] = exchangeValue;
			sortArray[2][j] = exchangeClassValue;
			i++;
			j--;
		}
		else {
			if (i == j) {
				i++;
				if (j != 0) j--;
			}
		}
	} while (i <= j);

	if (start < j)
		QuickSort(sortArray, start, j, TotalSets);
	if (i < end)
		QuickSort(sortArray, i, end, TotalSets);
}

/**** quicksort2A ****/
void Sort::QuickSort(double* array, unsigned long start, unsigned long end, unsigned long TotalSets)
{
	unsigned long i, j;
	double median, exchangeValue;
	i = start;
	j = end;
	median = array[(start + end) / 2];
	do {
		while ((array[i]< median) && (i < TotalSets)) i++;
		while ((array[j]> median) && (j >= 0)) j--;
		if (i<j)
		{
			exchangeValue = array[i];
			array[i] = array[j];
			array[j] = exchangeValue;
			i++;
			j--;
		}
		else {
			if (i == j) {
				i++;
				if (j != 0) j--;
			}
		}
	} while (i <= j);
	if (start < j) QuickSort(array, start, j, TotalSets);
	if (i < end) QuickSort(array, i, end, TotalSets);
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
void Sort::quicksort2A(double* arrayMinor, double* arrayMain, unsigned long size, unsigned long start, unsigned long end)
{
	unsigned long i, j;
	double        median, exchangeVarVekt, exchangeVar;

	i = start;
	j = end;
	median = arrayMain[(start + end) / 2];
	do
	{
		while ((arrayMain[i] < median) && (i < size)) i++;
		while ((arrayMain[j] > median) && (j >= 0)) j--;

		if (i < j)
		{
			exchangeVar = arrayMain[i];
			exchangeVarVekt = arrayMinor[i];

			arrayMain[i] = arrayMain[j];
			arrayMinor[i] = arrayMinor[j];

			arrayMain[j] = exchangeVar;
			arrayMinor[j] = exchangeVarVekt;
			i++;
			j--;
		}
		else
			if (i == j)
			{
				i++;
				if (j != 0) j--;
			}
	} while (i <= j);
	if (start < j) quicksort2A(arrayMinor, arrayMain, size, start, j);
	if (i < end) quicksort2A(arrayMinor, arrayMain, size, i, end);
}