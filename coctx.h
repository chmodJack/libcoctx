#ifndef __CO_CTX_H__
#define __CO_CTX_H__

#include <stdlib.h>

typedef void* (*coctx_pfn_t)(void* arg);

struct coctx_t
{
	void*  regs[14];
	size_t ss_size;
	char*  ss_sp;
};

extern "C" void coctx_init(coctx_t* ctx);
extern "C" void coctx_make(coctx_t* ctx, coctx_pfn_t pfn,const void* arg);
extern "C" void coctx_swap(coctx_t* ctx_0, coctx_t* ctx_1) asm("coctx_swap");

#endif
