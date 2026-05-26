#include "coctx.h"

// regs layout:
//   [0] rbx  [1] rbp  [2] r12  [3] r13
//   [4] r14  [5] r15  [6] rdi  [7] rsp

extern void coctx_switch(struct coctx_t* from, struct coctx_t* to) asm("coctx_switch");

#define COCTX_MAX 16
static struct coctx_t* g_co[COCTX_MAX];
static int g_n = 0;
static int g_cur = 0;

static void coctx_make(struct coctx_t* ctx, void*(*pfn)(void*), void* arg)
{
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->sp + ctx->size) & ~0xFUL);
	*--sp = (unsigned long)pfn;   // ret in coctx_switch pops this as return addr

	ctx->regs[6] = arg;
	ctx->regs[7] = sp;
}

void coctx_add(struct coctx_t* ctx, void*(*pfn)(void*), void* arg)
{
	if (pfn) coctx_make(ctx, pfn, arg);
	g_co[g_n++] = ctx;
}

void coctx_swap(void)
{
	int from = g_cur;
	int to = (g_cur + 1) % g_n;
	g_cur = to;
	coctx_switch(g_co[from], g_co[to]);
}
