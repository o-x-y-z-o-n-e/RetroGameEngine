#ifdef EXC_DEBUG

#include <stdarg.h>
#include <stdio.h>


//------------------------------------------------------------------------------


void log(const char* prefix, const char* format, va_list args) {
	char buffer[256];
	vsprintf_s(buffer, 256, format, args);
	printf("[%s] %s\n", prefix, buffer);
}


//------------------------------------------------------------------------------


void log_info(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log("INFO", format, args);
	va_end(args);
}


//------------------------------------------------------------------------------


void log_warning(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log("WARNING", format, args);
	va_end(args);
}


//------------------------------------------------------------------------------


void log_error(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log("ERROR", format, args);
	va_end(args);
}

#else

void log_info(const char* format, ...) {}
void log_warning(const char* format, ...) {}
void log_error(const char* format, ...) {}

#endif