#ifndef LOGCONFIG_H
#define LOGCONFIG_H

#include <stdbool.h>

/** Logs stored to persistent storage can be scrambled
using a provided key. That key can be at most MAX_SCRAMBLE_KEY_LENGTH
bytes in length. */
#define MAX_SCRAMBLE_KEY_LENGTH 128

/** This enum describes the log levels that are available.
TRACE - Used for basic program flow logging (lowest level)
WARNING - Used for scenarios that are not ideal but can be handled
ERROR - Used for scenarios that "should never happen" or are serious */
typedef enum LogLevel_e
{
  TRACE,
  WARNING,
  ERROR
} LogLevel_t;

/** A log config object describes how logging should be handled by the logger
and provides function pointers that the logger may call to perform its job. */
typedef struct LogConfig_s
{
  /** Pointer to a function that returns a string timestamp for the current
  time when the function is called. Used to timestamp log messages. Will
  only be called once per log message at the time of logging. Returned
  timestamp string will be copied immediately upon function return. If no
  RTC is available or no timestamping is needed, this may be NULL. */
  void (*GetCurrentTimestamp)(const char ** ppTimestampStr,
    unsigned int *pTimestampLen);

  /** Pointer to a function that accepts a string to write to
  permanent storage and the length of the given string that is to be written.
  Function must return TRUE if the write succeeds and FALSE otherwise.
  The logger module does not need the concept of a filename or filesystem,
  which allows lower level writes to take place if the function you provide
  here is aware of how to accomplish that. If no permanent storage is available
  or if you do not want the logger to write to permanent storage, you may
  assign NULL to this field. */
  bool (*WriteToStorage)(const char * const str, unsigned long len);

  /** Minimum log level to write to permanent storage if permanent storage
  is being used. Only log messages at this level or higher will be stored. */
  LogLevel_t storageLogThreshold;

  /** Pointer to a function that returns a monotonic time value in
  milliseconds. This field MUST be provided if WriteToStorage is used.
  It is used to determine when log lines should be flushed
  to permanent storage. */
  unsigned long long (*GetMonotonicTimeMillis)(void);

  /** The interval in milliseconds at which the logger should flush
  log messages to permanent storage. Relevant only when WriteToStorage is
  set. If this field is zero and WriteToStorage is set, log lines will be
  flushed immediately upon logging. */
  unsigned long long flushIntervalMillis;

  /** The key to use to scramble log text before writing to permanent storage.
  THIS KEY WILL BE STORED IN PLAINTEXT! IT SHOULD NOT BE SENSITIVE INFORMATION!
  If no scrambling is needed, fill this field with 0x00. */
  unsigned char scrambleKey[MAX_SCRAMBLE_KEY_LENGTH];

  /** The length of the key used for scrambling, in bytes.
  If no scrambling is needed, set this field to zero. */
  unsigned int scrambleKeyLength;

  /** If the logger will start appending to an existing stream and scrambling
  is used, this field must contain the initial offset within the existing
  stream where the logger will start. If this is not set correctly, it will
  not be possible to unscramble the log. */
  unsigned long initialStreamOffsetBytes;

  /** Pointer to a function that accepts a string to write to
  the console and the length of the given string that is to be written.
  If no console is available or if you do not want the logger to write
  to the console, you may assign NULL to this field. Log lines will be
  flushed to console immediately upon logging, and they will not be
  scrambled, even if scrambling is enabled for permanent storage. */
  void (*WriteToConsole)(const char * const str, unsigned long len);

  /** Minimum log level to write to console if console logging is
  being used. Only log messages at this level or higher will be written
  to the console. */
  LogLevel_t consoleLogThreshold;
} LogConfig_t;

/** Initializes a logger config. Blanks out/disables everything. */
void LogConfig_Init(LogConfig_t *this);

/** Sets up console logging in the given config object using
the given parameters. */
void LogConfig_EnableConsole(LogConfig_t *this,
  void (*writeFunc)(const char * const, unsigned long),
  LogLevel_t threshold);

/** Sets up permanent storage in the given config object using the
given parameters. */
void LogConfig_EnableStorage(LogConfig_t *this,
  bool (*writeFunc)(const char * const, unsigned long),
  LogLevel_t threshold,
  unsigned long long (*monoTimeFunc)(void),
  unsigned long long flushIntervalMillis);

/** Sets up timestamping in the given config object using the
given parameters. */
void LogConfig_EnableTimestamps(LogConfig_t *this,
  void (*timestampFunc)(const char **, unsigned int *));

/** Sets up scrambling in the given config object using the
given parameters. */
void LogConfig_EnableScrambling(LogConfig_t *this,
  const unsigned char *key,
  unsigned int keyLength,
  unsigned long streamOffset);

/** Turns off the console for the given config object. */
void LogConfig_DisableConsole(LogConfig_t *this);

/** Turns off permanent storage for the given config object. */
void LogConfig_DisableStorage(LogConfig_t *this);

/** Turns off timestamping for the given config object. */
void LogConfig_DisableTimestamps(LogConfig_t *this);

/** Turns off scrambling for the given config object. */
void LogConfig_DisableScrambling(LogConfig_t *this);

#endif
