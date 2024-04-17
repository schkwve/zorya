/**
 * Copyright (c) 2024 Zorya Browser
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTILS_LOGGING_H
#define UTILS_LOGGING_H

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

#endif /* UTILS_LOGGING_H */
