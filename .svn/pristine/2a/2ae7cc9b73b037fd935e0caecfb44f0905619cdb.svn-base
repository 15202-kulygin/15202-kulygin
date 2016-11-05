	.file	"lab3.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB4:
	.text
.LHOTB4:
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB19:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	.cfi_offset 3, -12
	xorl	%ebx, %ebx
	subl	$36, %esp
	fldl	8(%ebp)
	fldz
.L4:
	movl	%ebx, -12(%ebp)
	fildl	-12(%ebp)
	fxch	%st(2)
	fucomi	%st(2), %st
	fstpl	-32(%ebp)
	jb	.L6
	fstpl	-24(%ebp)
	pushl	%eax
	pushl	%eax
	fstpl	(%esp)
	pushl	$-1074790400
	pushl	$0
	call	pow
	fmuls	.LC2
	leal	1(%ebx,%ebx), %eax
	addl	$16, %esp
	incl	%ebx
	movl	%eax, -12(%ebp)
	fidivl	-12(%ebp)
	fldl	-24(%ebp)
	faddp	%st, %st(1)
	fldl	-32(%ebp)
	fxch	%st(1)
	jmp	.L4
.L6:
	fstp	%st(1)
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE19:
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
	.globl	main
	.type	main, @function
main:
.LFB20:
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
	subl	$64, %esp
	pushl	$.LC5
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	call	puts
	popl	%eax
	leal	-40(%ebp), %eax
	fldz
	popl	%edx
	pushl	%eax
	pushl	$.LC6
	fstpl	-40(%ebp)
	call	scanf
	popl	%ecx
	popl	%eax
	leal	-28(%ebp), %eax
	pushl	%eax
	pushl	$4
	call	clock_gettime
	popl	%eax
	popl	%edx
	pushl	-36(%ebp)
	pushl	-40(%ebp)
	call	_Z9pi_numberd
	popl	%ecx
	popl	%eax
	leal	-20(%ebp), %eax
	fstpl	-48(%ebp)
	pushl	%eax
	pushl	$4
	call	clock_gettime
	popl	%eax
	popl	%edx
	fldl	-48(%ebp)
	fstpl	(%esp)
	pushl	$.LC7
	pushl	$1
	call	__printf_chk
	popl	%ecx
	popl	%eax
	movl	-16(%ebp), %eax
	subl	-24(%ebp), %eax
	fldl	.LC8
	movl	%eax, -48(%ebp)
	movl	-20(%ebp), %eax
	fimull	-48(%ebp)
	subl	-28(%ebp), %eax
	movl	%eax, -48(%ebp)
	fiaddl	-48(%ebp)
	fstpl	(%esp)
	pushl	$.LC9
	pushl	$1
	call	__printf_chk
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L10
	call	__stack_chk_fail
.L10:
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE20:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE10:
	.section	.text.startup
.LHOTE10:
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC2:
	.long	1082130432
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC8:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
