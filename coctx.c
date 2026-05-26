#include "coctx.h"

// regs layout:
//   [0] rbx  [1] rbp  [2] r12  [3] r13
//   [4] r14  [5] r15  [6] rdi  [7] rsp

void coctx_make(struct coctx_t* ctx, void*(*pfn)(void*), void* arg)
{
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->sp + ctx->size) & ~0xFUL);
	*--sp = (unsigned long)pfn;   // ret in coctx_swap pops this as return addr

	ctx->regs[6] = arg;
	ctx->regs[7] = sp;
}
