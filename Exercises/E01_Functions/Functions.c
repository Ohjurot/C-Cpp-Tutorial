#include <stdio.h>
#include <stdint.h>

/*
 * Exercise 01 - Functions (e01)
 * 
 * ABOUT:
 * Implementing sending over a serial interface.
 * The given functions emulate a serial interface.
 * 16-Bits are sended at a time. Each 16-Bit word is accompanied
 * with a singel parity bit. From a give 16-Bit word the parity bit
 * can be computed like this:
 * 1 - Count the bits set in the 16-Bit data word
 * 2 - Parity bit is 
 *     0 - when count bits are even (0, 2, 4, 6, 8, 10, 12, 14, 16)
 *     1 - when count bits are odd  (1, 3, 5, 7, 9, 11, 13, 15)
 * The serial interface must be started (SerialBegin) and stoped (SerialEnd)
 * correctly.
 * 
 * TODO:
 * Send the following data via the Serial interface:
 * 0xFFFF 0x1234 0x5678 0x9ABC 0xDEF0 0x0000
 * Use a least one function to make the code more readable
 * 
 * HITS: 
 *  - https://en.wikipedia.org/wiki/Euclidean_division
 *  - https://en.wikipedia.org/wiki/Modulo_operation
 * 
 * VIDEOS:
 *  - Task:         https://youtu.be/XKuywa66u-Q
 *  - Solution:     https://youtu.be/wL92Eef85t8
 */

/*
 *  Function given in e01
 */
uint16_t CountBits(uint16_t value);
void SerialBegin();
void SerialEnd();
void SerialSend(uint16_t data, uint8_t parity);

/*
 *  Your function(s)
 */

/*
 *  Implementation of main 
 */
int main()
{

}

/*
 *  Implementation of your function(s)
 */
