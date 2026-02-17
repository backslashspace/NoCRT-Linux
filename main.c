#include "types.h"
#include "testing.h"

uint8_t Main(uint64_t argc, uint8_t** argv, uint8_t** envp)
{
    MemoryIntrinsics();

    /* ------------------------------------------------- */

    DebugASLR();

    TestAVX2();

    TestOtherX86();

    return 67;
}

