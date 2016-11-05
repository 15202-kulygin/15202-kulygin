	.file	"lab3.c"
	.text
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB33:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movsd	%xmm0, 8(%rsp)
	pxor	%xmm4, %xmm4
	movsd	%xmm4, (%rsp)
	movl	$0, %ebx
.L4:
	pxor	%xmm1, %xmm1
	cvtsi2sd	%ebx, %xmm1
	movsd	8(%rsp), %xmm2
	ucomisd	%xmm1, %xmm2
	jb	.L6
	movsd	.LC1(%rip), %xmm0
	call	pow
	mulsd	.LC2(%rip), %xmm0
	leal	1(%rbx,%rbx), %eax
	pxor	%xmm1, %xmm1
	cvtsi2sd	%eax, %xmm1
	divsd	%xmm1, %xmm0
	addsd	(%rsp), %xmm0
	movsd	%xmm0, (%rsp)
	addl	$1, %ebx
	jmp	.L4
.L6:
	movsd	(%rsp), %xmm0
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE33:
	.size	_Z9pi_numberd, .-_Z9pi_numberd
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"Put int the n parameter :"
.LC4:
	.string	"%lf"
.LC5:
	.string	"Result : %f\n"
.LC7:
	.string	"Time : %lf sec\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB34:
	.cfi_startproc
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movl	$.LC3, %edi
	call	puts
	movq	$0, 24(%rsp)
	leaq	24(%rsp), %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	scanf
	leaq	32(%rsp), %rsi
	movl	$4, %edi
	call	clock_gettime
	movsd	24(%rsp), %xmm0
	call	_Z9pi_numberd
	movsd	%xmm0, 8(%rsp)
	leaq	48(%rsp), %rsi
	movl	$4, %edi
	call	clock_gettime
	movsd	8(%rsp), %xmm0
	movl	$.LC5, %esi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk
	movq	48(%rsp), %rdx
	subq	32(%rsp), %rdx
	movq	56(%rsp), %rax
	subq	40(%rsp), %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	mulsd	.LC6(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rdx, %xmm1
	addsd	%xmm1, %xmm0
	movl	$.LC7, %esi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk
	movq	72(%rsp), %rcx
	xorq	%fs:40, %rcx
	je	.L9
	call	__stack_chk_fail
.L9:
	movl	$0, %eax
	addq	$88, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE34:
	.size	main, .-main
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
.LC6:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
