#ifndef __DEBUG_H__
#define __DEBUG_H__

/*
each bit in uint64_t state express DEBUG_LEVEL
*/
#define DEBUG_INSTRUCTIONCYCLE      0x1
#define DEBUG_REGISTERS             0x2
#define DEBUG_PRINTSTACK            0x4
#define DEBUG_PRINTCACHESET         0x8
#define DEBUG_CACHEDETAILS          0x10
#define DEBUG_MMU                   0x20
#define DEBUG_LINKER                0x40
#define DEBUG_LOADER                0x80
#define DEBUG_PARSEINST             0x100

#define DEBUG_VERBOSE_SET  DEBUG_INSTRUCTIONCYCLE

// do page walk
#define DEBUG_ENABLE_PAGE_WALK      0
// use sram cache for memory access 
#define DEBUG_ENABLE_SRAM_CACHE     0

#include <stdint.h>
//printf wrapper
uint64_t debug_printf(uint64_t open_set, const char* format, ...);

//type convert
uint32_t uint2float(uint32_t u);
uint64_t string2uint(const char* str);
uint64_t string2uint_range(const char* str, int start, int end);

#endif
