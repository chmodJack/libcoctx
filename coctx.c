#include "coctx.h"

__attribute__((naked))
void coctx_switch(struct coctx_t* from, struct coctx_t* to)
{
	__asm__ volatile(
		"movq %rbx,  0(%rdi)\n\t"
		"movq %rbp,  8(%rdi)\n\t"
		"movq %r12, 16(%rdi)\n\t"
		"movq %r13, 24(%rdi)\n\t"
		"movq %r14, 32(%rdi)\n\t"
		"movq %r15, 40(%rdi)\n\t"
		"movq %rdi, 48(%rdi)\n\t"
		"movq %rsp, 56(%rdi)\n\t"

		"movq  0(%rsi), %rbx\n\t"
		"movq  8(%rsi), %rbp\n\t"
		"movq 16(%rsi), %r12\n\t"
		"movq 24(%rsi), %r13\n\t"
		"movq 32(%rsi), %r14\n\t"
		"movq 40(%rsi), %r15\n\t"
		"movq 56(%rsi), %rsp\n\t"
		"movq 48(%rsi), %rdi\n\t"
		"ret\n\t"
	);
}

struct coctx_t global_ctx[COCTX_MAX];

void coctx_make(int index, void(*pfn)(void))
{
	struct coctx_t* ctx = global_ctx + index;
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->stack + COCTX_STACK_SIZE) & ~0xFUL);
	*--sp = (unsigned long)pfn;

	ctx->regs[7] = sp;
}

void coctx_swap(int from, int to)
{
	coctx_switch(global_ctx + from, global_ctx + to);
}
