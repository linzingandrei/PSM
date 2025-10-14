;;-----------------_DEFINITIONS ONLY_-----------------------
;; IMPORT FUNCTIONS FROM C
%macro IMPORTFROMC 1-*
%rep  %0
    %ifidn __OUTPUT_FORMAT__, win32 ; win32 builds from Visual C decorate C names using _ 
    extern _%1
    %1 equ _%1
    %else
    extern %1
    %endif
%rotate 1 
%endrep
%endmacro

;; EXPORT TO C FUNCTIONS
%macro EXPORT2C 1-*
%rep  %0
    %ifidn __OUTPUT_FORMAT__, win32 ; win32 builds from Visual C decorate C names using _ 
    global _%1
    _%1 equ %1
    %else
    global %1
    %endif
%rotate 1 
%endrep
%endmacro

%define break xchg bx, bx

IMPORTFROMC _KernelMain

TOP_OF_STACK                equ 0x200000
KERNEL_BASE_PHYSICAL        equ 0x200000
;;-----------------^DEFINITIONS ONLY^-----------------------

segment .text
[BITS 32]
ASMEntryPoint:
    cli
    MOV     DWORD [0x000B8000], 'O1S1'
%ifidn __OUTPUT_FORMAT__, win32
    MOV     DWORD [0x000B8004], '3121'                  ; 32 bit build marker
%else
    MOV     DWORD [0x000B8004], '6141'                  ; 64 bit build marker
%endif

    MOV     ESP, TOP_OF_STACK                           ; just below the kernel
    
    break
    
    PML4_ADDR equ 0x1000
    PDPT_ADDR equ 0x2000
    PDT_ADDR equ 0x3000
    PT_ADDR equ 0x4000
    PT2_ADDR equ 0x5000

    PDPT_ADDR_1TB equ 0x6000
    PDT_ADDR_1TB equ 0x7000
    PT_ADDR_1TB equ 0x8000
    PT2_ADDR_1TB equ 0x9000

    mov edi, 0x0
    xor eax, eax
    mov ecx, 512
    rep stosd

    mov edi, PML4_ADDR
    xor eax, eax
    mov ecx, 512
    rep stosd 

    mov edi, PML4_ADDR
    add edi, 16
    xor eax, eax
    mov ecx, 512
    rep stosd 

    mov edi, PDPT_ADDR
    xor eax, eax
    mov ecx, 512
    rep stosd

    mov edi, PDT_ADDR
    xor eax, eax
    mov ecx, 512
    rep stosd

    mov edi, PT_ADDR
    xor eax, eax
    mov ecx, 1024
    rep stosd

    mov edi, PDPT_ADDR_1TB
    xor eax, eax
    mov ecx, 512
    rep stosd

    mov edi, PDT_ADDR_1TB
    xor eax, eax
    mov ecx, 512
    rep stosd

    mov edi, PT_ADDR_1TB
    xor eax, eax
    mov ecx, 1024 
    rep stosd

    ; break
    
    mov edi, PML4_ADDR 
    mov cr3, edi

    ; break

    PT_PRESENT equ 1
    PT_WRITABLE equ 2

    mov edi, PML4_ADDR
    mov eax, PDPT_ADDR | PT_PRESENT | PT_WRITABLE
    mov dword [edi], eax
    mov dword [edi+4], 0 

    mov edi, PDPT_ADDR
    mov eax, PDT_ADDR | PT_PRESENT | PT_WRITABLE 
    mov dword [edi], eax
    mov dword [edi+4], 0 

    mov edi, PDT_ADDR
    mov eax, PT_ADDR | PT_PRESENT | PT_WRITABLE 
    mov dword [edi], eax
    mov dword [edi+4], 0 
    mov dword [edi+8], PT2_ADDR | PT_PRESENT | PT_WRITABLE 
    mov dword [edi+12], 0

    mov edi, PML4_ADDR
    add edi, 16 
    mov eax, PDPT_ADDR_1TB | PT_PRESENT | PT_WRITABLE
    mov dword [edi], eax
    mov dword [edi+4], 0 

    mov edi, PDPT_ADDR_1TB 
    mov eax, PDT_ADDR_1TB | PT_PRESENT | PT_WRITABLE
    mov dword [edi], eax
    mov dword [edi+4], 0 

    mov edi, PDT_ADDR_1TB 
    mov eax, PT_ADDR_1TB | PT_PRESENT | PT_WRITABLE
    mov dword [edi], eax
    mov dword [edi+4], 0 
    mov dword [edi+8], PT2_ADDR_1TB | PT_PRESENT | PT_WRITABLE 
    mov dword [edi+12], 0

    mov edi, PT_ADDR
    mov eax, 0x00
    mov ecx, 512 
    .SetPTEntry:
        mov ebx, eax
        or ebx, PT_PRESENT | PT_WRITABLE
        mov dword [edi], ebx
        mov dword [edi+4], 0
        add eax, 0x1000
        add edi, 8
        loop .SetPTEntry
    
    ; break

    mov edi, PT2_ADDR
    mov eax, 0x200000
    mov ecx, 512
    .SetPTEntry2:
        mov ebx, eax
        or ebx, PT_PRESENT | PT_WRITABLE
        mov dword [edi], ebx
        mov dword [edi+4], 0
        add eax, 0x1000
        add edi, 8
        loop .SetPTEntry2
    
    mov edi, PT_ADDR_1TB
    mov eax, 0x00
    mov ecx, 1024 
    .SetPTEntry1TB:
        mov ebx, eax
        or ebx, PT_PRESENT | PT_WRITABLE
        mov dword [edi], ebx
        mov dword [edi+4], 0
        add eax, 0x1000
        add edi, 8
        loop .SetPTEntry1TB

    ; break

    CR4_PAE_ENABLE equ 1 << 5
    mov eax, cr4
    or eax, CR4_PAE_ENABLE
    mov cr4, eax

    ; break
    ; 0x0000001000201270
    ; 0x0000010000201270
    ; 0x0000010000000000
    ; 0x0000100000201270

    EFER_MSR equ 0xC0000080
    EFER_LM_ENABLE equ 1 << 8
    mov ecx, EFER_MSR
    rdmsr
    or eax, EFER_LM_ENABLE
    wrmsr

    ; break

    mov eax, cr0
    or eax, (1 << 31) | (1 << 0)
    mov cr0, eax

    break

    lgdt [GDT64]
    jmp 0x08:LongMode 

    ; break

    [BITS 64]
    LongMode:
        ; break
        cli

        mov rax, 0x10 
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax


        break

        mov     rax, 0x1000
        shl     rax, 28
        or      rax, _KernelMain
        mov     rsp, rax
        jmp     rax 

        break
        CLI
        HLT

;;--------------------------------------------------------

__cli:
    CLI
    RET

__sti:
    STI
    RET
 
__magic:
    XCHG    BX,BX
    RET
    
__enableSSE:                ;; enable SSE instructions (CR4.OSFXSR = 1)  
    MOV     RAX, CR4
    OR      EAX, 0x00000200
    MOV     CR4, RAX
    RET
    
EXPORT2C ASMEntryPoint, __cli, __sti, __magic, __enableSSE

; GDT TABLE FOR x64. It has to have the .end: at the end otherwise it won't jump to the kernel correctly.

FLAT_DESCRIPTOR_CODE64  equ 0x00AF9A000000FFFF  ; code, long-mode
FLAT_DESCRIPTOR_DATA64  equ 0x00AF92000000FFFF  ; data, long-mode
GDT64:
    .limit  dw  GDT64Table.end - GDT64Table - 1
    .base   dq  GDT64Table
GDT64Table:
    .null   dq 0                              ; 0x00
    .code64 dq FLAT_DESCRIPTOR_CODE64         ; 0x08
    .data64 dq FLAT_DESCRIPTOR_DATA64         ; 0x10
    .end: