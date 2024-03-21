/**
 * @file utils/logging.h
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 28/02/2024
 * @brief Logging functionality
 */

#ifndef LOG_LOGGING_H
#define LOG_LOGGING_H

#include <stdarg.h>

/**
 * @brief Log levels
 */
enum
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

#if ENABLE_TRACE_LOGGING == 1
#define LOG_MIN_LEVEL (LOG_TRACE)
#else
#if defined(__DEBUG)
#define LOG_MIN_LEVEL (LOG_DEBUG)
#else
#define LOG_MIN_LEVEL (LOG_INFO)
#endif
#endif

/**
 * @brief Prints a log with the TRACE log level.
 */
#define log_trace(...) log_impl(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)

/**
 * @brief Prints a log with the DEBUG log level.
 */
#define log_debug(...) log_impl(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

/**
 * @brief Prints a log with the INFO log level.
 */
#define log_info(...) log_impl(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)

/**
 * @brief Prints a log with the WARN log level.
 */
#define log_warn(...) log_impl(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)

/**
 * @brief Prints a log with the ERROR log level.
 */
#define log_error(...) log_impl(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

/**
 * @brief Prints a log with the FATAL log level.
 */
#define log_fatal(...) log_impl(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_impl(int level, const char *file, int line, const char *fmt, ...);

#endif /* LOG_LOGGING_H */
