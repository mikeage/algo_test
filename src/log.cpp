#include "log.h"
#include "stdarg.h"
#include "stdio.h"

#define MAX_LINE 1024
void debug_print(int level, const char * file, int line, const char * fmt, ...)
{
	char buf[MAX_LINE];
	int len;
	va_list ap;

	len=snprintf(buf, sizeof(buf), "%s:%d ", file, line);
	switch(level) {
		case LEVEL_INFO:
			len+=snprintf(buf+len, sizeof(buf)-len, "INFO ");
			break;
		case LEVEL_WARNING:
			len+=snprintf(buf+len, sizeof(buf)-len, "WARNING ");
			break;
		case LEVEL_ERROR:
			len+=snprintf(buf+len, sizeof(buf)-len, "ERROR ");
			break;
		default:
			len+=snprintf(buf+len, sizeof(buf)-len, "??? ");
			break;
	}
	va_start(ap, fmt);
	len+=vsnprintf(buf+len, sizeof(buf)-len, fmt, ap);
	va_end(ap);

	printf("%s\n", buf);
}

