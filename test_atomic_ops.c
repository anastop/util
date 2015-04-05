/**
 * @file 
 * Uniprocessor sanity tests for atomic ops
 */

#include <stdio.h>
#include "atomic_x86_64.h" 

int main(int argc, char **argv)
{
    unsigned long x, y, z;
    unsigned int xi, yi, zi;
    int res;

    printf("64-bit:\n");
    printf("----------\n");
    x = 50;
    y = 3;
    printf("z=atomic_fetch_and_add(x=%lu, y=%lu): ", x, y);
    z = atomic_fetch_and_add(&x, y);
    printf("x=%lu z=%lu\n", x, z);

    x = 50;
    y = 3;
    printf("z=atomic_fetch_and_store(x=%lu, y=%lu): ", x, y);
    z = atomic_fetch_and_store(&x, y); 
    printf("x=%lu z=%lu\n", x, z);

    x = 50;
    y = 3;
    printf("atomic_add(x=%lu, y=%lu): ", x, y);
    atomic_add(&x, y); 
    printf("x=%lu\n", x);

    x = 50;
    y = 3;
    printf("atomic_sub(x=%lu, y=%lu): ", x, y);
    atomic_sub(&x, y); 
    printf("x=%lu\n", x);

    x = 50;
    printf("atomic_inc(x=%lu): ", x);
    atomic_inc(&x); 
    printf("x=%lu\n", x);

    x = 50;
    printf("atomic_dec(x=%lu): ", x);
    atomic_dec(&x); 
    printf("x=%lu\n", x);

    x = 50;
    y = 3;
    z = 4;
    printf("res=compare_and_swap(x=%lu, y=%lu, z=%lu): ", x, y, z);
    res = compare_and_swap(&x, y, z);
    printf("res=%d, x=%lu\n", res, x);

    x = 50;
    y = 50;
    z = 4;
    printf("res=compare_and_swap(x=%lu, y=%lu, z=%lu): ", x, y, z);
    res = compare_and_swap(&x, y, z);
    printf("res=%d, x=%lu \n", res, x);
    
    x = 2;
    printf("res=atomic_dec_and_test(x=%lu): ", x);
    res = atomic_dec_and_test(&x);
    printf("res=%d, x=%lu \n", res, x);
    printf("res=atomic_dec_and_test(x=%lu): ", x);
    res = atomic_dec_and_test(&x);
    printf("res=%d, x=%lu \n", res, x);

    printf("\n");

 
    printf("32-bit:\n");
    printf("----------\n");
    xi = 50;
    yi = 3;
    printf("zi=atomic_fetch_and_add_int(xi=%u, yi=%u): ", xi, yi);
    zi = atomic_fetch_and_add_int(&xi, yi);
    printf("xi=%u zi=%u\n", xi, zi);

    xi = 50;
    yi = 3;
    printf("zi=atomic_fetch_and_store_int(xi=%u, yi=%u): ", xi, yi);
    zi = atomic_fetch_and_store_int(&xi, yi); 
    printf("xi=%u zi=%u\n", xi, zi);

    xi = 50;
    yi = 3;
    printf("atomic_add_int(xi=%u, yi=%u): ", xi, yi);
    atomic_add_int(&xi, yi); 
    printf("xi=%u\n", xi);

    xi = 50;
    yi = 3;
    printf("atomic_sub_int(xi=%u, yi=%u): ", xi, yi);
    atomic_sub_int(&xi, yi); 
    printf("xi=%u\n", xi);

    xi = 50;
    printf("atomic_inc_int(xi=%u): ", xi);
    atomic_inc_int(&xi); 
    printf("xi=%u\n", xi);

    xi = 50;
    printf("atomic_dec_int(xi=%u): ", xi);
    atomic_dec_int(&xi); 
    printf("xi=%u\n", xi);

    xi = 50;
    yi = 3;
    zi = 4;
    printf("res=compare_and_swap_int(xi=%u, yi=%u, zi=%u): ", xi, yi, zi);
    res = compare_and_swap_int(&xi, yi, zi);
    printf("res=%d, xi=%u\n", res, xi);

    xi = 50;
    yi = 50;
    zi = 4;
    printf("res=compare_and_swap_int(xi=%u, yi=%u, zi=%u): ", xi, yi, zi);
    res = compare_and_swap_int(&xi, yi, zi);
    printf("res=%d, xi=%u \n", res, xi);

    xi = 2;
    printf("res=atomic_dec_and_test(xi=%u): ", xi);
    res = atomic_dec_and_test_int(&xi);
    printf("res=%d, xi=%u \n", res, xi);
    printf("res=atomic_dec_and_test(xi=%u): ", xi);
    res = atomic_dec_and_test_int(&xi);
    printf("res=%d, xi=%u \n", res, xi);


   
    return 0;
}
