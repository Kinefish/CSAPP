#include <stdint.h>
#include "./code.h"
#include "../cpu/register.h"

inst_t program[INST_LEN] = {
    {
        PUSH_REG,
        {REG_A, 0, 0, (uint64_t *)&reg.rbp, NULL},
        {EMPTY, 0, 0, NULL, NULL},
        "push rbp"
    },
    {
        MOV_REG_REG,
        {REG_A, 0, 0, (uint64_t *)&reg.rsp, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rbp, NULL},
        "mov rsp rbp"
    },
    {
        MOV_REG_MEM,
        {REG_A, 0, 0, (uint64_t *)&reg.rdi, NULL},
        {MM_IMM_REG_A, 0, -0x18, (uint64_t *)&reg.rbp, NULL},
        "mov rdi -0x18(rbp)"
    },
    {
        MOV_REG_MEM,
        {REG_A, 0, 0, (uint64_t *)&reg.rsi, NULL},
        {MM_IMM_REG_A, 0, -0x20, (uint64_t *)&reg.rbp, NULL},
        "mov rsi -0x20(rbp)"
    },
    {
        MOV_MEM_REG,
        {MM_IMM_REG_A, 0, -0x18, (uint64_t *)&reg.rbp, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rdx, NULL},
        "mov -0x18(rbp) rdx"
    },
    {
        MOV_MEM_REG,
        {MM_IMM_REG_A, 0, -0x20, (uint64_t *)&reg.rbp, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rax, NULL},
        "mov -0x20(rbp) rax"
    },
    {
        ADD_REG_REG,
        {REG_A, 0, 0, (uint64_t *)&reg.rdx, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rax, NULL},
        "add rdx rax"
    },
    {
        MOV_REG_MEM,
        {REG_A, 0, 0, (uint64_t *)&reg.rax, NULL},
        {MM_IMM_REG_A, 0, -0x8, (uint64_t *)&reg.rbp, NULL},
        "mov rax -0x8(rbp)"
    },
    {
        MOV_MEM_REG,
        {MM_IMM_REG_A, 0, -0x8, (uint64_t *)&reg.rbp, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rax, NULL},
        "mov -0x8(rbp) rax"
    },
    {
        POP_REG,
        {EMPTY, 0 , 0, NULL, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rbp, NULL},
        "pop rbp"
    },
    {
        RET,
        {EMPTY, 0, 0, NULL, NULL},
        {EMPTY, 0, 0, NULL, NULL},
        "retq"
    },
    /*
    main entry point
    */
    {
        MOV_REG_REG,
        {REG_A, 0, 0, (uint64_t *)&reg.rdx, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rsi, NULL},
        "mov rdx rsi"
    },
    {
        MOV_REG_REG,
        {REG_A, 0, 0, (uint64_t *)&reg.rax, NULL},
        {REG_A, 0, 0, (uint64_t *)&reg.rdi, NULL},
        "mov rax rdi"
    },
    {
        CALL,
        {IMM, 0, (uint64_t)&program[0], NULL, NULL},
        {EMPTY, 0, 0, NULL, NULL},
        "call 5fa <add>"
    },
    {
        MOV_REG_MEM,
        {REG_A, 0, 0, (uint64_t *)&reg.rax, NULL},
        {MM_IMM_REG_A, 0, -0x8, (uint64_t *)&reg.rbp, NULL},
        "mov rax -0x8(rbp)"
    },
};