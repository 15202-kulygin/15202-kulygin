	.file	"lab3.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB42:
	.cfi_startproc
	pxor	%xmm2, %xmm2
	comisd	%xmm0, %xmm2
	ja	.L6
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%ebx, %ebx
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movsd	%xmm0, 8(%rsp)
	movsd	.LC0(%rip), %xmm0
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L8:
	movsd	.LC3(%rip), %xmm0
	movsd	%xmm2, (%rsp)
	call	__pow_finite
	movsd	(%rsp), %xmm2
.L3:
	pxor	%xmm1, %xmm1
	leal	1(%rbx,%rbx), %eax
	addl	$1, %ebx
	mulsd	.LC2(%rip), %xmm0
	cvtsi2sd	%eax, %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sd	%ebx, %xmm1
	addsd	%xmm0, %xmm2
	comisd	8(%rsp), %xmm1
	jbe	.L8
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	movapd	%xmm2, %xmm0
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
.L6:
	movapd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE42:
	.size	_Z9pi_numberd, .-_Z9pi_numberd
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC5:
	.string	"Put int the n parameter :"
.LC6:
	.string	"%lf"
.LC7:
	.string	"Result : %f\n"
.LC9:
	.string	"Time : %lf sec\n"
	.section	.text.unlikely
.LCOLDB10:
	.section	.text.startup,"ax",@progbits
.LHOTB10:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB43:
	.cfi_startproc
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movl	$.LC5, %edi
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	call	puts
	leaq	24(%rsp), %rsi
	movl	$.LC6, %edi
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
	movl	$.LC7, %esi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk
	movq	56(%rsp), %rax
	subq	40(%rsp), %rax
	movl	$.LC9, %esi
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	48(%rsp), %rax
	subq	32(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	mulsd	.LC8(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk
	movq	72(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L12
	xorl	%eax, %eax
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L12:
	.cfi_restore_state
	call	__stack_chk_fail
	.cfi_endproc
.LFE43:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE10:
	.section	.text.startup
.LHOTE10:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 8
.LC2:
	.long	0
	.long	1074790400
	.align 8
.LC3:
	.long	0
	.long	-1074790400
	.align 8
.LC8:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
