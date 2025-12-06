#include "interrupts.h"
#include "pic.h"
#include "io.h"
#include "frame_buffer.h"
#include "keyboard.h"

struct gate_descriptor idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void load_idt_asm(u32int);
extern void isr_33_wrapper();

void set_idt_gate(u8int num, u32int base, u16int sel, u8int flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].selector = sel;
    idt_entries[num].reserved = 0;
    idt_entries[num].flags = flags;
}

void init_idt() {
    idt_ptr.limit = sizeof(struct gate_descriptor) * 256 - 1;
    idt_ptr.base  = (u32int)&idt_entries;

    /* Set default gates to 0 */
    // (Optional loop here if needed, but globals are 0 initialized)

    /* Install Keyboard ISR (IRQ1 -> INT 33) */
    set_idt_gate(33, (u32int)isr_33_wrapper, 0x08, 0x8E);

    /* Load IDT */
    load_idt_asm((u32int)&idt_ptr);

    /* Remap PIC using macros from updated pic.h */
    /* Note: Using OFFSET_MASTER (0x20) and OFFSET_SLAVE (0x28) */
    pic_remap(OFFSET_MASTER, OFFSET_SLAVE);

    /* Unmask Keyboard (IRQ1) */
    outb(MASTER_PIC_DATA, 0xFD);

    /* Enable interrupts */
    asm volatile("sti");
}

/* Updated Interrupt Handler */
void handle_interrupt(struct register_state regs) {
    if (regs.int_no == 33) {
        u8int sc_code = get_scancode();
        u8int ascii_char = scancode_to_char(sc_code);

        if (ascii_char != 0) {
            char tmp_buff[2];
            tmp_buff[0] = ascii_char;
            tmp_buff[1] = 0;
            
            /* Using new color macro COLOR_WHT */
            fb_write(tmp_buff, 1, COLOR_WHT);
        }

        pic_acknowledge(33);
    }
}
