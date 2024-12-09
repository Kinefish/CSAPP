#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <stdint.h>

void init_handler();
void instruction_cycle();


#define NUM_INSTRUCTION 8
typedef void (*handler_t)(uint64_t, uint64_t);
extern handler_t handler_table[NUM_INSTRUCTION];

void add_reg_reg(uint64_t, uint64_t);
void mov_reg_reg(uint64_t, uint64_t);
void call(uint64_t, uint64_t);
void push(uint64_t, uint64_t);
void mov_reg_mem(uint64_t, uint64_t);
void mov_mem_reg(uint64_t, uint64_t);
void pop(uint64_t, uint64_t);
void ret(uint64_t, uint64_t);

#endif
