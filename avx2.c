#include "kernel.h"
#include "simd_types.h"
#include "intrinsics.h"

void TestAVX2()
{
    write(1, "# AVX2 shuffle feat.:\n", 20);
    write(1, "vmovntdqa (non temporal load)\n", 30);
    write(1, "vpshufb (shuffle bytes in 128 bit lane)\n", 40);
    write(1, "vperm2i128 (permute across lanes)\n", 34);
    write(1, "vmovntdq (non temporal store)\n", 30);

    static const uint8_t STRING_INVERSE_TEST_MASK[32] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0, 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
    static const char_t STRING_INVERSE_TEST[128] = "Yo my nutsack so spread, its dragging behind when i walk through the mall. Like you would not believe, you should see the faces.";

    write(1, "Test case - string inverse: ", 28);
    write(1, STRING_INVERSE_TEST, 128);
    write(1, "\n", 1);

    uint8x32_t* allignedTestBuffer = (uint8x32_t*)__builtin_alloca_with_align(128, 256);
    uint8x32_t* allignedMaskBuffer = (uint8x32_t*)__builtin_alloca_with_align(32, 256);
    uint8x32_t* allignedDestinationBuffer = (uint8x32_t*)__builtin_alloca_with_align(128, 256);

    MemoryCopyX86(allignedTestBuffer, STRING_INVERSE_TEST, 128);
    MemoryCopyX86(allignedMaskBuffer, STRING_INVERSE_TEST_MASK, 32);

    asm
    (   // nt load
        "vmovntdqa ymm0, %0;"
        "vmovntdqa ymm1, %1;"
        "vmovntdqa ymm2, %2;"
        "vmovntdqa ymm3, %3;"
        "vmovntdqa ymm4, %4;"
        :
    : "m"(allignedTestBuffer[0]), "m"(allignedTestBuffer[1]), "m"(allignedTestBuffer[2]), "m"(allignedTestBuffer[3]), "m"(*allignedMaskBuffer)
        : "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "memory"
        );

    // 0 = low  128-bit of source 1
    // 1 = high 128-bit of source 1
    // 2 = low  128-bit of source 2
    // 3 = high 128-bit of source 2
    //
    // upper of 1 + upper of 2 == (3 << 4) | 1 = 0x31
    // upper of 1 + lower of 2 == (2 << 4) | 1 = 0x21
    // lower of 1 + upper of 2 == (3 << 4) | 0 = 0x30
    // lower of 1 + lower of 2 == (2 << 4) | 0 = 0x20

    asm
    (   // shuffle
        "vpshufb ymm0, ymm0, ymm4;"
        "vpshufb ymm1, ymm1, ymm4;"
        "vpshufb ymm2, ymm2, ymm4;"
        "vpshufb ymm3, ymm3, ymm4;"
        "vperm2i128 ymm0, ymm0, ymm0, 0x01;"
        "vperm2i128 ymm1, ymm1, ymm1, 0x01;"
        "vperm2i128 ymm2, ymm2, ymm2, 0x01;"
        "vperm2i128 ymm3, ymm3, ymm3, 0x01;"
        :
    :
        : "ymm0", "ymm1", "ymm2", "ymm3"
        );

    asm
    (   // nt store
        "vmovntdq %0, ymm3;"
        "vmovntdq %1, ymm2;"
        "vmovntdq %2, ymm1;"
        "vmovntdq %3, ymm0;"
        "sfence"
        : "=m"(allignedDestinationBuffer[0]), "=m"(allignedDestinationBuffer[1]), "=m"(allignedDestinationBuffer[2]), "=m"(allignedDestinationBuffer[3])
        :
        : "memory"
    );

    write(1, "Result: ", 8);
    write(1, allignedDestinationBuffer, 128);
    write(1, "\nOK (no crash)\n\n", 16);
}