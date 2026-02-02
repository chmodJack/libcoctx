#ifndef __CO_CTX_H__
#define __CO_CTX_H__

struct coctx_t
{
	unsigned char* regs[14];
	unsigned char* sp;
	unsigned long  size;
};

void coctx_make(struct coctx_t* ctx, void*(*pfn)(void*),const void* arg);
void coctx_swap(struct coctx_t* ctx_0, struct coctx_t* ctx_1) asm("coctx_swap");

#endif
