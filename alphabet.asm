db 2 ; mov <reg8> <val> ; 0
db 0 ; AH               ; 1
db 0x0F ; 0x0F          ; 2

db 2 ; mov <reg8> <val> ; 3
db 1 ; AL               ; 4
db 'A' ; 65             ; 5

db 1 ; int              ; 6
db 0x10 ; 0x10          ; 7

db 8 ; INC              ; 8
db 1 ; AL               ; 9

db 20 ; cmp             ; 10
db 1 ; AL               ; 11
db 'Z' ; 90             ; 12

db 22 ; jne             ; 13
db 6 ; 6                ; 14

db 2 ; mov <reg8> <val> ; 15
db 1 ; AL               ; 16
db 10 ; 10              ; 17

db 1 ; int              ; 18
db 0x10 ; 0x10          ; 19

times 510-($-$$) db 0
db 0x55, 0xAA ; 510, 511