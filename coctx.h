#ifndef __CO_CTX_H__
#define __CO_CTX_H__

#define COCTX_STACK_SIZE (8 * 1024 * 1024)
#define COCTX_MAX (8)

#if defined(__x86_64__)

// regs layout (x86-64):
//   [0] rbx  [1] rbp  [2] r12  [3] r13
//   [4] r14  [5] r15  [6] rdi  [7] rsp
struct coctx_t
{
	void* regs[8];
	unsigned char stack[COCTX_STACK_SIZE];
};

#elif defined(__aarch64__)

// regs layout (aarch64):
//   [0]  x19  [1]  x20  [2]  x21  [3]  x22
//   [4]  x23  [5]  x24  [6]  x25  [7]  x26
//   [8]  x27  [9]  x28  [10] x29  [11] x30 (LR)
//   [12] sp
struct coctx_t
{
	void* regs[13];
	unsigned char stack[COCTX_STACK_SIZE];
};

#elif defined(__arm__)

// regs layout (arm32):
//   [0] r4   [1] r5   [2] r6   [3] r7
//   [4] r8   [5] r9   [6] r10  [7] r11
//   [8] sp   [9] lr
struct coctx_t
{
	void* regs[10];
	unsigned char stack[COCTX_STACK_SIZE];
};

#elif defined(__riscv)

// regs layout (riscv64 / riscv32):
//   [0]  ra   [1]  sp   [2]  s0   [3]  s1
//   [4]  s2   [5]  s3   [6]  s4   [7]  s5
//   [8]  s6   [9]  s7   [10] s8   [11] s9
//   [12] s10  [13] s11
struct coctx_t
{
	void* regs[14];
	unsigned char stack[COCTX_STACK_SIZE];
};

#else
#error "Unsupported architecture (only x86-64, aarch64, arm32, riscv64, riscv32)"
#endif

void coctx_make(int index, void(*pfn)(void));
void coctx_switch(struct coctx_t* from, struct coctx_t* to);
void coctx_swap(int from, int to);

#endif
