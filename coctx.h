#ifndef __CO_CTX_H__
#define __CO_CTX_H__

struct coctx_t
{
	void* regs[8];   // rbx, rbp, r12, r13, r14, r15, rdi, rsp
	void* sp;
	unsigned long size;
};

void coctx_make(struct coctx_t* ctx, void*(*pfn)(void*), void* arg);
void coctx_swap(struct coctx_t* ctx_0, struct coctx_t* ctx_1) asm("coctx_swap");

#endif
