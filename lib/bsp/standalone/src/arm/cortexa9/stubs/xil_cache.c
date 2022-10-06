
/*****************************************************************************/
/**
*
* @file xil_cache.c

* Cache functions provide access to cache related operations such as flush
* and invalidate for instruction and data caches. It gives option to perform
* the cache operations on a single cacheline, a range of memory and an entire
* cache.
* 
* These are stubs for crosscompilation.
*
******************************************************************************/

#include "xil_cache.h"


void Xil_DCacheEnable(void)
{}

void Xil_DCacheDisable(void)
{}
void Xil_DCacheInvalidate(void)
{}
void Xil_DCacheInvalidateRange(INTPTR adr, u32 len)
{
    (void)adr;
    (void)len;
}
void Xil_DCacheFlush(void)
{
}

void Xil_DCacheFlushRange(INTPTR adr, u32 len)
{
    (void)adr;
    (void)len;
}


void Xil_ICacheEnable(void)
{}
void Xil_ICacheDisable(void)
{}
void Xil_ICacheInvalidate(void);
void Xil_ICacheInvalidateRange(INTPTR adr, u32 len)
{
    (void)adr;
    (void)len;
}
