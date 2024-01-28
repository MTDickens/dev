	.file	"data-passing.c"
	.text
	.globl	my_function
	.type	my_function, @function
my_function:
.LFB0:
	.cfi_startproc
	endbr64
	movq	%rdi, %rax
	imulq	%rsi, %rax
	movq	%rax, (%rdx)
	ret
	.cfi_endproc
.LFE0:
	.size	my_function, .-my_function
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movl	$40, %ebx
	movq	%fs:(%rbx), %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdx
	movl	$3, %esi
	movl	$2, %edi
	call	my_function
	movq	8(%rsp), %rax
	xorq	%fs:(%rbx), %rax
	jne	.L5
	movl	$0, %eax
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
