#ifndef _FMCONFIG_H_
#define _FMCONFIG_H_

#include <db.h>
#include <errorcodes.h>


enum LOG_MODES
  {
    LOG_INFO,
    LOG_WARNING,
    LOG_DEBUG,
  };

typedef unsigned short LOG_MODE;


ERROR_CODE init_fmnc();
ERROR_CODE exit_fmnc();

void LOG(const char* message, LOG_MODE mode);
MYSQL* DB();


#endif
