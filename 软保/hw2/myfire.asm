code segment
assume cs:code, ds:code
;my int_8h
int_8h:
    cmp cs:fixed, 1
    je goto_old_8h
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push ds
    push es
    mov ah, 62h
    int 21h     ;BX=psp
    add bx, 10h
    mov ds, bx

    cmp byte ptr ds:[0AB85h], 0FFh
    jne skip
    cmp byte ptr ds:[0AB86h], 47h
    jne skip
    cmp byte ptr ds:[0AB87h], 12h
    jne skip
    mov byte ptr ds:[0AB85h], 90h
    mov byte ptr ds:[0AB86h], 90h
    mov byte ptr ds:[0AB87h], 90h

    mov cs:fixed, 1
skip:
    pop es
    pop ds
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
goto_old_8h:
    jmp dword ptr cs:[old_8h]
fixed  db 0
old_8h dw 0,0       ;old vector of int_8h
;end of int_8h

initialize:
    push cs
    pop ds          ;DS=CS
    xor ax, ax
    mov es, ax
    mov bx, 8*4     ;ES:BX-> int_8h's vector
    push es:[bx]
    pop old_8h[0]
    push es:[bx+2]
    pop old_8h[2]   ;save old vector of int_8h
    mov ax, offset int_8h
    cli             ;disable interrupt when changing int_8h's vector
    push ax
    pop es:[bx]
    push cs
    pop es:[bx+2]   ;set vector of int_8h
    sti             ;enable interrupt
install:
    mov ah, 9
    mov dx, offset install_msg
    int 21h

    mov dx, offset initialize    ;DX=len before label initialize
    add dx, 100h    ;include PSP's len
    add dx, 0Fh     ;include remnant bytes
    mov cl, 4
    shr dx, cl      ;DX=program's paragraph size to keep resident
    mov ah, 31h
    int 21h         ;keep resident
install_msg db 'Fire buster installed, enjoy it!', 0Dh, 0Ah, '$'
code ends
end initialize