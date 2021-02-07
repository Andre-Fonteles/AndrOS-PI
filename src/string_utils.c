#include "common.h"

/**
 * Parse a unsigned 64 bits number to a string in *str in the chosen base  
 */
void parse_int(u64 number, char *str, int base)
{
    if (base > 36)
        return;

    int length = 0;
    while (str[length] != '\0')
    {
        str[length] = '0';
        length++;
    }

    char remainder;
    while (length > 0)
    {
        length--;
        remainder = (number % base);
        if (remainder > 9)
        {
            remainder -= 10;
            str[length] = 'A' + remainder;
        }
        else
        {
            str[length] = '0' + remainder;
        }
        number /= base;
    }
}