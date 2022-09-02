#ifdef SYS_MACOSX

#include "platform/system.h"

/* DEPRECATED
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

uint64_t get_current_time() {
    uint64_t time = mach_absolute_time();
    
    Nanoseconds nano = AbsoluteToNanoseconds(*(AbsoluteTime*)&time);

    return (*(uint64_t*)&nano)/1000/1000;
}
*/

#include <time.h>
uint64_t get_current_time() {
    struct timespec time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);

    return (time.tv_sec * 1000) + (time.tv_nsec / 1000000);
}


#endif