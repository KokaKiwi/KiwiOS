global _start
extern start, code, data, bss, end

MULTIBOOT_HEADER_MAGIC  equ 0x1BADB002
MULTIBOOT_PAGE_ALIGN    equ 1<<0
MULTIBOOT_MEMORY_INFO   equ 1<<1
MULTIBOOT_USE_GFX       equ 1<<2
MULTIBOOT_HEADER_FLAGS  equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO ; | MULTIBOOT_USE_GFX
CHECKSUM                equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

;-- Multiboot header --
section .__mbHeader
align 4

mbheader:
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd CHECKSUM
    dd mbheader
        dd code                 ; Start of kernel '.text' (code) section.
        dd bss                  ; End of kernel '.data' section.
        dd end                  ; End of kernel.
        dd _start               ; Kernel entry point (initial EIP).
        ; Graphics
        dd 0x00000000           ; 0 = linear graphics
        dd 0
        dd 0
        dd 32
;-- /Multiboot header --

_start:
    cli

    mov esp, stack              ; Setup stack

    push ebx                    ; Multiboot infos
    push eax                    ; Multiboot magic
    mov ebp, 0

    call start

    cli
    hlt
    jmp $
.end:

section .bss
    resb 32768
stack:
