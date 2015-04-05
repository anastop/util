/**
 * @file
 * Utility functions signatures
 */ 

#ifndef UTIL_H_
#define UTIL_H_

#define _GNU_SOURCE

#include <sched.h>
#include <sys/types.h>

void trim(char *src, const char tc);
ssize_t readline(int fd, char *vptr, size_t maxlen);
unsigned int galois_lfsr();
unsigned int marsaglia_prng(void); 
void swap(void *x, void *y, size_t elem_size);
void* malloc_aligned(size_t size, size_t alignment);
void* malloc_safe(size_t size);
void flush_caches(int num_proc, unsigned long flush_bytes);
unsigned long get_mask_from_cpuset(cpu_set_t *s);
unsigned long get_current_thread_mask(void);

#endif
