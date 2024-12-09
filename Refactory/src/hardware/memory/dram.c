#include "dram.h"

#define SRAM_SETTING 0

uint8_t mm[MM_LEN];
uint64_t read64bits_dram(uint64_t paddr) {
    if(SRAM_SETTING == 1)
        return 0x0;
    return *(uint64_t *)&mm[paddr];
}

/*
mm[]是uint8_t，往paddr地址开始存入64位数据
*/
void write64bits_dram(uint64_t paddr, uint64_t data) {
    if(SRAM_SETTING == 1)
        return;
    for(int i = 0; i < 8; i++) {
        mm[paddr + i] = (data >> (i * 8)) & 0xff;
    }
}