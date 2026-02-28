#include "kernel.h"
#include "intrinsics.h"

void MemoryIntrinsics()
{
	write(1, "# MemoryIntrinsics:\n", 20);

	static const char_t testString[126] = "Yes I should not get copied into a local buffer every time this function gets called, because of the const in the declaration.";
	char_t *stackMemory = (char_t *)__builtin_alloca(126);

	/* ------------------------------------------------- */

	// set to 0
	for (uint16_t i = 0; i < 126; ++i) stackMemory[i] = 0;

	// asm rep movsb - try copy
	MemoryCopyX86(stackMemory, testString, 126);

	// fail if any char is 0
	for (uint16_t i = 0; i < 126; ++i)
	{
		if (stackMemory[i] != testString[i])
		{
			write(1, "MemoryCopyX86 failed! Some or all chars were not copied.", 56);
			exit(1);
		}
	}

	write(1, "MemoryCopyX86: OK\n", 18);

	/* ------------------------------------------------- */

	// asm rep stosb - try set set to 0
	MemoryFillX86(stackMemory, 0, 126);

	// fail if any char is not 0
	for (uint16_t i = 0; i < 126; ++i)
	{
		if (stackMemory[i] != 0)
		{
			write(1, "MemoryFillX86 failed! Some or all chars were not 0.", 51);
			exit(1);
		}
	}

	write(1, "MemoryFillX86: OK\n", 18);

	/* ------------------------------------------------- */

	// asm rep movsb std - try copy
	MemoryInverseCopyX86(stackMemory, testString, 126);

	// fail if any char is 0
	for (uint16_t i = 0; i < 126; ++i)
	{
		if (stackMemory[i] != testString[i])
		{
			write(1, "MemoryInverseCopyX86 failed! Some or all chars were not copied.", 63);
			exit(1);
		}
	}

	write(1, "MemoryInverseCopyX86: OK\n", 25);

	/* ------------------------------------------------- */

	// asm repe cmpsb - should be equal
	if (!MemoryCompareX86(stackMemory, testString, 126))
	{
		write(1, "MemoryCompareX86 failed! Expected result: buffer are equal", 58);
		exit(1);
	}

	stackMemory[23] = '#';

	if (MemoryCompareX86(stackMemory, testString, 126))
	{
		write(1, "MemoryCompareX86 failed! Expected result: buffer are not equal", 58);
		exit(1);
	}

	write(1, "MemoryCompareX86: OK\n", 21);

	/* ------------------------------------------------- */

	MemoryFillX86(stackMemory, '+', 126);

	if (!MemoryIsValueX86(stackMemory, '+', 126))
	{
		write(1, "MemoryIsValueX86 failed! Expected result: buffer is value", 57);
		exit(1);
	}

	stackMemory[67] = 'X';

	if (MemoryIsValueX86(stackMemory, '+', 126))
	{
		write(1, "MemoryIsValueX86 failed! Expected result: buffer is not value", 61);
		exit(1);
	}

	write(1, "MemoryIsValueX86: OK\n", 21);

	/* ------------------------------------------------- */

	MemoryCopyX86(stackMemory, testString, 126);

	if (MemoryGetFirstMismatchIndexX86(stackMemory, testString, 126) != -1)
	{
		write(1, "MemoryGetFirstMismatchIndexX86 failed! No mismatch test", 55);
		exit(1);
	}

	stackMemory[67] = '#';

	if (MemoryGetFirstMismatchIndexX86(stackMemory, testString, 126) != 67)
	{
		write(1, "MemoryGetFirstMismatchIndexX86 failed! Mismatch test", 52);
		exit(1);
	}

	write(1, "MemoryGetFirstMismatchIndexX86: OK\n", 35);

	/* ------------------------------------------------- */

	MemoryCopyX86(stackMemory, testString, 126);

	if (MemoryGetFirstMatchIndexX86(stackMemory, 3, 126) != -1)
	{
		write(1, "MemoryGetFirstMatchIndexX86 failed! Unexpected return value when set up to not find.", 84);
		exit(1);
	}

	stackMemory[67] = '#';

	if (MemoryGetFirstMatchIndexX86(stackMemory, '#', 126) != 67)
	{
		write(1, "MemoryGetFirstMatchIndexX86 failed! Unexpected return value when set up to find mismatch.", 89);
		exit(1);
	}

	write(1, "MemoryGetFirstMatchIndexX86: OK\n", 32);

	/* ------------------------------------------------- */

	write(1, "\n", 1);
}