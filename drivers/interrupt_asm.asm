global isr_33_wrapper
global load_idt_asm
extern handle_interrupt

load_idt_asm:
    mov edx, [esp + 4]
    lidt [edx]
    ret

isr_33_wrapper:
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub

irq_common_stub:
    pusha           ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    call handle_interrupt

    popa            ; Pops same registers
    add esp, 8      ; Clean up pushed error code and ISR number
    sti
    iret
