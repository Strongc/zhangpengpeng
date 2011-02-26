;265.asm
	.model small
	.stack
	.code
	.code
	.startup
	mov bx,0b800h
	mov ds,bx
	mov si,0h
        mov cx,100d		;initial
again:  mov word ptr [si],0567h
	add si,2h
	loop again
	mov ax,0000h            ;prepare for proceeding
	mov dx,0000h
	mov si,0h               ;point back
	mov cx,100d
dagain: add ax,[si]
        adc dx,0h
        add si,2h
        loop dagain
        .exit 0
        end
