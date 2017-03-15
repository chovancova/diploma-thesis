#ifndef _VALUES_LOG_H_
#define _VALUES_LOG_H_


class CValuesLog
{
  private:
    char file_name[1024];

  public:
    CValuesLog(char *file_name);
    ~CValuesLog();

    void clear();
    void save_values(unsigned int count, ...);
};


#endif
