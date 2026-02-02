#include "coctx.h"

#if 0
#define RSP 0
#define RIP 1
#define RBX 2
#define RDI 3
#define RSI 4

#define RBP 5
#define R12 6
#define R13 7
#define R14 8
#define R15 9
#define RDX 10
#define RCX 11
#define R8 12
#define R9 13
#endif

//-------------
// 64 bit
// low | regs[0]: r15  |
//     | regs[1]: r14  |
//     | regs[2]: r13  |
//     | regs[3]: r12  |
//     | regs[4]: r9   |
//     | regs[5]: r8   |
//     | regs[6]: rbp  |
//     | regs[7]: rdi  |
//     | regs[8]: rsi  |
//     | regs[9]: ret  |  //ret func addr
//     | regs[10]: rdx |
//     | regs[11]: rcx |
//     | regs[12]: rbx |
// hig | regs[13]: rsp |

#define	kRDI      7
#define	kRSI      8
#define	kRETAddr  9
#define	kRSP     13

void coctx_make(struct coctx_t* ctx, void*(*pfn)(void*), const void* arg)
{
	unsigned char* sp = ctx->sp + ctx->size - sizeof(unsigned char*);
	sp = (unsigned char*)((unsigned long)sp & -16LL);

	//memset(ctx->regs, 0, sizeof(ctx->regs));
	void** ret_addr = (void**)(sp);
	*ret_addr = (void*)pfn;

	ctx->regs[kRSP] = sp;

	ctx->regs[kRETAddr] = (unsigned char*)pfn;

	ctx->regs[kRDI] = (unsigned char*)arg;
}
