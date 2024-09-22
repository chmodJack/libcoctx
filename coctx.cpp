#include "coctx.h"
#include <stdio.h>
#include <string.h>

// -----------
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

//-------------
// 64 bit
// low | regs[0]: r15 |
//    | regs[1]: r14 |
//    | regs[2]: r13 |
//    | regs[3]: r12 |
//    | regs[4]: r9  |
//    | regs[5]: r8  |
//    | regs[6]: rbp |
//    | regs[7]: rdi |
//    | regs[8]: rsi |
//    | regs[9]: ret |  //ret func addr
//    | regs[10]: rdx |
//    | regs[11]: rcx |
//    | regs[12]: rbx |
// hig | regs[13]: rsp |
enum
{
	kRDI = 7,
	kRSI = 8,
	kRETAddr = 9,
	kRSP = 13,
};

extern "C" void coctx_make(coctx_t* ctx, coctx_pfn_t pfn, const void* arg)
{
	char* sp = ctx->ss_sp + ctx->ss_size - sizeof(void*);
	sp = (char*)((unsigned long)sp & -16LL);

	memset(ctx->regs, 0, sizeof(ctx->regs));
	void** ret_addr = (void**)(sp);
	*ret_addr = (void*)pfn;

	ctx->regs[kRSP] = sp;

	ctx->regs[kRETAddr] = (char*)pfn;

	ctx->regs[kRDI] = (char*)arg;
}
extern "C" void coctx_init(coctx_t* ctx)
{
	memset(ctx, 0, sizeof(*ctx));
}

