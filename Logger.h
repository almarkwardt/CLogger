#ifndef LOGGER_H
#define LOGGER_H

#include "LogConfig.h"

/** The logger will immediately log to the console, if provided, but
we will buffer messages before writing them to permanent storage. We do
this to save some wear and tear on flash based storage media. The log
buffer can contain up to MAX_BUFFERED_LOG_LINES lines of logs, each of
which can be up to MAX_LOG_LINE_LENGTH bytes in length. If a log line is
longer than MAX_LOG_LINE_LENGTH, it will be truncated. If the log is
not flushed to permanent storage before MAX_BUFFERED_LOG_LINES are logged,
some log messages will be lost. In the event that a log line is truncated
or buffered log messages are overwritten, annotations will be added to the
log to indicate that this has happened. */
#define MAX_BUFFERED_LOG_LINES 2048
#define MAX_LOG_LINE_LENGTH 512

/** A logger object accepts a log config object which tells the logger
how to perform its job. The logger's responsibilities include accepting
strings to be logged from the user, filtering log messages based on provided
log threshold values, timestamping log messages when they are received,
writing log messages to console, buffering log messages intended for
permanent storage, scrambling those log messages, and flushing those
buffered messages to permanent storage at the appropriate interval. */
typedef struct Logger_s
{
  LogConfig_t config;
  char logBuffer[MAX_BUFFERED_LOG_LINES][MAX_LOG_LINE_LENGTH];
  unsigned int logLineLengths[MAX_BUFFERED_LOG_LINES];
  unsigned int nextFreeLogLineIndex;
  unsigned int lastFlushedLogLineIndex;
} Logger_t;

/** Initializes a logger object with the given configuration. */
void Logger_Init(Logger_t *this, LogConfig_t config);

/** Must be called periodically when permanent log storage is enabled
to give the logger an opportunity to flush buffered log text to
permanent storage and manage its buffers. */
void Logger_ProcessBufferedLogs(Logger_t *this);

/** Called to log a string at the given log level. */
void Logger_Log(Logger_t *this, LogLevel_t level,
  const char * const callingFilename, unsigned long callingFileLineNum,
  const char * const formatString, ...);

#endif
