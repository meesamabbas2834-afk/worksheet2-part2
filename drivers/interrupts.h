#ifndef SYS_IDT_H
#define SYS_IDT_H

#include "type.h"

struct idt_ptr_struct {
    u16int limit;
    u32int base;
} __attribute__((packed));

struct gate_descriptor {
    u16int base_low;
    u16int selector;
    u8int  reserved;
    u8int  flags;
    u16int base_high;
} __attribute__((packed));

/* Registers struct for interrupt handler */
struct register_state {
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32int int_no, err_code;
    u32int eip, cs, eflags, useresp, ss;
};

void init_idt();
void isr_33_wrapper(); 

#endif
