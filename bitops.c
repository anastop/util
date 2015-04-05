/**
 * @file 
 * Bit operation functions
 */

#include "bitops.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Allocates bit array
 * @param nbits number of bits in the array
 * @return bit array base address
 */ 
unsigned long *bitarray_alloc(unsigned long nbits)
{
	unsigned long *base = (unsigned long*)malloc((nbits >> 3) + 1);
	if ( !base ) {
		fprintf(stderr, "Allocation error!\n");
		exit(EXIT_FAILURE);
	}
	memset(base, 0, (nbits >> 3) + 1);

	return base;
}

/**
 * Deallocates bit array
 * @param base bit array base address
 */ 
void bitarray_free(unsigned long *base)
{
    free(base);
}

/**
 * Resets a bit in memory (low-level) 
 * @param byte_addr address of byte where bit resides
 * @param offset bit offset
 */ 
inline void bit_reset_ll(char *byte_addr, int offset)
{
	__asm__ __volatile__ ("btr %1,%0"
							: "=m" (*byte_addr)
							: "Ir" (offset)
							: "memory");
}

/**
 * Changes a bit in memory (low-level) 
 * @param byte_addr address of byte where bit resides
 * @param offset bit offset
 */ 
inline void bit_change_ll(char *byte_addr, int offset)
{
	__asm__ __volatile__ ("btc %1,%0"
							: "=m" (*byte_addr)
							: "Ir" (offset)
							: "memory");
}

/**
 * Sets a bit in memory (low-level) 
 * @param byte_addr address of byte where bit resides
 * @param offset bit offset
 */ 
inline void bit_set_ll(char *byte_addr, int offset)
{
	__asm__ __volatile__ ("bts %1,%0"
							: "=m" (*byte_addr)
							: "Ir" (offset)
							: "memory");
}

/**
 * Resets a bit in memory and returns its old value (low-level)
 * @param byte_addr address of byte where bit resides
 * @param offset bit offset
 * @return bit value before change
 */ 
inline int bit_test_and_reset_ll(char *byte_addr, int offset)
{
	char result;
	__asm__ __volatile__ ("btr %2,%0; setc %1"
							: "=m" (*byte_addr), "=q" (result)
							: "Ir" (offset)
							: "memory");
	return (int)result;
}

/**
 * Changes a bit in memory and returns its old value (low-level)
 * @param byte_addr address of byte where bit resides
 * @param offset bit offset
 * @return bit value before change
 */ 
inline int bit_test_and_change_ll(char *byte_addr, int offset)
{
	char result;
	__asm__ __volatile__ ("btc %2,%0; setc %1"
							: "=m" (*byte_addr), "=q" (result)
							: "Ir" (offset)
							: "memory");
	return (int)result;
}

/**
 * Sets a bit in memory and returns its old value (low-level)
 * @param byte_addr address of byte where bit resides
 * @param offset bit offset
 * @return bit value before change
 */ 
inline int bit_test_and_set_ll(char *byte_addr, int offset)
{
	char result;
	__asm__ __volatile__ ("bts %2,%0; setc %1"
							: "=m" (*byte_addr), "=q" (result)
							: "Ir" (offset)
							: "memory");
	return (int)result;
}

/**
 * Tests a bit in memory (low-level)
 * @param byte_addr address of byte where bit resides
 * @param offset bit offset
 * @return bit value
 */ 
inline int bit_test_ll(char *byte_addr, int offset)
{
	char result;
	__asm__ __volatile__ ("bt %2,%0; setc %1"
							: "=m" (*byte_addr), "=q" (result)
							: "Ir" (offset)
							: "memory");
	return (int)result;
}

/**
 * Tests a bit in memory
 * @param base base address of bit array 
 * @param nr number of bit 
 * @return bit value
 */ 
inline int bit_test(unsigned long *base, unsigned long bit)
{
	char *byte_addr = (char*)base + (bit >> 3);
	int offset = bit & 7UL;
	return bit_test_ll(byte_addr, offset);
}

/**
 * Sets a bit in memory and returns its old value
 * @param base base address of bit array 
 * @param nr number of bit 
 * @return bit value before change
 */ 
inline int bit_test_and_set(unsigned long *base, unsigned long bit)
{
	char *byte_addr = (char*)base + (bit >> 3);
	int offset = bit & 7UL;
	return bit_test_and_set_ll(byte_addr, offset);
}

/**
 * Changes a bit in memory and returns its old value
 * @param base base address of bit array 
 * @param nr number of bit 
 * @return bit value before change
 */ 
inline int bit_test_and_change(unsigned long *base, unsigned long bit)
{
	char *byte_addr = (char*)base + (bit >> 3);
	int offset = bit & 7UL;
	return bit_test_and_change_ll(byte_addr, offset);
}

/**
 * Resets a bit in memory and returns its old value
 * @param base base address of bit array 
 * @param nr number of bit 
 * @return bit value before change
 */ 
inline int bit_test_and_reset(unsigned long *base, unsigned long bit)
{
	char *byte_addr = (char*)base + (bit >> 3);
	int offset = bit & 7UL;
	return bit_test_and_reset_ll(byte_addr, offset);
}

/**
 * Sets a bit in memory 
 * @param base base address of bit array 
 * @param nr number of bit 
 */ 
inline void bit_set(unsigned long *base, unsigned long bit)
{
	char *byte_addr = (char*)base + (bit >> 3);
	int offset = bit & 7UL;
	bit_set_ll(byte_addr, offset);
}

/**
 * Changes a bit in memory 
 * @param base base address of bit array 
 * @param nr number of bit 
 */ 
inline void bit_change(unsigned long *base, unsigned long bit)
{
	char *byte_addr = (char*)base + (bit >> 3);
	int offset = bit & 7UL;
	bit_change_ll(byte_addr, offset);
}

/**
 * Resets a bit in memory 
 * @param base base address of bit array 
 * @param nr number of bit 
 */ 
inline void bit_reset(unsigned long *base, unsigned long bit)
{
	char *byte_addr = (char*)base + (bit >> 3);
	int offset = bit & 7UL;
	bit_reset_ll(byte_addr, offset);
}

