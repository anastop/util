/**
 * @file
 * Bit operations unit test 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "bitops.h"

void test_all_bits(unsigned long *base, unsigned long nbits)
{
    unsigned long b;
    printf("Set bits: ");
    for ( b = 0; b < nbits; b++ ) {
        if ( bit_test(base, b) == 1 )
            printf("%lu ", b);
    }
    printf("\n");
}


int main(int argc, char **argv)
{
    unsigned long nbits = 20, *ba = bitarray_alloc(nbits);

    printf("\nSetting bit 2\n");
    bit_test_and_set(ba, 2);
    test_all_bits(ba, nbits);
    
    printf("\nChanging bit 5\n");
    bit_test_and_change(ba, 5);
    test_all_bits(ba, nbits);

    printf("\nChanging bit 5\n");
    bit_test_and_change(ba, 5);
    test_all_bits(ba, nbits);

    printf("\nResetting bit 2\n");
    bit_test_and_reset(ba, 2);
    test_all_bits(ba, nbits);

    bitarray_free(ba);
    
    return 0;
}
