/**
 * @file
 * x86-64 atomic operations
 */ 

#ifndef ATOMIC_X86_64_H_
#define ATOMIC_X86_64_H_

/**
 * Implements a full memory fence.
 * @note From 253666 manual: guarantees that every load and store 
 * instruction that precedes in program order the MFENCE instruction 
 * is globally visible before any load or store instruction that 
 * follows the MFENCE instruction is globally visible. 
 * The MFENCE instruction is ordered w.r.t. load and store 
 * instructions, other MFENCE instructions, any SFENCE and
 * LFENCE instructions and any serializing instructions
 * (e.g. CPUID).
 */ 
static inline void mfence()
{
    __asm__ __volatile__ ("mfence" : : : "memory");
}


/**
 * Implements a load fence. 
 * @note From 253666 manual: guarantees that every load instruction 
 * that precedes in program order the LFENCE instruction is globally 
 * visible before any load instruction that follows the LFENCE 
 * instruction is globally visible. 
 * The LFENCE instruction is ordered w.r.t. load instructions, 
 * other LFENCE instructions, any MFENCE instructions, and any 
 * serializing instructions (e.g. CPUID). It is not ordered w.r.t. 
 * store instructions of the SFENCE instruction.
 */ 
static inline void lfence()
{
    __asm__ __volatile__ ("lfence" : : : "memory");
}


/**
 * Implements a store fence.
 * @note From 253667 manual: guarantees that every store instruction 
 * that precedes in program order the SFENCE instruction is globally 
 * visible before any store instruction that follows the SFENCE 
 * instruction is globally visible. 
 * The SFENCE instruction is ordered w.r.t. store instructions, 
 * other SFENCE instructions, any MFENCE instructions, and any 
 * serializing instructions (e.g. CPUID). It is not ordered w.r.t. 
 * load instructions of the LFENCE instruction.
 */
static inline void sfence()
{
    __asm__ __volatile__ ("sfence" : : : "memory");
}


/**
 * Implements a compiler barrier
 * Hardware's reordering operates normally
 */
static inline void compiler_barrier()
{
    __asm__ __volatile__ ("" : : : "memory");
}

/**
 * Implements a memory barrier using a locked add operation.
 * See blogs.sun.com/dave/entry/instruction_selection_for_volatile_fences
 * for more info.
 */ 
static inline void mfence_lockadd()
{
    __asm__ __volatile__ ("lock; addq $0, (%%rsp)"::);
}

/**
 * Writes to a memory location with release semantics. 
 * This means that all previous writes will become globally 
 * visible before the releasing write.
 * @note A common use case is in lock-release operations
 * (hence the name of the semantic, possibly), where the
 * write operation that releases the lock must occur after
 * any write operation inside the lock. 
 * Another use case is e.g. when we want to inialize an object 
 * and then publish a pointer to it in some global location p. 
 * We have to guarantee that the write of its new value must 
 * occur before the write to p, to ensure that threads accessing 
 * the location will read an initialized object. The memory 
 * barrier put before the relasing write guarantees this ordering.
 * 
 * @param p Pointer to memory location
 * @param val value to write
 */ 
static inline void store_release(volatile unsigned long *p,
                                 unsigned long val)
{
    mfence();  
    *p = val;   
}


/**
 * Reads from a memory location with acquire semantics.
 * This means that all subsequent reads will happen after
 * the acquiring read.
 * @param p pointer to memory location
 * @return value read from memory location
 */  
static inline unsigned long load_acquire(volatile unsigned long *p)
{
    unsigned long result = *p;
    mfence();
    return result;
}


/**
 * Atomically adds an increment value to a given memory
 * location and returns the original value of the location.
 * The lock prefix implies a full memory barrier.
 * @param p pointer to 64-bit memory location
 * @param incr 64-bit increment value
 * @return original value of memory location
 */ 
static inline unsigned long 
atomic_fetch_and_add(volatile unsigned long *p, unsigned long incr)
{
    unsigned long oldval;

    // XADD r64, r/m64: exchanges operands and loads sum into r/m64

    __asm__ __volatile__ ("lock; xaddq %0, %1"
                          : "=r" (oldval), "=m" (*p)
                          : "0" (incr), "m" (*p)
                          : "memory");
    return oldval;
}


/**
 * Atomically fetches the value of a memory location and 
 * stores a new one into it. It returns the original value 
 * of the location.
 * The XCHG instruction does not need a lock prefix, and
 * implies a full memory barrier.
 * @param p pointer to 64-bit memory location
 * @param val 64-bit value to store
 * @return original value of memory location
 */ 
static inline unsigned long 
atomic_fetch_and_store(volatile unsigned long *p, unsigned long val)
{
    unsigned long oldval;

    // XCHG r64, r/m64: exchanges operands 

    __asm__ __volatile__ ("xchgq %0, %1"
                          : "=r" (oldval), "=m" (*p)
                          : "0" (val), "m" (*p)
                          : "memory");
    return oldval;
}


/**
 * Atomically adds an increment value to a given memory location 
 * The lock prefix implies a full memory barrier.
 * @param p pointer to 64-bit memory location
 * @param incr 64-bit increment value
 */ 
static inline void  
atomic_add(volatile unsigned long *p, unsigned long incr)
{
    // ADD r64, r/m64: add r64 to r/m64

    __asm__ __volatile__ ("lock; addq %2, %0"
                          : "=m" (*p)
                          : "m" (*p), "r" (incr)
                          : "memory");
}


/**
 * Atomically increments by 1 a given memory location 
 * The lock prefix implies a full memory barrier.
 * @param p pointer to 64-bit memory location
 */ 
static inline void  
atomic_inc(volatile unsigned long *p)
{
    // INC r/m64: increment by 1 r/m64

    __asm__ __volatile__ ("lock; incq %0"
                          : "=m" (*p)
                          : "m" (*p)
                          : "memory");
}


/**
 * Atomically subtracts a decrement value from a given memory 
 * location 
 * The lock prefix implies a full memory barrier.
 * @param p pointer to 64-bit memory location
 * @param incr 64-bit decrement value
 */ 
static inline void  
atomic_sub(volatile unsigned long *p, unsigned long decr)
{
    // SUB r64, r/m64: subtract r64 from r/m64

    __asm__ __volatile__ ("lock; subq %2, %0"
                          : "=m" (*p)
                          : "m" (*p), "r" (decr)
                          : "memory");
}


/**
 * Atomically decrements by 1 a given memory location 
 * The lock prefix implies a full memory barrier.
 * @param p pointer to 64-bit memory location
 */ 
static inline void  
atomic_dec(volatile unsigned long *p)
{
    // DEC r/m64: decrement by 1 r/m64

    __asm__ __volatile__ ("lock; decq %0"
                          : "=m" (*p)
                          : "m" (*p)
                          : "memory");
}


/**
 * Atomically compares *p to oldval for equality, and replaces 
 * *p with newval if the comparison succeeds. 
 * @param p Pointer to 64-bit memory location
 * @param oldval 64-bit value to compare memory location with
 * @param newval 64-bit value to replace memory location with 
 * @return nonzero if the comparison is successful and newval was written
 */ 
static inline int compare_and_swap(volatile unsigned long *p,
                                   unsigned long oldval,
                                   unsigned long newval)
{
    char result;

    // CMPXCHG r64, r/m64: Compare RAX with r/m64. 
    // If equal, ZF is set and r64 is loaded into r/m64. 
    // Else, clear ZF and load r/m64 into RAX.
     
    __asm__ __volatile__ ("lock; cmpxchgq %3, %0; setz %1" 
                          : "=m" (*p), "=q" (result)
                          : "m"  (*p), "r" (newval), "a" (oldval)
                          : "memory" );

    return (int)result;
}

/**
 * Atomically decrements *p by 1 and tests equality with 0.
 * @param p Pointer to 64-bit memory location
 * @return nonzero if value decremented to 0, 0 otherwise
 */ 
static inline int atomic_dec_and_test(volatile unsigned long *p)
{
	char result;

	__asm__ __volatile__( "lock; decq %0; setz %1"
					      :"=m" (*p), "=q" (result)
						  :"m" (*p) 
						  : "memory");
	return (int)result;
}




// 32-bit versions

/**
 * 32-bit version of atomic_fetch_and_add
 * @param p pointer to 32-bit memory location
 * @param incr 32-bit increment value
 * @return original value of memory location
 */ 
static inline unsigned int
atomic_fetch_and_add_int(volatile unsigned int *p, unsigned int incr)
{
    unsigned int oldval;
    
    __asm__ __volatile__ ("lock; xaddl %0, %1"
                          : "=r" (oldval), "=m" (*p)
                          : "0" (incr), "m" (*p)
                          : "memory");
    return oldval;
}


/**
 * 32-bit version of atomic_fetch_and_store
 * @param p pointer to 32-bit memory location
 * @param val 32-bit value to store
 * @return original value of memory location
 */ 
static inline unsigned int
atomic_fetch_and_store_int(volatile unsigned int *p, unsigned int val)
{
    unsigned int oldval;

    __asm__ __volatile__ ("xchgl %0, %1"
                          : "=r" (oldval), "=m" (*p)
                          : "0" (val), "m" (*p)
                          : "memory");
    return oldval;
}


/**
 * 32-bit version of atomic_add
 * @param p pointer to 32-bit memory location
 * @param incr 32-bit increment value
 */ 
static inline void  
atomic_add_int(volatile unsigned int *p, unsigned int incr)
{
    __asm__ __volatile__ ("lock; addl %2, %0"
                          : "=m" (*p)
                          : "m" (*p), "r" (incr)
                          : "memory");
}


/**
 * 32-bit version of atomic_inc
 * @param p pointer to 32-bit memory location
 */ 
static inline void  
atomic_inc_int(volatile unsigned int *p)
{
    __asm__ __volatile__ ("lock; incl %0"
                          : "=m" (*p)
                          : "m" (*p)
                          : "memory");
}


/**
 * 32-bit version of atomic_sub
 * @param p pointer to 32-bit memory location
 * @param incr 32-bit decrement value
 */ 
static inline void  
atomic_sub_int(volatile unsigned int *p, unsigned int decr)
{
    __asm__ __volatile__ ("lock; subl %2, %0"
                          : "=m" (*p)
                          : "m" (*p), "r" (decr)
                          : "memory");
}


/**
 * 32-bit version of atomic_dec
 * @param p pointer to 32-bit memory location
 */ 
static inline void  
atomic_dec_int(volatile unsigned int *p)
{
    __asm__ __volatile__ ("lock; decl %0"
                          : "=m" (*p)
                          : "m" (*p)
                          : "memory");
}



/**
 * Atomically adds an increment value to a given memory
 * location and returns the original value of the location.
 * The lock prefix implies a full memory barrier.
 * @param p pointer to memory location (1 byte)
 * @param incr increment value (1 byte)
 * @return original value of memory location
 */ 
static inline unsigned char
atomic_fetch_and_add_char(volatile unsigned char *p, unsigned char incr)
{
    unsigned char oldval;
    
    __asm__ __volatile__ ("lock; xaddb %0, %1"
                          : "=r" (oldval), "=m" (*p)
                          : "0" (incr), "m" (*p)
                          : "memory");
    return oldval;
}


/**
 * 32-bit version of compare_and_swap
 * @param p Pointer to 32-bit memory location
 * @param oldval 32-bit value to compare memory location with
 * @param newval 32-bit value to replace memory location with 
 * @return nonzero if the comparison is successful and newval was written
 */ 
static inline int compare_and_swap_int(volatile unsigned int *p,
                                       unsigned int oldval,
                                       unsigned int newval)
{
    char result;

    // CMPXCHG r32, r/m32: Compare EAX with r/m32. 
    // If equal, ZF is set and r32 is loaded into r/m32. 
    // Else, clear ZF and load r/m32 into EAX.
     
    __asm__ __volatile__ ("lock; cmpxchgl %3, %0; setz %1" 
                          : "=m" (*p), "=q" (result)
                          : "m"  (*p), "r" (newval), "a" (oldval)
                          : "memory" );

    return (int) result;
}

/**
 * 32-bit version of atomic_dec_and_test
 * Atomically decrements *p by 1 and tests equality with 0.
 * @param p Pointer to 32-bit memory location
 * @return nonzero if value decremented to 0, 0 otherwise
 */ 
static inline int atomic_dec_and_test_int(volatile unsigned int *p)
{
	char result;

	__asm__ __volatile__( "lock; decl %0; setz %1"
					      :"=m" (*p), "=q" (result)
						  :"m" (*p) 
						  : "memory");
	return (int)result;
}


#endif // ATOMIC_X86_64_H_
