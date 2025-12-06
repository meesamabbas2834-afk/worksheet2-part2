#include "pic.h"
#include "io.h"

void pic_remap(s32int m_base, s32int s_base) {
    u8int mask_m, mask_s;

    mask_m = inb(MASTER_PIC_DATA);
    mask_s = inb(SLAVE_PIC_DATA);

    outb(MASTER_PIC_CMD, INIT_ICW1 | ICW4_NEEDED);
    outb(SLAVE_PIC_CMD, INIT_ICW1 | ICW4_NEEDED);

    outb(MASTER_PIC_DATA, m_base);
    outb(SLAVE_PIC_DATA, s_base);

    outb(MASTER_PIC_DATA, 4);
    outb(SLAVE_PIC_DATA, 2);

    outb(MASTER_PIC_DATA, MODE_8086);
    outb(SLAVE_PIC_DATA, MODE_8086);

    outb(MASTER_PIC_DATA, mask_m);
    outb(SLAVE_PIC_DATA, mask_s);
}

void pic_acknowledge(u32int irq) {
    if (irq < OFFSET_MASTER || irq > OFFSET_SLAVE_END) {
        return;
    }

    if (irq >= OFFSET_SLAVE) {
        outb(SLAVE_PIC_CMD, PIC_EOI);
        outb(MASTER_PIC_CMD, PIC_EOI);
    } else {
        outb(MASTER_PIC_CMD, PIC_EOI);
    }
}
