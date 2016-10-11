	.file	"lab3.c"
	.text
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	%xmm0, -24(%rbp)
	movl	$0, -12(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	$0, -12(%rbp)
.L4:
	pxor	%xmm0, %xmm0
	cvtsi2sd	-12(%rbp), %xmm0
	movsd	-24(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	jb	.L7
	pxor	%xmm0, %xmm0
	cvtsi2sd	-12(%rbp), %xmm0
	movapd	%xmm0, %xmm1
	movsd	.LC1(%rip), %xmm0
	call	pow
	movapd	%xmm0, %xmm1
	movsd	.LC2(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movl	-12(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	pxor	%xmm1, %xmm1
	cvtsi2sd	%eax, %xmm1
	divsd	%xmm1, %xmm0
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
	jmp	.L4
.L7:
	movsd	-8(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z9pi_numberd, .-_Z9pi_numberd
	.section	.rodata
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
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$.LC3, %edi
	call	puts
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -64(%rbp)
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	scanf
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$4, %edi
	call	clock_gettime
	movq	-64(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	call	_Z9pi_numberd
	movq	%xmm0, %rax
	movq	%rax, -56(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$4, %edi
	call	clock_gettime
	movq	-56(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC5, %edi
	movl	$1, %eax
	call	printf
	movq	-32(%rbp), %rdx
	movq	-48(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm1
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC6(%rip), %xmm2
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movl	$.LC7, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L10
	call	__stack_chk_fail
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
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
