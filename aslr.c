#include "types.h"
#include "kernel.h"
#include "utility.h"

static uint32_t _globalVariable = 0;

void DebugASLR()
{
    write(1, "# ASLR Debug Output:\n", 21);

    uint32_t stackVariable = 67;

    uint32_t* stackVariablePointer = &stackVariable;
    uint32_t* globalVariablePointer = &_globalVariable;
    void (*functionPointer)() = &DebugASLR;
    uint8_t* heapMemory = (uint8_t*)mmap(null, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, (uint32_t)-1, 0);
    if (CheckErrno((int64_t)heapMemory)) write(1, "mmap error\n", 11);

    char_t* stackVariableString = (char_t*)__builtin_alloca(21);
    stackVariableString[20] = '\n';
    uint16_t stackVariableStringLength = UInt64ToChar((uint64_t)stackVariablePointer, stackVariableString);

    char_t* globalVariableString = (char_t*)__builtin_alloca(21);
    uint16_t globalVariableStringLength = UInt64ToChar((uint64_t)globalVariablePointer, globalVariableString);
    globalVariableString[20] = '\n';

    char_t* functionVariableString = (char_t*)__builtin_alloca(21);
    uint16_t functionVariableStringLength = UInt64ToChar((uint64_t)functionPointer, functionVariableString);
    functionVariableString[20] = '\n';

    char_t* heapVariableString = (char_t*)__builtin_alloca(21);
    uint16_t heapVariableStringLength = UInt64ToChar((uint64_t)heapMemory, heapVariableString);
    heapVariableString[20] = '\n';

    write(1, "Stack Variable: ", 16);
    write(1, stackVariableString + (20 - stackVariableStringLength), 1l + stackVariableStringLength);
    write(1, "Global Variable: ", 17);
    write(1, globalVariableString + (20 - globalVariableStringLength), 1l + globalVariableStringLength);
    write(1, "Function Pointer: ", 18);
    write(1, functionVariableString + (20 - functionVariableStringLength), 1l + functionVariableStringLength);
    write(1, "Heap Allocation: ", 17);
    write(1, heapVariableString + (20 - heapVariableStringLength), 1l + heapVariableStringLength);
    write(1, "\n", 1);
}