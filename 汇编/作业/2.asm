assume cs:code,ds:data,ss:stack
data segment
	input1 db "please input the first number:",'$'
	input2 db "please input the second number:",'$'
	aa db 6				;用来存储第一个乘数
		db ?			
		db 6 dup(?)
	bb db 6				;用来存储第二个乘数
		db ?
		db 6 dup(?)
	hex db 9 dup('0'),'$'	;用来存储16进制结果
	bi db 33 dup('0'),'$'	;用来存储2进制结果
	de db 10 dup('0'),'$'	;用来来存储10进制结果
	crlf db 0ah,0dh,'$'		;回车和换行
data ends

stack segment 				;堆栈段
	dw 100h dup(?)
stack ends

code segment
main:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	
	lea si,hex+8
	mov ah,68h		
	mov [si],ah			;16进制末尾加h
	lea si,bi+32
	mov ah,42h			;2进制末尾加B
	mov [si],ah
	
	lea dx,input1		;输入第一个数
	mov ah,09h
	int 21h
	lea dx,aa
	mov ah,0Ah
	int 21h
	lea dx,crlf
	mov ah,09h
	int 21h
	
	lea dx,input2		;输入第二个数
	mov ah,09h
	int 21h
	lea dx,bb
	mov ah,0Ah
	int 21h
	lea dx,crlf
	mov ah,09h
	int 21h
	
	xor cx,cx			;输出第一个数
	mov cl,aa[1]
	lea si,aa+2
again1:				
	mov dl,[si]
	mov ah,02h
	int 21h
	inc si
	loop again1
	mov ah,02h			;输出一个乘号
	mov dl,2Ah
	int 21h
	
	xor cx,cx			;输出第二个数
	mov cl,bb[1]
	lea si,bb+2
again2:				
	mov dl,[si]
	mov ah,02h
	int 21h
	inc si
	loop again2			;输出一个等于号
	mov ah,02h
	mov dl,3Dh
	int 21h
	lea dx,crlf			;回车，换行
	mov ah,09h
	int 21h
	
	xor cx,cx			;把第一个数转换为一个dw
	mov cl,aa[1]
	lea si,aa+2
	xor ax,ax
s1:	
	mov bx,10
	mul bx
	xor bx,bx
	mov bl,[si]
	sub bl,30h
	add ax,bx
	inc si
	loop s1
	
	push ax
	
	xor cx,cx			;把第二个数转换为一个dw
	mov cl,bb[1]
	lea si,bb+2
	xor ax,ax
s2:
	mov bx,10
	mul bx
	xor bx,bx
	mov bl,[si]
	sub bl,30h
	add ax,bx
	inc si
	loop s2
	
	mov bx,ax
	pop ax
	
	mul bx				;相乘
	push dx
	push ax
	push dx
	push ax
	push dx
	
	mov cx,4			;把结果转化为16进制存在hex中
	lea di,hex+7		;先低位，从后往前存
s3:
	xor dx,dx
	mov bx,10h
	div bx
	add dx,30h
	cmp dx,3Ah
	jb less1			;大于等于10则换为字母表示
	add dx,7
less1:
	mov [di],dl
	dec di
	loop s3
	
	pop ax				;再高位，也从后往前存
	mov cx,4
s4:
	xor dx,dx
	mov bx,10h
	div bx
	add dx,30h
	cmp dx,3Ah
	jb less2			;大于等于10则换为字母表示
	add dx,7
less2:
	mov [di],dl
	dec di
	loop s4
	
	pop ax 			
	mov cx,16			;把结果转化为2进制存在bi中
	lea di,bi+31		;先低位，从后往前存
s5:
	xor dx,dx
	mov bx,2
	div bx
	add dx,30h
	mov [di],dl
	dec di
	loop s5
	
	pop ax				;再高位，也从后往前存
	mov cx,16
s6:
	xor dx,dx
	mov bx,2
	div bx
	add dx,30h
	mov [di],dl
	dec di
	loop s6
	
	xor cx,cx			;把结果转化为10进制存在de中
	pop ax
	pop dx
	lea di,de+9
s7:
	push cx
	mov bx,10
	call divdw			;用divdw解决除法溢出的问题
	add bx,30h
	mov [di],bl
	pop cx
	dec di
	push ax
	or ax,dx			;判断商是否已经为0
	pop ax
	jnz s7				;商不为0则继续循环
	
	inc di				;让指针指向de第一个非零元素
	
done:
	mov ah,09h			;输出10进制结果
	mov dx,di
	int 21h
	lea dx,crlf
	mov ah,09h
	int 21h
	
	mov ah,09h			;输出16进制结果
	lea dx,hex
	int 21h
	lea dx,crlf
	mov ah,09h
	int 21h
	
	mov cx,7			;输出2进制结果
	lea bx,bi
s8:	
	mov ah,02h
	mov dl,[bx]
	int 21h
	inc bx
	mov ah,02h
	mov dl,[bx]
	int 21h
	inc bx
	mov ah,02h
	mov dl,[bx]
	int 21h
	inc bx
	mov ah,02h
	mov dl,[bx]
	int 21h
	inc bx
	mov ah,02h			;每输出4个bit输出一个空格
	mov dl,20h
	int 21h
	loop s8
	mov dx,bx			;输出最后4个bit以及末尾的‘B’
	mov ah,09h
	int 21h
	lea dx,crlf		
	mov ah,09h
	int 21h
	
	mov ah,4Ch
	int 21h
	
divdw:					;解决除法溢出的问题
	push ax				;先算高位，把低位压入栈
	mov ax,dx
	xor dx,dx
	div bx			
	mov cx,ax			;先把商的高位存起来
	pop ax				;再算低位
	div bx
	mov bx,dx			;此时bx中是余数
	mov dx,cx			;此时dx中是商的高位
	ret
	
code ends
end main
	