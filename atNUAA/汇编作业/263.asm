;263.asm
	.model small
	.stack
	.data
	.code
	.startup
	mov dx,01ffh;or 00ffh
	cmp dh,00h
	jz chax
	jmp endex
chax:mov ax,0000h
	jmp endexe
endex:mov ax,0ffffh
endexe:.exit 0
	end
