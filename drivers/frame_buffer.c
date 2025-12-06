#include "frame_buffer.h"
#include "io.h"

/* Video memory pointer definition */
char *vga_mem = (char *) 0x000B8000;
unsigned short current_cursor = 0;

/* Internal helper function */
void set_vga_char(unsigned int idx, char c, unsigned char fg, unsigned char bg) {
    vga_mem[idx * 2] = c;
    vga_mem[idx * 2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/* Hardware cursor update function */
void fb_move_cursor(unsigned short pos) {
    outb(0x3D4, 14);           // High byte command
    outb(0x3D5, (pos >> 8));   // Send High byte
    outb(0x3D4, 15);           // Low byte command
    outb(0x3D5, pos & 0xFF);   // Send Low byte
}

void fb_clear() {
    unsigned int k = 0;
    while (k < 80 * 25) {
        /* Updated macros: COLOR_WHT and COLOR_BLK */
        set_vga_char(k, ' ', COLOR_WHT, COLOR_BLK);
        k++;
    }
    current_cursor = 0;
    fb_move_cursor(current_cursor);
}

void fb_write(char *str, unsigned int len, unsigned char color) {
    unsigned int i;
    for (i = 0; i < len; i++) {
        if (str[i] == '\n') {
            /* Move cursor to start of next line */
            unsigned int current_row = current_cursor / 80;
            current_cursor = (current_row + 1) * 80;
        } else {
            /* Using COLOR_BLK as background default */
            set_vga_char(current_cursor, str[i], color, COLOR_BLK);
            current_cursor++;
        }

        /* Wrap around if screen end reached */
        if (current_cursor >= 80 * 25) {
            current_cursor = 0;
        }
        
        fb_move_cursor(current_cursor);
    }
}

/* Changed u32int to unsigned int to fix type error */
void fb_write_dec(unsigned int val, unsigned char color) {
    if (val == 0) {
        fb_write("0", 1, color);
        return;
    }

    char temp_buf[32];
    int count = 0;

    /* Extract digits in reverse order */
    while (val > 0) {
        temp_buf[count] = '0' + (val % 10);
        val /= 10;
        count++;
    }

    /* Reverse the string back to normal */
    char final_str[32];
    int j;
    for (j = 0; j < count; j++) {
        final_str[j] = temp_buf[count - 1 - j];
    }
    
    fb_write(final_str, count, color);
}
