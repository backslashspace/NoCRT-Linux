__attribute__((naked))
void Start()
{
    asm
    (
        "mov rdi, [rsp];"
        "lea rsi, [rsp + 8];"
        "lea rdx, [rsp + 16];"
        "lea rdx, [rdx + rdi*8];"
        "call Main;"
        "movzx rdi, al;"
        "mov rax, 60;"
        "syscall;"
    );
}