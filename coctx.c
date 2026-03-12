#include "coctx.h"
#include <string.h>

void coctx_init(struct coctx_t* ctx)
{
	memset(ctx->regs, 0, sizeof(ctx->regs));
}

void coctx_make(struct coctx_t* ctx, void*(*pfn)(void*), const void* arg)
{
	memset(ctx->regs, 0, sizeof(ctx->regs));

	unsigned char* sp = ctx->sp + ctx->size - 128;
	sp = (unsigned char*)((unsigned long)sp & -16LL);

	void** ret_addr = (void**)(sp);
	*ret_addr = (void*)pfn;

	ctx->regs[kRSP] = sp;
	ctx->regs[kRETAddr] = (unsigned char*)pfn;
	ctx->regs[kRDI] = (unsigned char*)arg;
	ctx->regs[kRBX] = 0;
	ctx->regs[kRBP] = 0;
	ctx->regs[kR12] = 0;
	ctx->regs[kR13] = 0;
	ctx->regs[kR14] = 0;
	ctx->regs[kR15] = 0;
}