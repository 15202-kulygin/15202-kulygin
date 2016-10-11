	.file	"lab3.c"
	.text
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	$0, -20(%ebp)
	fldz
	fstpl	-16(%ebp)
	movl	$0, -20(%ebp)
.L4:
	fildl	-20(%ebp)
	fldl	-32(%ebp)
	fucomip	%st(1), %st
	fstp	%st(0)
	jb	.L7
	fildl	-20(%ebp)
	leal	-8(%esp), %esp
	fstpl	(%esp)
	fld1
	fchs
	leal	-8(%esp), %esp
	fstpl	(%esp)
	call	pow
	addl	$16, %esp
	fldl	.LC2
	fmulp	%st, %st(1)
	movl	-20(%ebp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	movl	%eax, -36(%ebp)
	fildl	-36(%ebp)
	fdivrp	%st, %st(1)
	fldl	-16(%ebp)
	faddp	%st, %st(1)
	fstpl	-16(%ebp)
	addl	$1, -20(%ebp)
	jmp	.L4
.L7:
	fldl	-16(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z9pi_numberd, .-_Z9pi_numberd
	.section	.rodata
.LC4:
	.string	"Put int the n parameter :"
.LC5:
	.string	"%lf"
.LC6:
	.string	"Result : %f\n"
.LC8:
	.string	"Time : %lf sec\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$68, %esp
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$12, %esp
	pushl	$.LC4
	call	puts
	addl	$16, %esp
	fldz
	fstpl	-48(%ebp)
	subl	$8, %esp
	leal	-48(%ebp), %eax
	pushl	%eax
	pushl	$.LC5
	call	scanf
	addl	$16, %esp
	subl	$8, %esp
	leal	-28(%ebp), %eax
	pushl	%eax
	pushl	$4
	call	clock_gettime
	addl	$16, %esp
	fldl	-48(%ebp)
	subl	$8, %esp
	leal	-8(%esp), %esp
	fstpl	(%esp)
	call	_Z9pi_numberd
	addl	$16, %esp
	fstpl	-40(%ebp)
	subl	$8, %esp
	leal	-20(%ebp), %eax
	pushl	%eax
	pushl	$4
	call	clock_gettime
	addl	$16, %esp
	subl	$4, %esp
	pushl	-36(%ebp)
	pushl	-40(%ebp)
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	movl	-20(%ebp), %edx
	movl	-28(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -60(%ebp)
	fildl	-60(%ebp)
	movl	-16(%ebp), %edx
	movl	-24(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -60(%ebp)
	fildl	-60(%ebp)
	fldl	.LC7
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	subl	$4, %esp
	leal	-8(%esp), %esp
	fstpl	(%esp)
	pushl	$.LC8
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-12(%ebp), %ecx
	xorl	%gs:20, %ecx
	je	.L10
	call	__stack_chk_fail
.L10:
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
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
