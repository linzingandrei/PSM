[bits 64]

segment .text

global func1

func1:
    mov eax, 5
    mov ecx, 0
    idiv ecx
    ret