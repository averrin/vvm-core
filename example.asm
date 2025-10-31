; Simple VVM Assembly Program Example
; This program demonstrates basic VM operations

; Move immediate value 42 to EAX register
MOV EAX 42

; Move immediate value 10 to EBX register
MOV EBX 10

; Add EBX to EAX (EAX = EAX + EBX = 52)
ADD EAX EBX

; Move value from EAX to ECX
MOV ECX EAX

; Increment ECX (ECX = 53)
INC ECX

; Compare EAX with immediate value 52
CMP EAX 52

; Print interrupt - output character 'H' (0x48)
MOV AL 72
INT 33

; Print 'e'
MOV AL 101
INT 33

; Print 'l'
MOV AL 108
INT 33

; Print 'l'
MOV AL 108
INT 33

; Print 'o'
MOV AL 111
INT 33

; Print '!'
MOV AL 33
INT 33

; Print newline
MOV AL 10
INT 33

; End program
; INT 255
