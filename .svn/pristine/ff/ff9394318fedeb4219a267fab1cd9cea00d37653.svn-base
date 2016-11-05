	.file	"lab3.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB96:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$20, %esp
	.cfi_def_cfa_offset 32
	fldl	32(%esp)
	fstl	8(%esp)
	fldz
	fld	%st(0)
	fcomip	%st(2), %st
	fstp	%st(1)
	ja	.L4
	fld1
	movl	$1, %esi
	xorl	%ebx, %ebx
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L7:
	fxch	%st(1)
	fstpl	(%esp)
	subl	$8, %esp
	.cfi_def_cfa_offset 40
	fstpl	(%esp)
	pushl	$-1074790400
	.cfi_def_cfa_offset 44
	pushl	$0
	.cfi_def_cfa_offset 48
	call	__pow_finite
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	fldl	(%esp)
	fxch	%st(1)
.L3:
	fmull	.LC4
	movl	%esi, (%esp)
	addl	$1, %ebx
	addl	$2, %esi
	fildl	(%esp)
	movl	%ebx, (%esp)
	fdivrp	%st, %st(1)
	faddp	%st, %st(1)
	fildl	(%esp)
	fldl	8(%esp)
	fxch	%st(1)
	fcomi	%st(1), %st
	fstp	%st(1)
	jbe	.L7
	fstp	%st(0)
.L2:
	addl	$20, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
.L4:
	.cfi_restore_state
	jmp	.L2
	.cfi_endproc
.LFE96:
	.size	_Z9pi_numberd, .-_Z9pi_numberd
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC7:
	.string	"Put int the n parameter :"
.LC8:
	.string	"%lf"
.LC9:
	.string	"Result : %f\n"
.LC11:
	.string	"Time : %lf sec\n"
	.section	.text.unlikely
.LCOLDB12:
	.section	.text.startup,"ax",@progbits
.LHOTB12:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB97:
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
	pushl	$.LC7
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	call	puts
	popl	%eax
	leal	-40(%ebp), %eax
	fldz
	popl	%edx
	pushl	%eax
	pushl	$.LC8
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
	pushl	$.LC9
	pushl	$1
	call	__printf_chk
	popl	%ecx
	popl	%eax
	movl	-16(%ebp), %eax
	subl	-24(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	-20(%ebp), %eax
	fildl	-48(%ebp)
	subl	-28(%ebp), %eax
	fmull	.LC10
	movl	%eax, -48(%ebp)
	fildl	-48(%ebp)
	faddp	%st, %st(1)
	fstpl	(%esp)
	pushl	$.LC11
	pushl	$1
	call	__printf_chk
	addl	$16, %esp
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	jne	.L11
	movl	-4(%ebp), %ecx
	.cfi_remember_state
	.cfi_def_cfa 1, 0
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
.L11:
	.cfi_restore_state
	call	__stack_chk_fail
	.cfi_endproc
.LFE97:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE12:
	.section	.text.startup
.LHOTE12:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC4:
	.long	0
	.long	1074790400
	.align 8
.LC10:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
