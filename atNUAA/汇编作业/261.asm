;261.asm
	.model small
	.stack
	.data
string 	db 'ABCDEFGHI  ','$'
	.code
	.startup
	mov si,offset string  ;先显示一下数据
	mov dx,si
	mov ah,9h
	int 21h

	mov dl,[si]
	mov ah,02h
	int 21h
	mov dh,dl
	mov dl,[si+5]
	mov ah,02h
	int 21h
	.exit 0

	end
	