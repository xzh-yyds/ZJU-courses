.386
assume cs:code,ds:data,ss:stack
data segment use16
	handle dw 0				;store the handle of the file
	input db "enter the file name:",'$'
	filename db 100 
		db ?
		db 100 dup(?)		;store the filename
	row db 18 dup(?),'$'	;store the current row
	errmsg db "error",'$'
	count1 dd 0				;row number
	count2 dw 0				;the count of a row
	pg dd 0					;record the page
	filesize dd 0			;store the size of the file
	crlf db 0ah,0dh,'$' 	;a return
data ends

stack segment use16
	dw 100h dup(?)
stack ends

code segment use16
main:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	
	mov ax,3
	int 10h				;shift to video mode
	mov ax,0b800h		;find the address of video memory
	mov es,ax			;shift to the address of video memory
	cld					;set draw forward
	mov di,0			;move the pen to the biginning
	
	lea dx,input
	mov ax,0900h
	int 21h
	lea dx,filename
	mov ah,0Ah
	int 21h				;input the filename
	lea dx,crlf
	mov ax,0900h
	int 21h
	
	lea si,filename+1
	xor cx,cx
	mov cl,[si]
q3:	inc si
	loop q3
	inc si
	mov byte ptr [si],0	;add a 0 after the end of filename
	
	mov ax,3D00h
	lea dx,filename+2
	int 21h				;open the file
	jc err
	mov [handle],ax
	mov ax,4202h
	mov bx,[handle]
	mov cx,0
	mov dx,0
	int 21h				;obtain the size of the file
	mov word ptr [filesize+2],dx
	mov word ptr [filesize],ax		
	mov ax,4200h
	mov bx,[handle]
	mov cx,0
	mov dx,0
	int 21h				;mov the file ptr to the beginning
	jmp show_this_page

next_page:
	mov eax,dword ptr [pg]
	add eax,256
	cmp eax,dword ptr [filesize]
	jnb keyboard
	add dword ptr [pg],256
	mov di,0
	mov cx,80*16
	mov ax,0720h
	rep stosw			;clear the screen
	mov di,0
	jmp show_this_page

last_page:
	cmp dword ptr [pg],0
	jna keyboard
	sub dword ptr [pg],256
	mov di,0
	mov cx,80*16
	mov ax,0720h
	rep stosw			;clear the screen
	mov eax,dword ptr [pg]
	mov dword ptr [count1],eax
	mov ax,4200h
	mov bx,[handle]
	mov cx,word ptr [pg+2]
	mov dx,word ptr [pg]
	int 21h
	mov di,0
	jmp show_this_page
	
first_page:
	mov di,0
	mov cx,80*16
	mov ax,0720h		;clear the screen
	rep stosw
	mov dword ptr [count1],0
	mov dword ptr [pg],0
	mov ax,4200h
	mov bx,[handle]
	mov cx,0
	mov dx,0
	int 21h
	mov di,0
	jmp show_this_page

end_page:
	mov di,0
	mov cx,80*16
	mov ax,0720h
	rep stosw			;clear the screen
	mov eax,dword ptr [pg]
q2:	add eax,256
	cmp eax,dword ptr [filesize]
	jna q2
	sub eax,256
	mov dword ptr [pg],eax
	mov dword ptr [count1],eax
	mov ax,4200h
	mov bx,[handle]
	mov cx,word ptr [pg+2]
	mov dx,word ptr [pg]
	int 21h
	mov di,0
	jmp show_this_page

show_this_page:
	mov cx,16
next_row:
	push cx
	mov cx,16
	lea si,row
q1:	mov byte ptr [si],20h	;clear the last row
	inc si
	loop q1
	mov ax,3F00h
	mov bx,[handle]
	mov cx,16
	lea dx,row
	int 21h				;read the file once a row/16 bytes
	mov [count2],ax
	sub word ptr [count2],1
	jc keyboard
	or ax,ax
	jz keyboard
	call show_this_row
	add di,10
	add [count1],16
	pop cx
	loop next_row
	
keyboard:	
	mov ax,0000h
	int 16h
	cmp ax,5100h		;PgDn
	je next_page
	cmp ax,4900h		;PgUp
	je last_page
	cmp ax,4700h		;Home
	je first_page
	cmp ax,4F00h		;End
	je end_page
	cmp ax,011Bh		;Esc
	je done
	jmp keyboard
	
done:						
	mov ax,3E00h
	mov bx,[handle]
	int 21h				;close the file
		
exit:
	mov ax,4C00h
	int 21h
	
err:
	lea dx,errmsg
	mov ax,0900h
	int 21h
	jmp exit
	
show_this_row:
	call show_row_number
	lea si,row
	mov cx,4
again2:
	push cx
	mov cx,3
again1:
	call show_ascll
	mov ax,0720h		
	stosw 				;add a space 
	inc si
	loop again1
	call show_ascll
	mov ax,0F7Ch		;a vertical line in bright white
	stosw
	inc si
	pop cx
	loop again2
	std					;draw back 
	mov ax,0720h		
	stosw
	cld					;draw forward again
	mov ax,0720h		 
	stosw				;add a space
	mov ax,0720h		
	stosw				;add a space 
	lea si,row
	mov cx,16
again3:
	mov al,[si]
	mov ah,0Ch
	stosw
	inc si
	loop again3
	ret	
	
show_ascll:
	lea bx,row
	add bx,[count2]
	cmp bx,si
	jnb p1
	mov ax,0720h
	stosw				;a space
	stosw				;a space
	jmp p2
p1:	mov al,[si]
	shr al,4
	add al,30h
	cmp al,3Ah
	jb s1
	add al,7
s1:	mov ah,0Ch
	stosw				;show the higher byte
	mov al,[si]
	and al,00001111b
	add al,30h
	cmp al,3Ah
	jb s2
	add al,7
s2:	mov ah,0Ch
	stosw				;show the lower byte
p2:	ret
	
show_row_number:
	mov ebx,[count1]
	shr ebx,28
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 1st hex number of the row number
	mov ebx,[count1]
	shr ebx,24
	and bx,000Fh
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 2nd hex number of the row number
	mov ebx,[count1]
	shr ebx,20
	and bx,000Fh
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 3rd hex number of the row number
	mov ebx,[count1]
	shr ebx,16
	and bx,000Fh
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 4th hex number of the row number
	mov ebx,[count1]
	shr ebx,12
	and bx,000Fh
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 5th hex number of the row number
	mov ebx,[count1]
	shr bx,8
	and bx,000Fh
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 6th hex number of the row number
	mov ebx,[count1]
	shr bx,4
	and bx,000Fh
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 7th hex number of the row number
	mov ebx,[count1]
	;shr bx,0
	and bx,000Fh
	mov al,bl
	add al,30h
	call hex_check
	mov ah,0Ch
	stosw				;the 8th hex number of the row number
	mov ax,0C3Ah 		
	stosw				;a colon
	mov ax,0720h
	stosw				;a space
	ret					;ret of show_row_number
	
hex_check:				;used to correct the hex number
	cmp al,3Ah
	jb s
	add al,7
s:	ret
	
code ends
end main