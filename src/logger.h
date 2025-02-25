#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define LOG_COLOR_RESET   "\x1b[0m"
#define LOG_COLOR_RED     "\x1b[31m"
#define LOG_COLOR_GREEN   "\x1b[32m"
#define LOG_COLOR_YELLOW  "\x1b[33m"
#define LOG_COLOR_BLUE    "\x1b[34m"
#define LOG_COLOR_CYAN    "\x1b[36m"

#define LOG_ERROR(fmt, ...)   fprintf(stderr, LOG_COLOR_RED "[ERROR] " fmt LOG_COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)    fprintf(stderr, LOG_COLOR_YELLOW "[WARN] " fmt LOG_COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)    fprintf(stdout, LOG_COLOR_GREEN "[INFO] " fmt LOG_COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)   fprintf(stdout, LOG_COLOR_CYAN "[DEBUG] " fmt LOG_COLOR_RESET "\n", ##__VA_ARGS__)

#endif // LOGGER_H
