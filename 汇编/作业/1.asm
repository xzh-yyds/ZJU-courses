code segment
assume cs:code,ds:code,ss:code

main:
	mov ax,3			;设置分辨率80*25，16色
	int 10h				;切换文本显示模式
	mov ax,0b800h		;找显存地址
	mov es,ax			;切换显存地址
	cld					;用右手写
	mov di,0			;把笔放到左上角
	mov dx,3030h		;两位ascll值归零
	mov bl,0			;字符值归零
	mov cx,11			;一共11列
p1:
	push di				;记录横坐标
	push cx				;记录列数
	mov cx,25			;开始新的一列，1列25行
p2:	
	cmp dh,47h			;判断是否打印完
	jz p6				;若已打印完则直接结束
	call print			;没有打印完就继续打印
	inc bl				;字符值加1
	cmp dl,46h			;判断低位是否满16
	jnz p4				;低位不满16就去加1
	mov dl,30h			;低位满16则归零
	inc dh				;进位
	cmp dh,3ah			;判断高位是否满10
	jnz p3				;高位不满10不用进一步操作
	add dh,7			;高位满10切换16进制字母表示
p3:						;此处就是个中转站
	jmp p5			
p4:						;低位在这里加1
	inc dl				;低位加1
	cmp dl,3ah			;判断低位是否满10
	jne p5				;低位不满10不用进一步操作
	add dl,7			;低位满10切换16进制字母表示
	
p5: 					;all roads lead to Rome
	add di,80*2-7*2		;竖着写
	loop p2 			;这一列没有写完就接着写
						;写完就准备开始新的一列
	pop cx				;找回列数
	pop di				;找回横坐标
	add di,7*2 			;准备写下一列
	loop p1 			;去写下一列
	
p6:	
	mov ah,0			;暂停 
	int 16h 
	mov ah,4ch 
	int 21h 
	
print: 
	mov al,bl 
	mov ah,0ch			;红色的字符
	stosw
	 
	mov al,dh			;打印高位 
	mov ah,0ah			;绿色的数字
	stosw 
	mov al,dl			;打印低位 
	stosw 
	
	mov ax,0720h		;跟上一个空格 
	stosw
	mov ax,0720h		;再来一个空格
	stosw 
	mov ax,0720h		;再来一个空格
	stosw
	mov ax,0720h		;一共4个空格
	stosw
	
	ret 

code ends
end main
	
	
	
	
	
	