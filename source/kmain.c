#include "../drivers/frame_buffer.h"
#include "../drivers/interrupts.h"

/* Refactored Helper Functions */
int calc_tri_sum(int v1, int v2, int v3) {
    return v1 + v2 + v3;
}

int calc_product(int x, int y) {
    return x * y;
}

int validate_input(int val) {
    if (val == 0x1234) return 1;
    return 0;
}

/* Main Kernel Entry */
int kmain(void) {
    /* Correct function name call */
    init_idt();
    
    fb_clear();
    
    char welcome[] = "Kernel Booted Successfully (Refactored)\n";
    fb_write(welcome, sizeof(welcome) - 1, COLOR_LGRN);

    /* Arithmetic Tests */
    int total = calc_tri_sum(10, 20, 30);
    char msg_sum[] = "Total (10+20+30): ";
    
    fb_write(msg_sum, sizeof(msg_sum) - 1, COLOR_WHT);
    fb_write_dec(total, COLOR_LCYN);
    fb_write("\n", 1, COLOR_WHT);

    int result = calc_product(8, 8);
    char msg_prod[] = "Product (8*8): ";
    
    fb_write(msg_prod, sizeof(msg_prod) - 1, COLOR_WHT);
    fb_write_dec(result, COLOR_LCYN);
    fb_write("\n", 1, COLOR_WHT);

    char prompt[] = "Waiting for Keyboard Input:\n";
    fb_write(prompt, sizeof(prompt) - 1, COLOR_LRED);

    return total + result;
}
