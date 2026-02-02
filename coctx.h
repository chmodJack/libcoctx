#ifndef __CO_CTX_H__
#define __CO_CTX_H__

struct coctx_t
{
	unsigned char* regs[14];
	unsigned char* sp;
	unsigned long  size;
};

extern "C" void coctx_make(coctx_t* ctx, void*(*pfn)(void*),const void* arg);
extern "C" void coctx_swap(coctx_t* ctx_0, coctx_t* ctx_1) asm("coctx_swap");

#endif
