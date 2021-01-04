code segment
assume cs:code
shell:
    call next
next:
    pop bx  ; BX = offset of next
    sub bx, offset next - offset shell
    ; bx = offset of shell about CS
    
    push cs
    pop di

    mov bp, ds  ; mov bp, es
    add bp, 10h ; bp = address of the fisrt paragraph
    ; psp + 10h

    push es
    
    mov es, bp
    mov al, 33h
decrypt:
    mov dx, es
    cmp dx, di
    jae remain
    mov si, 0
next_byte:
    cmp si, 10h
    jae next_10h
    xor es:[si], al
    inc si
    jmp next_byte
next_10h:
    mov dx, es
    inc dx
    mov es, dx
    jmp decrypt
remain:
    mov si, 0
next_remain_byte:
    cmp si, bx
    jae reloc
    xor es:[si], al
    inc si
    jmp next_remain_byte

reloc:
    mov cx, cs:[bx+head+6]      ; get the number of relocation items
    mov ax, cs:[bx+head+18h]    ; get the offset of relocation table
    push bx
    add bx, ax
    lea si, cs:[bx+head]
    pop bx
reloc_next:
    test cx, cx
    jz reloc_end
    mov di, cs:[si]     ; offset
    mov dx, cs:[si+2]   ; delta_para
    add dx, bp          ; dx是重定位项的段地址
    mov es, dx
    add es:[di], bp
    add si, 4
    dec cx
    jmp reloc_next
reloc_end:  

    pop es
    
;(5)set ss:sp
    mov dx, cs:[bx+head+0Eh]
    add dx, bp
    mov sp, cs:[bx+head+10h]
    mov ss, dx
;(6)set cs:ip
    mov dx, cs:[bx+head+16h]
    add dx, bp
    push dx
    push word ptr cs:[bx+head+14h]
    retf
head label word; head是一个变量名, 类型为word,
               ; 但它只有名字及地址,没有值,
               ; 编译后不占内存空间
;head+00 MZ
;head+02 bytes in last page
;head+04 pages count
;head+06 number of relocation items
;head+08 header size in paragraphs
;head+0A minimum extra paragraphs needed
;head+0C maximum extra paragraphs needed
;head+0E initial SS
;head+10 initial SP
;head+12 checksum
;head+14 initial IP
;head+16 initial CS
;head+18 address of relocation table in file
;head+1A overlay number
;head+1C reversed words
code ends
end shell
