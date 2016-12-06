	.arch armv7-a
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 1
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"lab4.c"
	.text
	.align	2
	.global	pi_number
	.syntax unified
	.thumb
	.thumb_func
	.type	pi_number, %function
pi_number:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	vpush.64	{d8, d9, d10, d11}
	vcmpe.f64	d0, #0
	vmrs	APSR_nzcv, FPSCR
	blt	.L8
	vmov.f64	d9, d0
	movs	r5, #1
	vldr.64	d1, .L10
	vmov.f64	d8, d1
	movs	r4, #0
	vmov.f64	d11, #-1.0e+0
	vmov.f64	d10, #4.0e+0
.L4:
	vmov.f64	d0, d11
	bl	pow
	vmul.f64	d0, d0, d10
	vmov	s15, r5		@ int
	vcvt.f64.s32d6, s15
	vdiv.f64	d7, d0, d6
	vadd.f64	d8, d8, d7
	adds	r4, r4, #1
	vmov	s15, r4	@ int
	vcvt.f64.s32	d1, s15
	adds	r5, r5, #2
	vcmpe.f64	d1, d9
	vmrs	APSR_nzcv, FPSCR
	bls	.L4
	b	.L2
.L8:
	vldr.64	d8, .L10
.L2:
	vmov.f64	d0, d8
	vldm	sp!, {d8-d11}
	pop	{r3, r4, r5, pc}
.L11:
	.align	3
.L10:
	.word	0
	.word	0
	.size	pi_number, .-pi_number
	.align	2
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r6, r7, lr}
	sub	sp, sp, #32
	movw	r4, #:lower16:__stack_chk_guard
	movt	r4, #:upper16:__stack_chk_guard
	ldr	r3, [r4]
	str	r3, [sp, #28]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	puts
	add	r1, sp, #32
	movs	r2, #0
	movs	r3, #0
	strd	r2, [r1, #-32]!
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	__isoc99_scanf
	add	r1, sp, #12
	movs	r0, #4
	bl	clock_gettime
	vldr.64	d0, [sp]
	bl	pi_number
	vmov	r6, r7, d0
	add	r1, sp, #20
	movs	r0, #4
	bl	clock_gettime
	mov	r2, r6
	mov	r3, r7
	movw	r1, #:lower16:.LC2
	movt	r1, #:upper16:.LC2
	movs	r0, #1
	bl	__printf_chk
	ldr	r2, [sp, #16]
	ldr	r3, [sp, #24]
	subs	r3, r3, r2
	vmov	s15, r3	@ int
	vcvt.f64.s32	d6, s15
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #20]
	subs	r3, r3, r2
	vmov	s15, r3	@ int
	vcvt.f64.s32	d7, s15
	vldr.64	d5, .L15
	vmla.f64	d7, d6, d5
	vmov	r2, r3, d7
	movw	r1, #:lower16:.LC3
	movt	r1, #:upper16:.LC3
	movs	r0, #1
	bl	__printf_chk
	ldr	r2, [sp, #28]
	ldr	r3, [r4]
	cmp	r2, r3
	beq	.L13
	bl	__stack_chk_fail
.L13:
	movs	r0, #0
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r6, r7, pc}
.L16:
	.align	3
.L15:
	.word	3894859413
	.word	1041313291
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Put int the n parameter :\000"
	.space	2
.LC1:
	.ascii	"%lf\000"
.LC2:
	.ascii	"Result : %f\012\000"
	.space	3
.LC3:
	.ascii	"Time : %lf sec\012\000"
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits







	Оптимизировано :
	1. не сразу проверка на 0 -> сначала потрогал стек -> выход
	остальное - как в O2 и O3







