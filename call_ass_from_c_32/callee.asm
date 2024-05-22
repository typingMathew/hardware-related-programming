; Definieren der Funktion add_ints als globale Funktion (kann von außerhalb aufgerufen werden)
global add_ints

; Definieren des Abschnitts .text (enthält den Code)
section .text

; Definition der Funktion add_ints
add_ints:
    ; ∗∗∗ Standard Subroutinen Prologue ∗∗∗
    ; Speichern des ursprünglichen Basispointers auf dem Stack
    push ebp
    ; Setzen des Basispointers auf den aktuellen Stackpointer
    mov ebp, esp
    ; Verringern des Stackpointers um 0 Bytes --> Anlegen einer x Byte großen lokalen Variablen
    sub esp, 0
    ; Speichern der Register edi, esi auf dem Stack, da diese nachfolgend verwendet werden
    push edi
    push esi

    ; ∗∗∗ Subroutine Body ∗∗∗
    ; Kopieren des ersten Parameters in das Register eax
    mov eax, [ebp + 8]
    ; Kopieren des zweiten Parameters in das Register edi
    mov edi, [ebp + 12]
    ; Kopieren des dritten Parameters in das Register esi
    mov esi, [ebp + 16]
    ; Addieren der ersten beiden Parameter
    add eax, edi
    ; Addieren des dritten Parameters
    add eax, esi
    
    ; ∗∗∗ Standard subroutine epilogue ∗∗∗
    ; Zurückschreiben der Register edi, esi
    pop esi
    pop edi
    ; Rücksetzen des Stackpointers auf den ursprünglichen Wert
    mov esp, ebp
    ; Zurückschreiben des ursprünglichen Basispointers
    pop ebp
    ; Rückkehr zur aufrufenden Funktion
    ret
