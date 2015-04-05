/**
 * @file 
 * Trivial timer test
 */

#include <stdio.h>
#include <stdlib.h>

#include "tsc_x86_64.h"

int main(int argc, char **argv)
{
    tsctimer_t tim;
    int i;
    unsigned int max = atoi(argv[1]);
    unsigned long res, cycles = atol(argv[2]);

    fprintf(stderr, "Spinning for %lu cycles...", cycles);
    spin_for_cycles(cycles);
    printf("OK\n");

    fprintf(stderr, "Measuring average rdtsc execution time:");
    timer_clear(&tim);
    timer_start(&tim);
    for ( i = 0; i < max; i++ )
        res = timer_read();
    timer_stop(&tim);
    printf("Average cycles per rdtsc read: %lf\n", timer_total(&tim)/max);

    return 0;
}
