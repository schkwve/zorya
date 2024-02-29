/**
 * @file utils/logging.c
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 28/02/2024
 * @brief Logging implementation
 */

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "logging.h"

/**
 * @brief Log Level strings
 */
static const char *log_level_str[] = {
  "TRACE",
  "DEBUG",
  "INFO",
  "WARN",
  "ERROR",
  "FATAL"
};

/**
 * @brief Log Level color escape sequences
 */
static const char *log_level_col[] = {
  "\x1b[94m",
  "\x1b[36m",
  "\x1b[32m",
  "\x1b[33m",
  "\x1b[31m",
  "\x1b[35m"
};

/**
 * @brief Private logger implementation, this function should never be called.
 *        Use log_<level> macros instead.
 *
 * @param level
 *        Log level. All log levels are defined in logging.h.
 *
 * @param file
 *        The file where the log call takes place.
 *
 * @param line
 *        The line where the log call takes place.
 *
 * @param fmt
 *        Format string
 *
 * @param ...
 *        Optional arguments
 */
void log_impl(int level, const char *file, int line, const char *fmt, ...)
{
  if (level < LOG_MIN_LEVEL)
    return;

  va_list ap;
  va_start(ap, fmt);

  // set up time
  time_t t = time(NULL);
  struct tm *cur_time = localtime(&t);

  // print to stderr
  char time_buf[16];
  size_t time_end = strftime(time_buf, sizeof(time_buf), "%H:%M:%S", cur_time);
  time_buf[time_end] = '\0';

  fprintf(stderr, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ", time_buf, log_level_col[level], log_level_str[level], file, line);

  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");

  va_end(ap);
}
