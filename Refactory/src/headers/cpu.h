#ifndef __CPU_H__
#define __CPU_H__
#include <stdio.h>
#include <stdint.h>

/*===================*/
/*     REGISTER      */
/*===================*/
typedef struct REGISTER_STRUCT {
    // return value
    union {
        struct {
            uint8_t al;
            uint8_t ah;
        };        
        uint16_t ax;
        uint32_t eax;
        uint64_t rax;
    };   
    
    //callee saved
    union {
        struct {
            uint8_t bl;
            uint8_t bh;
        };
        uint16_t bx;
        uint32_t ebx;
        uint64_t rbx;
    };

    //1st argument rdi
    union {
        struct {
            uint8_t dil;
            uint8_t dih;
        };
        uint16_t di;
        uint32_t edi;
        uint64_t rdi;
    };
    //2nd argument rsi
    union {
        struct {
            uint8_t sil;
            uint8_t sih;
        };
        uint16_t si;
        uint32_t esi;
        uint64_t rsi;
    };
    //3th argument rdx
    union {
        struct {
            uint8_t dl;
            uint8_t dh;
        };
        uint16_t dx;
        uint32_t edx;
        uint64_t rdx;
    };
    //4th argument rcx
    union {
        struct {
            uint8_t cl;
            uint8_t ch;
        };
        uint16_t cx;
        uint32_t ecx;
        uint64_t rcx;
    };

    //stack frame bottom rbp
    union {
        uint16_t bp;
        uint32_t ebp;
        uint64_t rbp;
    };
    //stack frame top rsp
    union {
        uint16_t sp;
        uint32_t esp;
        uint64_t rsp;
    };
    //pc rip
    union {
        uint16_t ip;
        uint32_t eip;
        uint64_t rip;
    }; 

    //5th argument r8
    union {
        struct {
            uint8_t r8b_low;
            uint8_t r8b_high;
        };
        uint16_t r8w;
        uint32_t r8d;
        uint64_t r8;
    };
    // 6th argument r9
    union {
        struct {
            uint8_t r9b_low;
            uint8_t r9b_high;
        };
        uint16_t r9w;
        uint32_t r9d;
        uint64_t r9;
    };

    //caller saved r10
    union {
        struct {
            uint8_t r10b_low;
            uint8_t r10b_high;
        };
        uint16_t r10w;
        uint32_t r10d;
        uint64_t r10;
    };
    //caller saved r11
    union {
        struct {
            uint8_t r11b_low;
            uint8_t r11b_high;
        };
        uint16_t r11w;
        uint32_t r11d;
        uint64_t r11;
    };

    /*
        callee saved r12-r15
    */
    union {
        struct {
            uint8_t r12b_low;
            uint8_t r12b_high;
        };
        uint16_t r12w;
        uint32_t r12d;
        uint64_t r12;
    };

    union {
        struct {
            uint8_t r13b_low;
            uint8_t r13b_high;
        };
        uint16_t r13w;
        uint32_t r13d;
        uint64_t r13;
    };

    union {
        struct {
            uint8_t r14b_low;
            uint8_t r14b_high;
        };
        uint16_t r14w;
        uint32_t r14d;
        uint64_t r14;
    };

    union {
        struct {
            uint8_t r15b_low;
            uint8_t r15b_high;
        };
        uint16_t r15w;
        uint32_t r15d;
        uint64_t r15;
    };

}reg_t;
extern reg_t reg;

/*===================*/
/*     SRAM(CACHE)   */
/*===================*/
/*
The components of a SRAM cache address:
Note: SRAM cache address is the translated physical address
|   TAG_LEN     |   INDEX_LEN   |   OFFSET_LEN  |
+---------------+---------------+---------------+
|   tag         |   index       |   offset      |
+---------------+---------------+---------------+
|   ADDR_LEN                                    |
*/

/*===================*/
/*     CPU(CORE)     */
/*===================*/
typedef struct CORE_STRUCT {
    //rip in cpu_core
    union {
        uint32_t eip;
        uint64_t rip;
    };

    /*
        condition code

        integer arithmetic instructions

        inc     increment 1
        dec     decrement 1
        neg     negate
        not     complement
    
        add     add
        sub     substract
        imul    muliply
        xor     exclusive or
        or      or
        and     and

        sal     left shift
        shl     left shift  (same as sal)
        sar     arithmetic right shift
        shr     logical right shift

        comparison and test instruction
        cmp     compare
        test    test    
    */
   
    /*
        carry flag: detect overflow for unsigned operations
    */
   uint32_t CF;
   /*
        overflow flag: detect overflow for signed operations
   */
   uint32_t OF;

   /*
        zero flag: result is zero
   */
   uint32_t ZF;
   /*
        sign flag: result is negative:highest bit
   */
   uint32_t SF;
   
   // register files
   reg_t reg;

   //page directory base register
   uint64_t pdbr;
}core_t;
extern core_t core;

// define cpu core array to support core level parallelism
#define NUM_CORES 1
core_t cores[NUM_CORES];

// active core for current task
uint64_t ACTIVE_CORE;

#define MAX_INSTRUCTION_CHAR 64
#define NUM_INSTRTYPE 14

void instruction_cycle(core_t* cr);

//translate the virtual address to physical address in MMU;
//each MMU is owned by each core
uint64_t va2pa(uint64_t vaddr, core_t* cr);
#endif
