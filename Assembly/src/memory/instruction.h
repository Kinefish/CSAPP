#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <stdint.h>

typedef enum OP {
    ADD_REG_REG,
    MOV_REG_REG, MOV_REG_MEM, MOV_MEM_REG,
    PUSH_REG, POP_REG,
    CALL, RET
}op_t;


typedef enum OD_TYPE {
    EMPTY,
    IMM, REG_A, MM_IMM, MM_REG_A, MM_IMM_REG_A,
    MM_REG_A_REG_B, MM_IMM_REG_A_REG_B, MM_REG_A_SCALS,
    MM_IMM_REG_A_SCALS, MM_REG_A_REG_B_SCALS,
    MM_IMM_REG_A_REG_B_SCALS
}od_type_t;


typedef struct OD {
    od_type_t type;
    int64_t scals;
    int64_t imm;
    uint64_t* reg_a;
    uint64_t* reg_b;
}od_t;


typedef struct INSTRUCT_STRUCT {
    op_t op; //mov, push
    od_t src; 
    od_t dst; 
    char code[100];
}inst_t;

uint64_t decode_od(od_t od);
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
