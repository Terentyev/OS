; Multiboot macros to make few lines later more readable
MULTIBOOT_PAGE_ALIGN    equ 1<<0
MULTIBOOT_MEMORY_INFO   equ 1<<1
MULTIBOOT_HEADER_MAGIC  equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS  equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
MULTIBOOT_CHECKSUM      equ - (MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

; This is the kernel'- entry point
[BITS 32]

[GLOBAL mboot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]


; This part MUST be 4byte aligned
ALIGN 4
mboot:
    ; This is GRUB Multiboot header. A boot signature
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM

    ; AOUT kludge - must be physical addresses. Make a note of these:
    ; The linker script fills in the data for these ones!
    dd mboot
    dd code
    dd bss
    dd end
    dd start

[GLOBAL start]
[EXTERN main] ; this is in the c file

start:
    mov  esp, _sys_stack ; This points the stack to our new stack area
    push ebx
;    cli
    call main
    cli                  ; stop interrupts
    hlt                  ; halt the CPU

SECTION .bss
    resb 8192            ; This reserves 8KBytes of memory here
_sys_stack:
