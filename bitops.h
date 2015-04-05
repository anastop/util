/**
 * @file 
 * Bit operation function declarations
 */

#ifndef BITOPS_H_
#define BITOPS_H_

unsigned long *bitarray_alloc(unsigned long nbits);
void bitarray_free(unsigned long *base);
void bit_reset_ll(char *byte_addr, int offset);
void bit_change_ll(char *byte_addr, int offset);
void bit_set_ll(char *byte_addr, int offset);
int bit_test_and_reset_ll(char *byte_addr, int offset);
int bit_test_and_change_ll(char *byte_addr, int offset);
int bit_test_and_set_ll(char *byte_addr, int offset);
int bit_test_ll(char *byte_addr, int offset);
int bit_test(unsigned long *base, unsigned long bit);
int bit_test_and_set(unsigned long *base, unsigned long bit);
int bit_test_and_change(unsigned long *base, unsigned long bit);
int bit_test_and_reset(unsigned long *base, unsigned long bit);
void bit_set(unsigned long *base, unsigned long bit);
void bit_change(unsigned long *base, unsigned long bit);
void bit_reset(unsigned long *base, unsigned long bit);

#endif
