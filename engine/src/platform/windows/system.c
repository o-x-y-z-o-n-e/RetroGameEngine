#ifdef SYS_WINDOWS
#include "platform/system.h"
#include <windows.h>


//------------------------------------------------------------------------------


uint64_t get_current_time() {
	LARGE_INTEGER freq;
	LARGE_INTEGER counter;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);

	return (counter.QuadPart * 1000LL) / freq.QuadPart;
}

#endif