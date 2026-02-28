#include "types.h"
#include "kernel.h"
#include "utility.h"
#include "syscalls.h"
#include "intrinsics.h"

void TestOtherX86()
{
    write(1, "# CRC32: init = 0xFFFFFFFFu, finailize ^= 0xFFFFFFFFu\n", 54);

    // https://www.dcode.fr/crc-32
    // create buffer that also works as a verifiable string LE only: 0-,+*)('&%$#!}"
    uint8_t byte = 34;
    uint16_t word = 32033;
    uint32_t dword = (35 << 24) | (36 << 16) | (37 << 8) | 38;
    uint64_t qword = (39ul << 56) | (40ul << 48) | (41ul << 40) | (42ul << 32) | (43ul << 24) | (44ul << 16) | (45ul << 8) | 48ul;
    uint8_t *buffer = (uint8_t *)__builtin_alloca(15);
    MemoryCopyX86(buffer, &qword, 8);
    MemoryCopyX86(buffer + 8, &dword, 4);
    MemoryCopyX86(buffer + 12, &word, 2);
    MemoryCopyX86(buffer + 14, &byte, 1);

    uint32_t crc32c = 0xFFFFFFFFu;
    write(1, "Adding byte\n", 12);
    asm("crc32 %q0, %q1" : "+r"(crc32c) : "r"(qword));
    write(1, "Adding word\n", 12);
    asm("crc32 %0, %k1" : "+r"(crc32c) : "r"(dword));
    write(1, "Adding dword\n", 13);
    asm("crc32 %0, %w1" : "+r"(crc32c) : "r"(word));
    write(1, "Adding qword\n", 13);
    asm("crc32 %0, %b1" : "+r"(crc32c) : "r"(byte));
    crc32c ^= 0xFFFFFFFFu;

    char_t *crc32cString = (char_t *)__builtin_alloca(20);
    uint16_t length = UInt64ToChar(crc32c, crc32cString);
    write(1, "String: 0-,+*)('&%$#!}\"\n", 24);
    write(1, "CRC32C: ", 8);
    write(1, crc32cString + (20 - length), length);
    write(1, "\n", 1);
    if (crc32c != 2011073399)
    {
        write(1, "CRC Error: unexpected value\n", 28);
        exit(1);
    }
    write(1, "OK\n\n: ", 4);

    /* ------------------------------------------------- */

    write(1, "# RNG Test feat.:\n", 18);
    write(1, "X86: rdseed\n", 12);
    write(1, "X86: rdrand\n", 12);

    uint16_t val16 = 0;
    uint32_t val32 = 0;
    uint64_t val64 = 0;
    boolean_t flag = 0;

    flag = RdRand16X86(&val16);
    flag = RdRand32X86(&val32);
    flag = RdRand64X86(&val64);

    asm("pause");

    asm("" : : "r"(flag));
    asm("" : : "r"(val16));
    asm("" : : "r"(val32));
    asm("" : : "r"(val64));

    flag = RdSeed16X86(&val16);
    flag = RdSeed32X86(&val32);
    flag = RdSeed64X86(&val64);

    asm("pause");

    asm("" : : "r"(flag));
    asm("" : : "r"(val16));
    asm("" : : "r"(val32));
    asm("" : : "r"(val64));

    write(1, "OK (no crash)\n\n", 15);

    /* ------------------------------------------------- */
}