/*
 * 
 *  Backend code for the 01 Functions exercise. 
 *  Take a look at it and have fun ;-)
 * 
 *  NOTE: This will only work on windows
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include <intrin.h>

int32_t serial_status = -1; // >= 0  - Read for data
                            //  = -1 - Serial closed (not opened)
                            //  = -2 - Serial closed (error)

uint16_t CountBits(uint16_t value)
{
    return __popcnt16(value);
}

void SerialBegin()
{
    if (serial_status == -1)
    {
        printf(" === Ready for sending Serial Data === \n");
        serial_status = 0;
    }
    else if (serial_status >= 0)
    {
        printf("Serial already opened!\n");
    }
    else
    {
        printf("Error in Serial interface!\n");
    }
}

void SerialEnd()
{
    if (serial_status != -1)
    {
        printf(" === End of serial data transmition (Sent %i Word(s)) === \n", serial_status);
        serial_status = -1;
    }
    else
    {
        printf("Serial already closed!\n");
    }
}

uint32_t SerialSend(uint16_t data, uint8_t parity)
{
    if (serial_status < 0)
    {
        printf("Error in Serial interface!\n");
    }

    if (parity != 0 && parity != 1)
    {
        serial_status = -2;
    }

    uint16_t bitCount = CountBits(data);
    uint8_t expectedParity = bitCount % 2;
    if (expectedParity != parity)
    {
        serial_status = -2;
    }

    printf("Sending: 0x%04X 0x%01X\n", data, parity);
    serial_status++;
}

