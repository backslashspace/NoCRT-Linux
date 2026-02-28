#include "types.h"

static const char_t DIGITS_LUT[201] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";

uint16_t UInt64ToChar(uint64_t value, char_t *const buffer)
{
    uint16_t position = 19; // max length = 20 - 1
    uint16_t index = 0;

    while (value >= 100)
    {
        index = (uint16_t)(value % 100) << 1;
        value /= 100;
        buffer[position] = DIGITS_LUT[index + 1];
        buffer[position - 1] = DIGITS_LUT[index];
        position -= 2;
    }

    if (value < 10)
    {
        buffer[position] = (48 + (char_t)value);
        return (20 - position);
    }

    index = (uint16_t)value << 1;
    buffer[position] = DIGITS_LUT[index + 1];
    buffer[position - 1] = DIGITS_LUT[index];

    return (20 - position + 1);
}