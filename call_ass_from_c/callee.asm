; Definieren der Funktion add_ints als globale Funktion (kann von außerhalb aufgerufen werden)
global add_ints

; Definieren des Abschnitts .text (enthält den Code)
section .text

; Definition der Funktion add_ints
add_ints:
    ; ∗∗∗ Standard Subroutinen Prologue ∗∗∗
    ; Verringern des Stackpointers um 0 Bytes --> Allokieren von lokalen Variablen
    sub rsp , 0
    ; Schieben des Registers rbx auf dem Stack
    push rbx

    ; ∗∗∗ Subroutine Body ∗∗∗
    ; Kopieren der Parameter in die Register rax und rbx
    mov rax, rdi
    mov rbx, rsi
    ; Addieren der Werte in den Registern rax und rbx
    add rax, rbx
    
    ; ∗∗∗ Standard subroutine epilogue ∗∗∗
    ; Zurückschreiben des Registers rbx vom Stack
    pop rbx
    ; Erhöhen des Stackpointers um 0 Bytes --> Deallokieren der lokalen Variablen
    add rsp, 0
    ; Rückkehr zur aufrufenden Funktion
    ret
