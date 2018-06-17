#ifndef _PILAB_LOG_H
#define _PILAB_LOG_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
	SILENT = 0,
	ERROR = 1,
	WARNING = 2,
	NOTICE = 3,
	INFO = 4,
	DEBUG = 5,
} t_pilab_log_priority;

typedef enum {
	OFF = 0,
	ON = 1,
} t_pilab_log_colors;

void pilab_log_init(logger_priority_t priority);
void pilab_log_set_priority(logger_priority_t priority);
void pilab_log_toggle_colors(logger_colors_t mode);
t_pilab_log_priority logger_get_priority(void);
size_t _localtime(char *buf, size_t size);

void _pilab_log_abort(const char *filepath, int line, const char *format, ...)
	__attribute__((format(printf, 3, 4)));
#define pilab_log_abort(FMT, ...)                                              \
	_pilab_log_abort(__FILE__, __LINE__, FMT, ##__VA_ARGS__)

void _pilab_log(const char *filepath, int line, logger_priority_t priority,
		const char *format, ...) __attribute__((format(printf, 4, 5)));
#define pilab_log(PRIORITY, FMT, ...)                                          \
	_pilab_log(__FILE__, __LINE__, PRIORITY, FMT, ##__VA_ARGS__)

bool _pilab_log_assert(bool condition, const char *filepath, int line,
		       const char *format, ...)
	__attribute__((format(printf, 4, 5)));
#define pilab_log_assert(COND, FMT, ...)                                       \
	_pilab_log_assert(COND, __FILE__, __LINE__, "%s: " FMT,                \
			  __PRETTY_FUNCTION__, ##__VA_ARGS__)

#endif
