;267.asm
        .model small
        .stack
        .data
Array   db 10d dup(10h)
        db 90d dup(11h)
        
        .code
        .startup
        mov si,offset Array
        mov cx,100d
again:  mov dl,[si]
        dec dl
        mov byte ptr [si],dl
        inc si
        loop again
        .exit 0
        
        end 
