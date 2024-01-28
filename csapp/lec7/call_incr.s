	.file	"call_incr.c"
	.text
	.globl	incr
	.type	incr, @function
incr:
.LFB0:
	.cfi_startproc
	endbr64
	movq	(%rdi,%rsi,8), %rax
	ret
	.cfi_endproc
.LFE0:
	.size	incr, .-incr
	.globl	call_incr
	.type	call_incr, @function
call_incr:
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
	movq	$15213, (%rsp)
	movq	%rsp, %rdi
	movl	$3000, %esi
	call	incr
	addq	$15213, %rax
	movq	8(%rsp), %rdx
	xorq	%fs:(%rbx), %rdx
	jne	.L5
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
	.size	call_incr, .-call_incr
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
