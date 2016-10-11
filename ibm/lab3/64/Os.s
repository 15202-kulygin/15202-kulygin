	.file	"lab3.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.text
.LHOTB3:
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB19:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorps	%xmm2, %xmm2
	movapd	%xmm0, %xmm3
	xorl	%ebx, %ebx
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
.L4:
	cvtsi2sd	%ebx, %xmm1
	movsd	%xmm3, 8(%rsp)
	ucomisd	%xmm1, %xmm3
	jb	.L6
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm2, (%rsp)
	call	pow
	leal	1(%rbx,%rbx), %eax
	mulsd	.LC2(%rip), %xmm0
	incl	%ebx
	movsd	(%rsp), %xmm2
	cvtsi2sd	%eax, %xmm1
	movsd	8(%rsp), %xmm3
	divsd	%xmm1, %xmm0
	addsd	%xmm0, %xmm2
	jmp	.L4
.L6:
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	movapd	%xmm2, %xmm0
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE19:
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
	.globl	main
	.type	main, @function
main:
.LFB20:
	.cfi_startproc
	subq	$72, %rsp
	.cfi_def_cfa_offset 80
	movl	$.LC4, %edi
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	puts
	leaq	16(%rsp), %rsi
	movl	$.LC5, %edi
	xorl	%eax, %eax
	movq	$0, 16(%rsp)
	call	scanf
	leaq	24(%rsp), %rsi
	movl	$4, %edi
	call	clock_gettime
	movsd	16(%rsp), %xmm0
	call	_Z9pi_numberd
	leaq	40(%rsp), %rsi
	movl	$4, %edi
	movsd	%xmm0, 8(%rsp)
	call	clock_gettime
	movsd	8(%rsp), %xmm0
	movl	$.LC6, %esi
	movl	$1, %edi
	movb	$1, %al
	call	__printf_chk
	movq	48(%rsp), %rax
	subq	32(%rsp), %rax
	movl	$.LC8, %esi
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movb	$1, %al
	mulsd	.LC7(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk
	movq	56(%rsp), %rdx
	xorq	%fs:40, %rdx
	je	.L10
	call	__stack_chk_fail
.L10:
	xorl	%eax, %eax
	addq	$72, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE20:
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
