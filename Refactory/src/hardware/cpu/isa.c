#include<stdint.h>

typedef enum OPERAND_TYPE {
    EMPTY,
    IMM, REG_A, MM_IMM, MM_REG_A, MM_IMM_REG_A,
    MM_REG_A_REG_B, MM_IMM_REG_A_REG_B, MM_REG_A_SCALS,
    MM_IMM_REG_A_SCALS, MM_REG_A_REG_B_SCALS,
    MM_IMM_REG_A_REG_B_SCALS
}od_type_t;

// data structures
typedef enum INST_OPERATOR
{
    INST_MOV,           // 0
    INST_PUSH,          // 1
    INST_POP,           // 2
    INST_LEAVE,         // 3
    INST_CALL,          // 4
    INST_RET,           // 5
    INST_ADD,           // 6
    INST_SUB,           // 7
    INST_CMP,           // 8
    INST_JNE,           // 9
    INST_JMP,           // 10
}op_t;
typedef struct OPERAND_STRUCT {
    od_type_t type;
    int64_t imm;
    int64_t scals;
    uint64_t reg_a;
    uint64_t reg_b;
}od_t;
typedef struct INST_STRUCT
{
    op_t    op;         // enum of operators. e.g. mov, call, etc.
    od_t    src;        // operand src of instruction
    od_t    dst;        // operand dst of instruction
} inst_t;

static uint64_t decode_operand(od_t* od)
{
    uint64_t vaddr = 0;
    switch (od->type)
    {
    case IMM:
        return *((uint64_t *)od->imm); // 这个方法可以统一每次取不同bits
        break;
    case REG_A:
        return od->reg_a;
    case MM_IMM:
        vaddr = od->imm;
        break;
    case MM_REG_A:
        vaddr = *((uint64_t*)od->reg_a);
        break;
    case MM_IMM_REG_A:
        vaddr = od->imm + *((uint64_t*)od->reg_a);
        break;
    case MM_REG_A_REG_B:
        vaddr = *((uint64_t*)od->reg_a) + *((uint64_t*)od->reg_b);
        break;
    case MM_IMM_REG_A_REG_B:
        vaddr = od->imm + *((uint64_t*)od->reg_a) + *((uint64_t*)od->reg_b);
        break;
    case MM_REG_A_SCALS:
        vaddr = od->scals * (*((uint64_t*)od->reg_a));
        break;
    case MM_IMM_REG_A_SCALS:
        vaddr = od->imm + (*((uint64_t*)od->reg_a)) * od->scals;
        break;
    case MM_REG_A_REG_B_SCALS:
        vaddr = *((uint64_t*)od->reg_a) + od->scals * (*((uint64_t*)od->reg_b));
        break;
    case MM_IMM_REG_A_REG_B_SCALS:
        vaddr = od->imm + *((uint64_t*)od->reg_a) + od->scals * (*((uint64_t*)od->reg_b));
        break;
    default:
        return 0;
    }
    return vaddr;
}

#include <headers/cpu.h>
static void parse_instruction(const char* str, inst_t* inst, core_t* cr){}
static void parse_operand(const char* str, od_t* od, core_t* cr){}

static void mov_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void push_handler            (od_t *src_od, od_t *dst_od, core_t *cr);
static void pop_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void leave_handler           (od_t *src_od, od_t *dst_od, core_t *cr);
static void call_handler            (od_t *src_od, od_t *dst_od, core_t *cr);
static void ret_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void add_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void sub_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void cmp_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void jne_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void jmp_handler             (od_t *src_od, od_t *dst_od, core_t *cr);

typedef void (*handler_t)(od_t*, od_t*, core_t*);
static handler_t handler_table[NUM_INSTRTYPE] = {
    &mov_handler,               // 0
    &push_handler,              // 1
    &pop_handler,               // 2
    &leave_handler,             // 3
    &call_handler,              // 4
    &ret_handler,               // 5
    &add_handler,               // 6
    &sub_handler,               // 7
    &cmp_handler,               // 8
    &jne_handler,               // 9
    &jmp_handler,               // 10
};

static inline void reset_cflags(core_t* cr) {
    cr->CF = 0;
    cr->ZF = 0;
    cr->SF = 0;
    cr->OF = 0;
}

static inline void next_rip(core_t* cr) {
    cr->rip += sizeof(char) *  MAX_INSTRUCTION_CHAR;
}