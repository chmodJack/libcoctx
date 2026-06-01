#ifndef __CO_CTX_H__
#define __CO_CTX_H__

#define COCTX_STACK_SIZE (8 * 1024 * 1024)
#define COCTX_MAX (8)

// regs layout:
//   [0] rbx  [1] rbp  [2] r12  [3] r13
//   [4] r14  [5] r15  [6] rdi  [7] rsp
struct coctx_t
{
	void* regs[8];
	unsigned char stack[COCTX_STACK_SIZE];
};

void coctx_make(int index, void(*pfn)(void));
void coctx_switch(struct coctx_t* from, struct coctx_t* to);
void coctx_swap(int from, int to);

#endif
