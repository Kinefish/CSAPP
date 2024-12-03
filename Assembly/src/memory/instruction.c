#include "instruction.h"
handler_t handler_table[NUM_INSTRUCTION];

#include "../cpu/mmu.h"
#include "../cpu/register.h"
uint64_t decode_od(od_t od)
{
    uint64_t vaddr = 0;
    switch (od.type)
    {
    case IMM:
        return *((uint64_t *)&od.imm); // 这个方法可以统一每次取不同bits
        break;
    case REG_A:
        return (uint64_t)od.reg_a;
    case MM_IMM:
        vaddr = od.imm;
        break;
    case MM_REG_A:
        vaddr = *od.reg_a;
        break;
    case MM_IMM_REG_A:
        vaddr = od.imm + *od.reg_a;
        break;
    case MM_REG_A_REG_B:
        vaddr = *od.reg_a + *od.reg_b;
        break;
    case MM_IMM_REG_A_REG_B:
        vaddr = od.imm + *od.reg_a + *od.reg_b;
        break;
    case MM_REG_A_SCALS:
        vaddr = od.scals * (*od.reg_a);
        break;
    case MM_IMM_REG_A_SCALS:
        vaddr = od.imm + (*od.reg_a) * od.scals;
        break;
    case MM_REG_A_REG_B_SCALS:
        vaddr = *od.reg_a + od.scals * (*od.reg_b);
        break;
    case MM_IMM_REG_A_REG_B_SCALS:
        vaddr = od.imm + *od.reg_a + od.scals * (*od.reg_b);
        break;
    default:
        return vaddr;
    }
    return vaddr;
}

void mov_reg_reg(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst = *(uint64_t *)src;
    reg.rip += sizeof(inst_t);
}

void add_reg_reg(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst += *(uint64_t *)src;
    reg.rip += sizeof(inst_t);
}

#include "dram.h"

void mov_reg_mem(uint64_t src, uint64_t dst)
{
    /*
        src reg
        dst mem vaddr
    */
    write64bits_dram(
        va2pa(dst),
        *(uint64_t *)src);
    reg.rip += sizeof(inst_t);
}

void mov_mem_reg(uint64_t src, uint64_t dst)
{
    /*
        src mem vaddr
        dst reg
    */
    *(uint64_t *)dst = read64bits_dram(va2pa(src));
    reg.rip += sizeof(inst_t);
}

void push(uint64_t src, uint64_t dst)
{
    /*
        src reg
        dst empty
        push command default push (%rsp)
    */
    reg.rsp -= 0x8;
    write64bits_dram(
        va2pa(reg.rsp), *(uint64_t *)src);
    reg.rip += sizeof(inst_t);
}

void pop(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst = (uint64_t)read64bits_dram(va2pa(reg.rsp));
    reg.rsp += 0x8;
    reg.rip += sizeof(inst_t);
}

void call(uint64_t src, uint64_t dst)
{
    // src imm
    /*
        1. rsp - 8
        2. write return address into rsp (push stack), stack frame in mm[]
        3. rip point to imm
    */
    reg.rsp -= 0x8;
    write64bits_dram(
        va2pa(reg.rsp), reg.rip + sizeof(inst_t));
    reg.rip = src; //(uint64_t)&program[0]
}

#include "disk/code.h"
void ret(uint64_t src, uint64_t dst)
{
    uint64_t ret_addr = read64bits_dram(va2pa(reg.rsp));
    reg.rsp += 0x8;
    reg.rip = ret_addr;
}

void init_handler()
{
    handler_table[ADD_REG_REG] = add_reg_reg;

    handler_table[MOV_REG_REG] = mov_reg_reg;
    handler_table[MOV_MEM_REG] = mov_mem_reg;
    handler_table[MOV_REG_MEM] = mov_reg_mem;

    handler_table[PUSH_REG] = push;
    handler_table[POP_REG] = pop;

    handler_table[CALL] = call;
    handler_table[RET] = ret;
}

#include <stdio.h>
#include "../disk/elf.h"
#include "../utils/utils.h"
/*
    1.取指
    2.译码
    3.执行
    4.更新pc（rip）
*/
void instruction_cycle() {
    inst_t *instr = (inst_t *)reg.rip;
    printf("%s\n", instr->code);
    uint64_t src = decode_od(instr->src); // physical address
    uint64_t dst = decode_od(instr->dst); // physical address
    handler_t handler = handler_table[instr->op];
    handler(src, dst);
}