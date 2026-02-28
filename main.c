#include "types.h"
#include "testing.h"
#include "intrinsics.h"

//void Test()
//{
//    asm("pause");
//}

uint8_t Main(uint64_t argc, uint8_t **argv, uint8_t **envp)
{
    //Test();

    /* ------------------------------------------------- */

    MemoryIntrinsics();

    /* ------------------------------------------------- */

    //vDSO(envp);

    /* ------------------------------------------------- */

    DebugASLR();

    TestAVX2();

    TestOtherX86();

    asm volatile("pause" : : "r"(argc), "r"(argv), "r"(envp));

    return 67;
}