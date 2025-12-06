global outb
global inb

; Function to write data to an I/O port
outb:
    mov dx, [esp + 4]    ; Port address load karein
    mov al, [esp + 8]    ; Data byte load karein
    out dx, al           ; Port par data bhejein
    ret

; Function to read data from an I/O port
inb:
    mov dx, [esp + 4]    ; Port address load karein
    in al, dx            ; Port se data read karein
    ret
