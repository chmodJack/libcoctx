#ifndef __CO_CTX_H__
#define __CO_CTX_H__

struct coctx_t
{
	void* regs[8];   // rbx, rbp, r12, r13, r14, r15, rdi, rsp
	void* sp;
	unsigned long size;
};

// Register a coroutine into the round-robin scheduler.
// Pass pfn == NULL for the currently-running context (e.g. main),
// which only reserves a slot to save its registers into.
void coctx_add(struct coctx_t* ctx, void*(*pfn)(void*), void* arg);

// Yield to the next coroutine in registration order.
void coctx_swap(void);

#endif
