.globl coctx_switch
coctx_switch:
	movq %rbx,  0(%rdi)
	movq %rbp,  8(%rdi)
	movq %r12, 16(%rdi)
	movq %r13, 24(%rdi)
	movq %r14, 32(%rdi)
	movq %r15, 40(%rdi)
	movq %rdi, 48(%rdi)
	movq %rsp, 56(%rdi)

	movq  0(%rsi), %rbx
	movq  8(%rsi), %rbp
	movq 16(%rsi), %r12
	movq 24(%rsi), %r13
	movq 32(%rsi), %r14
	movq 40(%rsi), %r15
	movq 56(%rsi), %rsp
	movq 48(%rsi), %rdi
	ret

.section .note.GNU-stack,"",@progbits
