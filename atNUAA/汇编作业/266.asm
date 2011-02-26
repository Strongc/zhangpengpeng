;266.asm
        .model small
        .stack
        .data
string  db 'abc$ad$$GEHH$cer$2h'
        db 32750d dup('a') ;32768
        
        .code
        .startup
        mov si,offset string
        mov cx,327d;32768d	;为了方便看结果，
        mov ah,02h
again:  mov dl,[si]
        cmp dl,'$'
        jnz yeah
        mov dl,' '
        mov byte ptr [si],dl
yeah:   int 21h
        inc si
        loop again
        .exit 0
        
        end 
