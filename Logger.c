#include "Logger.h"
#include <stdio.h>

/*******************************************/
void Logger_Init(Logger_t *this, LogConfig_t config)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void Logger_ProcessBufferedLogs(Logger_t *this)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void Logger_Log(Logger_t *this, LogLevel_t level,
  const char * const callingFilename, unsigned long callingFileLineNum,
  const char * const formatString, ...)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}
