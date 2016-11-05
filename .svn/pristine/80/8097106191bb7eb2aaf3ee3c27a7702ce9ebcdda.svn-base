	.file	"lab3.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:
.LFB52:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$36, %esp
	.cfi_def_cfa_offset 48
	fldl	48(%esp)
	fstl	24(%esp)
	fldz
	fld	%st(0)
	fxch	%st(2)
	fucomip	%st(2), %st
	jb	.L8
	movl	$1, %esi
	xorl	%ebx, %ebx
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L11:
	fxch	%st(1)
.L4:
	fstpl	16(%esp)
	subl	$8, %esp
	.cfi_def_cfa_offset 56
	addl	$1, %ebx
	fstpl	(%esp)
	pushl	$-1074790400
	.cfi_def_cfa_offset 60
	pushl	$0
	.cfi_def_cfa_offset 64
	call	pow
	fmuls	.LC2
	movl	%esi, 28(%esp)
	addl	$2, %esi
	fildl	28(%esp)
	movl	%ebx, 28(%esp)
	fdivrp	%st, %st(1)
	fldl	32(%esp)
	faddp	%st, %st(1)
	fildl	28(%esp)
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	fldl	24(%esp)
	fucomip	%st(1), %st
	jnb	.L11
	fstp	%st(0)
.L2:
	addl	$36, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
.L8:
	.cfi_restore_state
	fstp	%st(1)
	jmp	.L2
	.cfi_endproc
.LFE52:
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
.LFB53:
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
	movl	%eax, -48(%ebp)
	movl	-20(%ebp), %eax
	fildl	-48(%ebp)
	subl	-28(%ebp), %eax
	fmull	.LC8
	movl	%eax, -48(%ebp)
	fildl	-48(%ebp)
	faddp	%st, %st(1)
	fstpl	(%esp)
	pushl	$.LC9
	pushl	$1
	call	__printf_chk
	addl	$16, %esp
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	jne	.L15
	movl	-4(%ebp), %ecx
	.cfi_remember_state
	.cfi_def_cfa 1, 0
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
.L15:
	.cfi_restore_state
	call	__stack_chk_fail
	.cfi_endproc
.LFE53:
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
