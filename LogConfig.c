#include "LogConfig.h"
#include <stdio.h>

/*******************************************/
void LogConfig_Init(LogConfig_t *this)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_EnableConsole(LogConfig_t *this,
  void (*writeFunc)(const char * const, unsigned long),
  LogLevel_t threshold)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_EnableStorage(LogConfig_t *this,
  bool (*writeFunc)(const char * const, unsigned long),
  LogLevel_t threshold,
  unsigned long long (*monoTimeFunc)(void),
  unsigned long long flushIntervalMillis)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_EnableTimestamps(LogConfig_t *this,
  void (*timestampFunc)(const char **, unsigned int *))
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_EnableScrambling(LogConfig_t *this,
  const unsigned char *key,
  unsigned int keyLength,
  unsigned long streamOffset)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_DisableConsole(LogConfig_t *this)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_DisableStorage(LogConfig_t *this)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_DisableTimestamps(LogConfig_t *this)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}

/*******************************************/
void LogConfig_DisableScrambling(LogConfig_t *this)
{
  printf("%s:%u not implemented\n", __FILE__, __LINE__);
}
