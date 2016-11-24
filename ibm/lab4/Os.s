	.arch armv7-a
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 4
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"lab4.c"
	.text
	.align	1
	.global	pi_number
	.syntax unified
	.thumb
	.thumb_func
	.type	pi_number, %function
pi_number:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	movs	r4, #0
	vpush.64	{d8, d9, d10}
	vmov.f64	d10, #4.0e+0
	vldr.64	d8, .L6
	vmov.f64	d9, d0
.L2:
	vmov	s15, r4	@ int
	vcvt.f64.s32	d1, s15
	vcmpe.f64	d1, d9
	vmrs	APSR_nzcv, FPSCR
	bhi	.L5
	vmov.f64	d0, #-1.0e+0
	bl	pow
	lsls	r3, r4, #1
	adds	r3, r3, #1
	adds	r4, r4, #1
	vmov	s15, r3	@ int
	vcvt.f64.s32	d7, s15
	vmul.f64	d0, d0, d10
	vdiv.f64	d6, d0, d7
	vadd.f64	d8, d8, d6
	b	.L2
.L5:
	vmov.f64	d0, d8
	vldm	sp!, {d8-d10}
	pop	{r4, pc}
.L7:
	.align	3
.L6:
	.word	0
	.word	0
	.size	pi_number, .-pi_number
	.section	.text.startup,"ax",%progbits
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	sub	sp, sp, #40
	ldr	r4, .L10+8
	ldr	r0, .L10+12
	ldr	r3, [r4]
	str	r3, [sp, #36]
	bl	puts
	add	r1, sp, #40
	movs	r2, #0
	movs	r3, #0
	ldr	r0, .L10+16
	strd	r2, [r1, #-32]!
	bl	__isoc99_scanf
	add	r1, sp, #20
	movs	r0, #4
	bl	clock_gettime
	vldr.64	d0, [sp, #8]
	bl	pi_number
	add	r1, sp, #28
	movs	r0, #4
	vmov	r2, r3, d0
	strd	r2, [sp]
	bl	clock_gettime
	ldrd	r2, [sp]
	movs	r0, #1
	ldr	r1, .L10+20
	bl	__printf_chk
	ldr	r2, [sp, #24]
	ldr	r3, [sp, #32]
	movs	r0, #1
	vldr.64	d5, .L10
	subs	r3, r3, r2
	ldr	r2, [sp, #20]
	ldr	r1, .L10+24
	vmov	s15, r3	@ int
	ldr	r3, [sp, #28]
	subs	r3, r3, r2
	vcvt.f64.s32	d6, s15
	vmov	s15, r3	@ int
	vcvt.f64.s32	d7, s15
	vmla.f64	d7, d6, d5
	vmov	r2, r3, d7
	bl	__printf_chk
	ldr	r2, [sp, #36]
	ldr	r3, [r4]
	movs	r0, #0
	cmp	r2, r3
	beq	.L9
	bl	__stack_chk_fail
.L9:
	add	sp, sp, #40
	@ sp needed
	pop	{r4, pc}
.L11:
	.align	3
.L10:
	.word	3894859413
	.word	1041313291
	.word	__stack_chk_guard
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.size	main, .-main
	.section	.rodata.str1.1,"aMS",%progbits,1
.LC0:
	.ascii	"Put int the n parameter :\000"
.LC1:
	.ascii	"%lf\000"
.LC2:
	.ascii	"Result : %f\012\000"
.LC3:
	.ascii	"Time : %lf sec\012\000"
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits




Оптимизировано:
1. самый маленький размер
2. нет проверки на 0 параметра функции
3. использует меньше регистров
4. не вынес все константы
5. не обращается в память
6. каждый раз считает сложное выражение, вместо того, чтобы прибавить константу