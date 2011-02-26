;268.asm
        .model small
        .stack
        .data
string  db'abcdefeg','$'
        
        .code
        .startup
        mov si,offset string
        mov dl,0h
again:  inc dl
        mov al,[si]
        inc si
        cmp al,'$'
        jnz again
        dec dl
        .exit 0
        
        end 

