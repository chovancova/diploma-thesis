#ifndef _TEMP_FUNCTIONS_H_
#define _TEMP_FUNCTIONS_H_

	 void MyError(char* strErr);
	 	void MyWarning(char* strErr);

	 	int* newInt(unsigned int size, int value, char* strError);
	 	unsigned int* newUnInt(unsigned int size, unsigned int value, char* strError);
	 	unsigned long* newUnLong(unsigned long size, unsigned long value, char* strError);
	 	unsigned long* newUnLong(unsigned int size, unsigned long value, char* strError);
	 	float* newFloat(unsigned int size, float value, char* strError);
	 	float* newFloat(unsigned long size, float value, char* strError);
	 	double* newDouble(unsigned int size, double value, char* strError);
	 	double* newDouble(unsigned long size, double value, char* strError);
	 	bool* newBool(unsigned int size, bool value, char* strError);
	 	bool* newBool(unsigned long size, bool value, char* strError);
#endif
