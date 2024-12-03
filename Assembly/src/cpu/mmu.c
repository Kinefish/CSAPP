/*
    内存管理单元
    实现对虚拟地址对物理地址的映射
*/
#include "mmu.h"
#include "./memory/dram.h"
#include <stdio.h> 
uint64_t va2pa(uint64_t vaddr) {
    return vaddr % MM_LEN;
}