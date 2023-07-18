#ifndef TIME_LOGGING_H_
#define TIME_LOGGING_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {FORMAT_DEFAULT, FORMAT_NULL, FORMAT_TIME} FORMAT;

int logging_vprintf( const char *fmt, va_list l );
void time_logging_init(char * format);

#ifdef __cplusplus
}
#endif

#endif /* TIME_LOGGING_H_ */
