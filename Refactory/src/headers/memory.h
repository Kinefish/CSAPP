#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include <headers/cpu.h>

/*=================*/
/*  physical memory */
/*=================*/
// 4 + 6 + 6 = 16 bits physical address
// physical space is 2^16 = 65536 bytes = 64KB
#define PHYSICAL_MEMORY_SAPCE 65536
#define MAX_INDEX_PHYSICAL_PAGE 15 //0-15 total 16
//physical memory
uint8_t pm[PHYSICAL_MEMORY_SAPCE]; //64KB


/*======================================*/
/*      memory R/W                      */
/*======================================*/
uint64_t read64bits_dram(uint64_t paddr, core_t* cr);
void write64bits_dram(uint64_t paddr, uint64_t data, core_t* cr);
#endif
