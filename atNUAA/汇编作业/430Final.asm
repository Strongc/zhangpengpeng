;������ 040630416
;430.asm
        .model small
        .stack
        .data
score   db 50 dup(?)  
grade   db 5 dup('0')
		db '$'

head	db 0ah,0dh,0ah,0dh,0ah,0dh,'               Grades  Numbers','$'
scorea	db 0ah,0dh,'               scoreA:   ','$'
scoreb	db 0ah,0dh,'               scoreB:   ','$'
scorec	db 0ah,0dh,'               scoreC:   ','$'
scored	db 0ah,0dh,'      	       scoreD:   ','$'
scoree	db 0ah,0dh,'               scoreE:   ','$'
input	db 0ah,0dh,'            Welcome to Scores Static System  ',0ah,0dh,0ah,0dh,0ah,0dh
		db '  Please input the scores (divide with sign ",",and end with other signs): ',0ah,0dh,'   ','$'
		;���������ö��Ÿ������������������ҷǶ��ŵ��ַ�����������룻�����ż�Ϊ�գ����Ϊ0
		;if the resuat is not a number,that means OVERFLOW)
error	db 0ah,0dh,' error (>100) ','$'
thanks	db 0ah,0dh,0ah,0dh,0ah,0dh,0ah,0dh,'                    Thank you !','$'
		
       .code
        .startup
        mov si,offset score
        mov bx,offset grade
        call read
        call stat
        call display
        .exit 0

read	proc
	push si
	push bx
	mov dx,offset input
	mov ah,09h
	int 21h
	mov cx,0h
read0:	mov bx,0h		;��ʼ�¶�һ����
read1:	mov ah,1h		;�µ�һλ
	mov al,0h
	int 21h
	cmp al,','
	je getone
	cmp al,'0'
	jb endr
	cmp al,'9'
	ja endr
	sub al,'0'
	;bx<-bx*10d
	shl bx,1
	mov dx,bx
	shl bx,1
	shl bx,1
	add bx,dx
	;
	mov ah,0
	add bx,ax
	jmp read1
getone:	cmp bl,100d			;��ȡһ����
	ja shower1
	inc cx
	mov byte ptr [si],bl
	inc si
	jmp read0
shower1: call showerror
	jmp read0
endr:	cmp bl,100d			;�������
	ja shower2
	inc cx
	mov byte ptr [si],bl
	jmp endr2
shower2: call showerror
	;
endr2:	pop bx
	pop si
	ret
read	endp
showerror	proc			;����100ʱ���б���
	mov dx,offset error
	mov ah,09h
	int 21h
	ret
showerror	endp

stat    proc                   ;use cx as numbers
		cmp cx,0h				;���û����������Ҫͳ��
		jz endpro2
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
endpro2:	ret
stat    endp
        
display proc			;������
		push bx
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
		
		mov dx,offset thanks
		mov ah,09h
		int 21h

        pop bx
        ret
display endp

        end 

