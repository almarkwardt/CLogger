#include "LogMacros.h"
#include <string.h>
#include <stdio.h>

/** This is my fake monotonic timer function. */
unsigned long long TimeMillis(void)
{
  static unsigned long long millis = 0;

  return millis++;
}

/** This is my fake RTC/timestamper function. */
static void Timestamp(const char ** ppTimestampStr, unsigned int *pTimestampLen)
{
  static char time[128] = {0};

  sprintf(time, "00:00:%llu", TimeMillis());
  *ppTimestampStr = time;
  *pTimestampLen = strlen(time);
}

/** This is my fake permanent storage function. */
bool Storage(const char * const str, unsigned long len)
{
  printf("StorePermanently:");
  printf("%s", str);
  printf("\n");

  return true;
}

/** This is the global log pointer that the macro helpers
expect to have. I'll init it to NULL and then assign it
once I've actually created a logger object. */
Logger_t *g_pLogger = 0;

/** I'll instantiate a logger object, assign the global
pointer, and we should be able to rock and roll using the
macros defined in LogMacros.h */
int main()
{
  LogConfig_t myLoggerConfig;
  Logger_t myLogger;

  LogConfig_Init(&myLoggerConfig);
  // I want permanent storage, scrambling, and timestamps,
  // but I do not have a console to write to, so I don't need that.
  // I want everything to get logged, so I'll use TRACE as the threshold,
  // and I want to be gentle with my storage medium, so I'll only flush
  // every five seconds. For scrambling, say this is a brand new log file
  // and therefore I won't have any stream offset.
  LogConfig_EnableStorage(&myLoggerConfig, Storage, TRACE, TimeMillis, 5000);
  LogConfig_EnableTimestamps(&myLoggerConfig, Timestamp);
  LogConfig_EnableScrambling(&myLoggerConfig, "NotVerySecure", 13, 0);

  // Set up the logger using the configuration I made, and once that's done,
  // we can assign the global pointer for the macros and get started.
  Logger_Init(&myLogger, myLoggerConfig);
  g_pLogger = &myLogger;

  LOG_TRACE("This is a test of trace, called from %s", "main()");
  LOG_WARN("I don't like odd numbers like %d, %d, or %d", 1, 3, 5);
  LOG_ERROR("I cannot tolerate even numbers like %d, %d or %d, whatsoever!", 2, 4, 6);

  return 0;
}
