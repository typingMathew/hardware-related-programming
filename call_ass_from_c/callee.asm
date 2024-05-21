
global called_add_ints

section .text

called_add_ints:
    ; ∗∗∗ Standard subroutine prologue ∗∗∗
    sub rsp , 8 
    push rbx 

    ; ∗∗∗ Subroutine Body ∗∗∗
    mov rax, rdi 
    mov rbx, rsi 
    add rax, rbx
    
    ; ∗∗∗ Standard subroutine epilogue ∗∗∗
    pop rbx ;
    add rsp, 8
    ret
