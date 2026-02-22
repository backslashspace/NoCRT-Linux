#include "types.h"
#include "testing.h"
#include "intrinsics.h"

void Test()
{
    uint64_t test;
    boolean_t flag = Gurt(&test);

    asm("pause");

    asm("pause" : : "r"(flag), "r"(test));
}

uint8_t Main(uint64_t argc, uint8_t** argv, uint8_t** envp)
{
    Test();

    /* ------------------------------------------------- */

    MemoryIntrinsics();

    /* ------------------------------------------------- */

    //vDSO(envp);

    /* ------------------------------------------------- */

    DebugASLR();

    TestAVX2();

    TestOtherX86();

    return 67;
}