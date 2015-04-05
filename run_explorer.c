/**
 * @file
 * Explores and reports processor info for the system
 */ 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "processor_map.h"

int main(int argc, char **argv)
{
    procmap_t *pi = procmap_init();
    procmap_report(pi);
    procmap_destroy(pi);

    return 0;
}
