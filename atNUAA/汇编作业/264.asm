;264.asm
	.model small
	.stack
	.data
buffer1 dw 1357h,5678h,1234h,0fedh;0fed 1234 5678 1357h
buffer2 dw 0246h,5679h,1243h,0fech;0fec 1243 5679 0246h;answer 0000 fff0 ffff 1111h
	.code
	.startup
	mov bx,offset buffer1
	mov si,offset buffer2
	mov ax,[bx];1
	mov dx,[si]
	sub ax,dx
	mov [bx],ax
	inc bx
	inc bx
	inc si
	inc si
	mov cx,3	
again: mov ax,[bx];2
	mov dx,[si]
	sbb ax,dx
	mov [bx],ax
	inc bx
	inc bx
	inc si
	inc si
	loop again
	.exit 0
	end
