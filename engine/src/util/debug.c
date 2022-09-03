#ifdef EXC_DEBUG

#include <stdarg.h>
#include <stdio.h>


//------------------------------------------------------------------------------


static void log_base(const char* prefix, const char* format, va_list args) {
	char buffer[256];
	#ifdef SYS_WINDOWS
	vsprintf_s(buffer, 256, format, args);
	#else
	vsprintf(buffer, format, args);
	#endif
	printf("[%s] %s\n", prefix, buffer);
}


//------------------------------------------------------------------------------


void log_info(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_base("INFO", format, args);
	va_end(args);
}


//------------------------------------------------------------------------------


void log_warning(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_base("WARNING", format, args);
	va_end(args);
}


//------------------------------------------------------------------------------


void log_error(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_base("ERROR", format, args);
	va_end(args);
}

#else

void log_info(const char* format, ...) {}
void log_warning(const char* format, ...) {}
void log_error(const char* format, ...) {}

#endif