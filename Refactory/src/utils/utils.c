#include "./utils.h"
#include "../cpu/register.h"
#include "../memory/dram.h"
void printf_register() {
    printf("rax = %16lx\trbx = %16lx\trcx = %16lx\trdx = %16lx\n",
        reg.rax, reg.rbx, reg.rcx, reg.rdx);
    printf("rsi = %16lx\trdi = %16lx\trbp = %16lx\trsp = %16lx\n",
        reg.rsi, reg.rdi, reg.rbp, reg.rsp);
    printf("rip = %16lx\n", reg.rip);
}

/*
    memory of rbp -> rsp
*/
void printf_stack() {
    int n = STACK_RANGE;

    uint64_t* high = (uint64_t *)&mm[va2pa(reg.rsp)];
    high = &high[n];

    uint64_t rsp_start = reg.rsp + n * 8; // 8bytes
    for(int i = 0; i < 2*n; i++) {
        uint64_t* ptr = (uint64_t *)(high - i);
        printf("0x%lx : %16lx", rsp_start, (uint64_t)*ptr);

        if(i == n) printf(" <== rsp");
        rsp_start -= 8;
        printf("\n");
    }
}