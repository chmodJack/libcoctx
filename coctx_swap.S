.text
.globl coctx_swap
.type coctx_swap, @function
coctx_swap:
	# Save current context to ctx_0 (rdi)
	# regs layout: r15(0), r14(8), r13(16), r12(24), r9(32), r8(40),
	#              rbp(48), rdi(56), rsi(64), ret(72), rdx(80), rcx(88), rbx(96), rsp(104)
	leaq (%rsp), %rax
	movq %rax, 104(%rdi)    # rsp
	movq %rbx, 96(%rdi)     # rbx
	movq %rcx, 88(%rdi)     # rcx
	movq %rdx, 80(%rdi)     # rdx
	movq 0(%rax), %rax      # read ret addr from stack
	movq %rax, 72(%rdi)     # ret addr
	movq %rsi, 64(%rdi)     # rsi
	movq %rdi, 56(%rdi)     # rdi
	movq %rbp, 48(%rdi)     # rbp
	movq %r8, 40(%rdi)      # r8
	movq %r9, 32(%rdi)      # r9
	movq %r12, 24(%rdi)     # r12
	movq %r13, 16(%rdi)     # r13
	movq %r14, 8(%rdi)      # r14
	movq %r15, (%rdi)       # r15
	xorq %rax, %rax

	# Restore context from ctx_1 (rsi)
	movq 48(%rsi), %rbp
	movq 104(%rsi), %rsp
	movq (%rsi), %r15
	movq 8(%rsi), %r14
	movq 16(%rsi), %r13
	movq 24(%rsi), %r12
	movq 32(%rsi), %r9
	movq 40(%rsi), %r8
	movq 56(%rsi), %rdi
	movq 80(%rsi), %rdx
	movq 88(%rsi), %rcx
	movq 96(%rsi), %rbx
	leaq 8(%rsp), %rsp      # skip saved rax
	pushq 72(%rsi)          # push ret addr

	movq 64(%rsi), %rsi
	ret
.size coctx_swap, .-coctx_swap