#include <stdio.h>
#include "./utils/utils.h"
#include "./cpu/mmu.h"
#include "./memory/dram.h"
#include "./cpu/register.h"
#include "./disk/code.h"
#include "./memory/instruction.h"

void verify();
int verify_register();
int verify_mm();
int main() {
    
    init_handler();

    reg.rax = 0x12340000;
    reg.rbx = 0x0;
    reg.rcx = 0x08000660;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7ffffffee2f8;
    reg.rdi = 0x1;
    reg.rbp = 0x7ffffffee210;
    reg.rsp = 0x7ffffffee1f0;

    reg.rip = (uint64_t)&program[11];

    write64bits_dram(va2pa(0x7ffffffee210), 0x08000660); //rbp
    write64bits_dram(va2pa(0x7ffffffee208), 0x0);
    write64bits_dram(va2pa(0x7ffffffee200), 0xabcd);
    write64bits_dram(va2pa(0x7ffffffee1f8), 0x12340000);
    write64bits_dram(va2pa(0x7ffffffee1f0), 0x08000660); //rsp

    printf_register();
    printf_stack();

    for(int i = 0; i < INST_LEN; i++) {
        instruction_cycle();
        printf_register();
        printf_stack();
    }

    verify();

    return 0;
}

void verify() {
    char* ret = (char *)malloc(sizeof(char));
    ret = verify_register() == 1 ? "register matched" : "register not matched";
    puts(ret);
    ret = verify_mm() == 1 ? "memory matched" : "memory not matched";
    puts(ret);
}
int verify_register() {
    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x0);
    match = match && (reg.rcx == 0x08000660);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7ffffffee210);
    match = match && (reg.rsp == 0x7ffffffee1f0);

    return match;
}
int verify_mm() {
    int match = 1;
    match = match && (read64bits_dram(va2pa(0x7ffffffee210)) == 0x08000660); //rbp
    match = match && (read64bits_dram(va2pa(0x7ffffffee208)) == 0x1234abcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffee200)) == 0xabcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffee1f8)) == 0x12340000);
    match = match && (read64bits_dram(va2pa(0x7ffffffee1f0)) == 0x08000660); //rsp
    
    return match;
}