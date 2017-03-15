#include "values_log.h"

#include <stdio.h>
#include <stdarg.h>



CValuesLog::CValuesLog(char *file_name)
{
  sprintf(this->file_name,"%s",file_name);
}

CValuesLog::~CValuesLog()
{

}

void CValuesLog::clear()
{
  FILE *f;
  f = fopen(file_name,"w");
  fclose(f);
}

void CValuesLog::save_values(unsigned int count, ...)
{
  unsigned int i;

  va_list vl;
  va_start(vl, count);

  FILE *f;
  f = fopen(file_name,"a+");


  for (i = 0; i < count; i++)
  {
    float tmp = va_arg(vl, double);
    fprintf(f,"%f ", tmp);
  }

  va_end(vl);


  fprintf(f,"\n");
  fclose(f);
}
