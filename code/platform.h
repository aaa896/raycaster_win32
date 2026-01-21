#ifndef PLATFORM_H_
#define PLATFORM_H_
#include "mytypedefs.h"

void *platform_alloc(u64 size);


f64 platform_get_time_milliseconds();

#endif // PLATFORM_H_
