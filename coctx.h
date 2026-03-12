#ifndef __CO_CTX_H__
#define __CO_CTX_H__

#include <stddef.h>

struct coctx_t
{
	unsigned char* regs[14];
	unsigned char* sp;
	unsigned long  size;
};

#define kR15  0
#define kR14  1
#define kR13  2
#define kR12  3
#define kR9   4
#define kR8   5
#define kRBP  6
#define kRDI  7
#define kRSI  8
#define kRETAddr 9
#define kRDX 10
#define kRCX 11
#define kRBX 12
#define kRSP 13

void coctx_init(struct coctx_t* ctx);
void coctx_make(struct coctx_t* ctx, void*(*pfn)(void*),const void* arg);
void coctx_swap(struct coctx_t* ctx_0, struct coctx_t* ctx_1) asm("coctx_swap");

#endif