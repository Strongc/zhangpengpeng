;262.asm
	.model small
	.stack
	.data
buffer 	db 09h,18h,27h,36h
	.code
	.startup
	mov si,offset buffer

	mov dl,[si]
	mov al,[si+1]
	and byte ptr dl,0fh
	mov cl,4
	shl al,cl
	or dl,al

	mov dh,[si+2]
	mov ah,[si+3]
	and byte ptr dh,0fh
	mov cl,4
	shl ah,cl
	or dh,ah

	.exit 0
	end
	

