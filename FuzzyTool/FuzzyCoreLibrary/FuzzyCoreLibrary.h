#pragma once
// FUZZYCORELIBRARY.h - Contains declaration of Function class  

#ifdef FUZZYCORELIBRARY_EXPORTS  
#define FUZZYCORELIBRARY_API __declspec(dllexport)   
#else  
#define FUZZYCORELIBRARY_API __declspec(dllimport)   
#endif  
#include <string>

namespace FuzzyCoreLibrary
{
	// This class is exported from the FUZZYCORELIBRARY.dll  
	class Functions
	{
	public:
		static FUZZYCORELIBRARY_API  bool Process();
		static FUZZYCORELIBRARY_API bool LoadDataset();

	
	};
}
