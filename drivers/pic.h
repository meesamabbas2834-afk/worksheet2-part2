#ifndef DRIVERS_PIC_H
#define DRIVERS_PIC_H

#include "type.h"

#define MASTER_PIC_CMD  0x20
#define MASTER_PIC_DATA 0x21
#define SLAVE_PIC_CMD   0xA0
#define SLAVE_PIC_DATA  0xA1

#define OFFSET_MASTER   0x20
#define OFFSET_SLAVE    0x28
#define OFFSET_SLAVE_END (OFFSET_SLAVE + 7)

#define PIC_EOI         0x20

#define INIT_ICW1       0x10
#define ICW4_NEEDED     0x01
#define MODE_8086       0x01

void pic_remap(s32int m_offset, s32int s_offset);
void pic_acknowledge(u32int int_num);

#endif
