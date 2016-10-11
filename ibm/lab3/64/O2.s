	.file	"lab3.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB33:
	.cfi_startproc
	pxor	%xmm1, %xmm1
	ucomisd	%xmm1, %xmm0
	jb	.L8
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movapd	%xmm1, %xmm2
	xorl	%ebx, %ebx
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movsd	%xmm0, 8(%rsp)
	.p2align 4,,10
	.p2align 3
.L4:
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm2, (%rsp)
	call	pow
	pxor	%xmm1, %xmm1
	leal	1(%rbx,%rbx), %eax
	mulsd	.LC2(%rip), %xmm0
	addl	$1, %ebx
	movsd	8(%rsp), %xmm3
	cvtsi2sd	%eax, %xmm1
	movsd	(%rsp), %xmm2
	divsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sd	%ebx, %xmm1
	addsd	%xmm0, %xmm2
	ucomisd	%xmm1, %xmm3
	jnb	.L4
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	movapd	%xmm2, %xmm0
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
.L8:
	movapd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE33:
	.size	_Z9pi_numberd, .-_Z9pi_numberd
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"Put int the n parameter :"
.LC5:
	.string	"%lf"
.LC6:
	.string	"Result : %f\n"
.LC8:
	.string	"Time : %lf sec\n"
	.section	.text.unlikely
.LCOLDB9:
	.section	.text.startup,"ax",@progbits
.LHOTB9:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB34:
	.cfi_startproc
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movl	$.LC4, %edi
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	call	puts
	leaq	24(%rsp), %rsi
	movl	$.LC5, %edi
	xorl	%eax, %eax
	movq	$0, 24(%rsp)
	call	scanf
	leaq	32(%rsp), %rsi
	movl	$4, %edi
	call	clock_gettime
	movsd	24(%rsp), %xmm0
	call	_Z9pi_numberd
	leaq	48(%rsp), %rsi
	movl	$4, %edi
	movsd	%xmm0, 8(%rsp)
	call	clock_gettime
	movsd	8(%rsp), %xmm0
	movl	$.LC6, %esi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk
	movq	56(%rsp), %rax
	subq	40(%rsp), %rax
	movl	$.LC8, %esi
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	48(%rsp), %rax
	subq	32(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	mulsd	.LC7(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk
	movq	72(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L16
	xorl	%eax, %eax
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L16:
	.cfi_restore_state
	call	__stack_chk_fail
	.cfi_endproc
.LFE34:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE9:
	.section	.text.startup
.LHOTE9:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	-1074790400
	.align 8
.LC2:
	.long	0
	.long	1074790400
	.align 8
.LC7:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
