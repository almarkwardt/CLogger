#ifndef LOGMACROS_H
#define LOGMACROS_H

#include "Logger.h"

extern Logger_t *g_pLogger;

#define LOG_TRACE(...) Logger_Log(g_pLogger, TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) Logger_Log(g_pLogger, WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) Logger_Log(g_pLogger, ERROR, __FILE__, __LINE__, __VA_ARGS__)

#endif
