#include "coctx.h"

struct coctx_t global_ctx[COCTX_MAX];

#if defined(__x86_64__)

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

void coctx_make(int index, void(*pfn)(void))
{
	struct coctx_t* ctx = global_ctx + index;
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->stack + COCTX_STACK_SIZE) & ~0xFUL);
	*--sp = (unsigned long)pfn;

	ctx->regs[7] = sp;
}

#elif defined(__aarch64__)

__attribute__((naked))
void coctx_switch(struct coctx_t* from, struct coctx_t* to)
{
	__asm__ volatile(
		"stp x19, x20, [x0, #0]\n\t"
		"stp x21, x22, [x0, #16]\n\t"
		"stp x23, x24, [x0, #32]\n\t"
		"stp x25, x26, [x0, #48]\n\t"
		"stp x27, x28, [x0, #64]\n\t"
		"stp x29, x30, [x0, #80]\n\t"
		"mov x2, sp\n\t"
		"str x2, [x0, #96]\n\t"

		"ldp x19, x20, [x1, #0]\n\t"
		"ldp x21, x22, [x1, #16]\n\t"
		"ldp x23, x24, [x1, #32]\n\t"
		"ldp x25, x26, [x1, #48]\n\t"
		"ldp x27, x28, [x1, #64]\n\t"
		"ldp x29, x30, [x1, #80]\n\t"
		"ldr x2, [x1, #96]\n\t"
		"mov sp, x2\n\t"
		"ret\n\t"
	);
}

void coctx_make(int index, void(*pfn)(void))
{
	struct coctx_t* ctx = global_ctx + index;
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->stack + COCTX_STACK_SIZE) & ~0xFUL);

	ctx->regs[11] = (void*)pfn;
	ctx->regs[12] = sp;
}

#elif defined(__arm__)

__attribute__((naked))
void coctx_switch(struct coctx_t* from, struct coctx_t* to)
{
	__asm__ volatile(
		"str r4, [r0, #0]\n\t"
		"str r5, [r0, #4]\n\t"
		"str r6, [r0, #8]\n\t"
		"str r7, [r0, #12]\n\t"
		"str r8, [r0, #16]\n\t"
		"str r9, [r0, #20]\n\t"
		"str r10, [r0, #24]\n\t"
		"str r11, [r0, #28]\n\t"
		"str sp, [r0, #32]\n\t"
		"str lr, [r0, #36]\n\t"

		"ldr r4, [r1, #0]\n\t"
		"ldr r5, [r1, #4]\n\t"
		"ldr r6, [r1, #8]\n\t"
		"ldr r7, [r1, #12]\n\t"
		"ldr r8, [r1, #16]\n\t"
		"ldr r9, [r1, #20]\n\t"
		"ldr r10, [r1, #24]\n\t"
		"ldr r11, [r1, #28]\n\t"
		"ldr lr, [r1, #36]\n\t"
		"ldr sp, [r1, #32]\n\t"
		"bx lr\n\t"
	);
}

void coctx_make(int index, void(*pfn)(void))
{
	struct coctx_t* ctx = global_ctx + index;
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->stack + COCTX_STACK_SIZE) & ~0xFUL);

	ctx->regs[8] = sp;
	ctx->regs[9] = (void*)pfn;
}

#elif defined(__riscv) && __riscv_xlen == 64

__attribute__((naked))
void coctx_switch(struct coctx_t* from, struct coctx_t* to)
{
	__asm__ volatile(
		"sd ra,   0(a0)\n\t"
		"sd sp,   8(a0)\n\t"
		"sd s0,  16(a0)\n\t"
		"sd s1,  24(a0)\n\t"
		"sd s2,  32(a0)\n\t"
		"sd s3,  40(a0)\n\t"
		"sd s4,  48(a0)\n\t"
		"sd s5,  56(a0)\n\t"
		"sd s6,  64(a0)\n\t"
		"sd s7,  72(a0)\n\t"
		"sd s8,  80(a0)\n\t"
		"sd s9,  88(a0)\n\t"
		"sd s10, 96(a0)\n\t"
		"sd s11,104(a0)\n\t"

		"ld ra,   0(a1)\n\t"
		"ld sp,   8(a1)\n\t"
		"ld s0,  16(a1)\n\t"
		"ld s1,  24(a1)\n\t"
		"ld s2,  32(a1)\n\t"
		"ld s3,  40(a1)\n\t"
		"ld s4,  48(a1)\n\t"
		"ld s5,  56(a1)\n\t"
		"ld s6,  64(a1)\n\t"
		"ld s7,  72(a1)\n\t"
		"ld s8,  80(a1)\n\t"
		"ld s9,  88(a1)\n\t"
		"ld s10, 96(a1)\n\t"
		"ld s11,104(a1)\n\t"

		"ret\n\t"
	);
}

void coctx_make(int index, void(*pfn)(void))
{
	struct coctx_t* ctx = global_ctx + index;
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->stack + COCTX_STACK_SIZE) & ~0xFUL);

	ctx->regs[0] = (void*)pfn;
	ctx->regs[1] = sp;
}

#elif defined(__riscv) && __riscv_xlen == 32

__attribute__((naked))
void coctx_switch(struct coctx_t* from, struct coctx_t* to)
{
	__asm__ volatile(
		"sw ra,   0(a0)\n\t"
		"sw sp,   4(a0)\n\t"
		"sw s0,   8(a0)\n\t"
		"sw s1,  12(a0)\n\t"
		"sw s2,  16(a0)\n\t"
		"sw s3,  20(a0)\n\t"
		"sw s4,  24(a0)\n\t"
		"sw s5,  28(a0)\n\t"
		"sw s6,  32(a0)\n\t"
		"sw s7,  36(a0)\n\t"
		"sw s8,  40(a0)\n\t"
		"sw s9,  44(a0)\n\t"
		"sw s10, 48(a0)\n\t"
		"sw s11, 52(a0)\n\t"

		"lw ra,   0(a1)\n\t"
		"lw sp,   4(a1)\n\t"
		"lw s0,   8(a1)\n\t"
		"lw s1,  12(a1)\n\t"
		"lw s2,  16(a1)\n\t"
		"lw s3,  20(a1)\n\t"
		"lw s4,  24(a1)\n\t"
		"lw s5,  28(a1)\n\t"
		"lw s6,  32(a1)\n\t"
		"lw s7,  36(a1)\n\t"
		"lw s8,  40(a1)\n\t"
		"lw s9,  44(a1)\n\t"
		"lw s10, 48(a1)\n\t"
		"lw s11, 52(a1)\n\t"

		"ret\n\t"
	);
}

void coctx_make(int index, void(*pfn)(void))
{
	struct coctx_t* ctx = global_ctx + index;
	unsigned long* sp = (unsigned long*)
		(((unsigned long)ctx->stack + COCTX_STACK_SIZE) & ~0xFUL);

	ctx->regs[0] = (void*)pfn;
	ctx->regs[1] = sp;
}

#else
#error "Unsupported architecture (only x86-64, aarch64, arm32, riscv64, riscv32)"
#endif

void coctx_swap(int from, int to)
{
	coctx_switch(global_ctx + from, global_ctx + to);
}
