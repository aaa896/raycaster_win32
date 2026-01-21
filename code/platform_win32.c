#include "platform.h"
#include "mytypedefs.h"
#include <windows.h>

void *platform_alloc(u64 size) {
    return  VirtualAlloc(0, size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
}

f64 platform_get_time_milliseconds() {   
    static LARGE_INTEGER frequency = {0};
    if (!frequency.QuadPart) { QueryPerformanceFrequency(&frequency);}

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    return (f64)counter.QuadPart * 1.0 / (f64)frequency.QuadPart;
}
