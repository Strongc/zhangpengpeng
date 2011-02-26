;’≈≈Ù≈Ù 040630416
;430.asm
        .model small
        .stack
        .data
score   db 100d,99d,52d,85d,80d,90d,73d,61d,91d,73d;100d=64h  
grade   db 5 dup('0')
		db '$'

head	db '             Display Score Grades ',0ah,0dh,'               Grades  Numbers','$'
scorea	db 0ah,0dh,'               scoreA:   ','$'
scoreb	db 0ah,0dh,'               scoreB:   ','$'
scorec	db 0ah,0dh,'               scoreC:   ','$'
scored	db 0ah,0dh,'      	       scoreD:   ','$'
scoree	db 0ah,0dh,'               scoreE:   ','$'


       .code
        .startup
        mov si,offset score
        mov bx,offset grade
        call stat
        call display
        .exit 0

stat    proc
        mov cx,bx                          ;get the number of scores
        sub cx,si
again:  mov al,[si]
        inc si
        cmp al,90d;5Ah
        jge ga
        cmp al,80d;50h
        jge gb
        cmp al,70d;46h
        jge gc
        cmp al,60d;3Ch
        jge gd
        inc byte ptr [bx+4]
        jmp endpro
ga:     inc byte ptr [bx]  
        jmp endpro
gb:     inc byte ptr [bx+1]  
        jmp endpro
gc:     inc byte ptr [bx+2]  
        jmp endpro
gd:     inc byte ptr [bx+3]  
		jmp endpro
endpro: loop again
		ret
stat    endp
        
display proc
		push bx
;		call judovfl   ;judge whether overflow
		mov dx,offset head
		mov ah,09h
		int 21h

		mov dx,offset scorea
		mov ah,09h
		int 21h
		mov dl,[bx]
		mov ah,02h
		int 21h
		inc bx
		mov dx,offset scoreb
		mov ah,09h
		int 21h
		mov dl,[bx]
		mov ah,02h
		int 21h
		inc bx
		mov dx,offset scorec
		mov ah,09h
		int 21h
		mov dl,[bx]
		mov ah,02h
		int 21h
		inc bx
		mov dx,offset scored
		mov ah,09h
		int 21h
		mov dl,[bx]
		mov ah,02h
		int 21h
		inc bx
		mov dx,offset scoree
		mov ah,09h
		int 21h
		mov dl,[bx]
		mov ah,02h
		int 21h
		inc bx
		
        pop bx
        ret
display endp

        end 




