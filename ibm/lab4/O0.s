	// pc - programm counter - адрес выполняемой в данный момент команды
	// lr - link register - адрес вызывающей функции (адрес возврата)
	// sp - stack pointer - адрес текущего значения стека

	.arch armv7-a
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
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
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r7, lr} // сохраняем в стеке регистры вызывающей функции
	sub	sp, sp, #28 // выделяем память
	add	r7, sp, #0 // r7 = sp - наш указатель на стек
	vstr.64	d0, [r7] // загружаем n (на стеке сопроцессора уже было n)
	movs	r3, #0
	str	r3, [r7, #12] // int i = 0
	mov	r3, #0
	mov	r4, #0
	strd	r3, [r7, #16] // double result = 0.0
	movs	r3, #0
	str	r3, [r7, #12] // i = 0
	b	.L2 // branch на цикл
.L3:
	ldr	r3, [r7, #12] // загрузили интовое i из памяти
	vmov	s15, r3	@ int // загрузили вещественное i для работы с другими вещественными числами
	vcvt.f64.s32	d7, s15
	// загружаем параметры для pow
	vmov.f64	d1, d7 // переменная i в регистр d1 сопроцессора
	vmov.f64	d0, #-1.0e+0 // -1 в d0 регистр сопроцессора
	bl	pow // pow(-1, i)
	// результат теперь в d0
	vmov.f64	d6, d0 // d6 = результат выполнения pow
	vmov.f64	d7, #4.0e+0 // записываем константу 4 в d7
	vmul.f64	d5, d6, d7 // 4*pow()
	ldr	r3, [r7, #12] // загружаем i
	lsls	r3, r3, #1 // умножение на 2 (logical shift left << 1 bit) (2i)
	adds	r3, r3, #1 // +1 (2i+1)
	vmov	s15, r3	@ int // загружаем флоат i
	vcvt.f64.s32	d6, s15 // конверт
	vdiv.f64	d7, d5, d6 // 4 * pow(-1, i) / (2 * i + 1)
	vldr.64	d6, [r7, #16] // загружаем прошлый result
	vadd.f64	d7, d6, d7 // result += 4*...
	vstr.64	d7, [r7, #16] // выталкиваем result в память
	ldr	r3, [r7, #12] // загружаем i
	adds	r3, r3, #1 // i++
	str	r3, [r7, #12] // обновляем i
.L2:
	ldr	r3, [r7, #12] // в r3 грузим i
	vmov	s15, r3	@ int // в регистр сопроцессора грузим вещественное i 
	vcvt.f64.s32	d6, s15 // конверт из 32-битного fixed-point в 64-битный float-point -- это i
	vldr.64	d7, [r7] // тут у нас лежит n
	vcmpe.f64	d6, d7 // i <= n
	vmrs	APSR_nzcv, FPSCR // переносит флаги из сопроцессора в регистры процессора
	bls	.L3 // проверяем условие ---> следующая итерация
	ldrd	r3, [r7, #16] // вытаскиваем окончательный result
	vmov	d7, r3, r4 // r3 - в младшие разряды, r4 - в старшие
	vmov.f64	d0, d7 // помещаем окончательный результат на стек сопроцессора
	adds	r7, r7, #28 // возвращаем стек в исходное состояние
	mov	sp, r7
	@ sp needed
	pop	{r4, r7, pc}
	.size	pi_number, .-pi_number
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Put int the n parameter :\000"
	.align	2
.LC1:
	.ascii	"%lf\000"
	.align	2
.LC2:
	.ascii	"Result : %f\012\000"
	.align	2
.LC3:
	.ascii	"Time : %lf sec\012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r7, lr}
	sub	sp, sp, #44
	add	r7, sp, #0
	movw	r3, #:lower16:__stack_chk_guard
	movt	r3, #:upper16:__stack_chk_guard
	ldr	r3, [r3]
	str	r3, [r7, #36]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	puts
	mov	r3, #0
	mov	r4, #0
	strd	r3, [r7]
	mov	r3, r7
	mov	r1, r3
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	__isoc99_scanf
	add	r3, r7, #20
	mov	r1, r3
	movs	r0, #4
	bl	clock_gettime
	vldr.64	d7, [r7]
	vmov.f64	d0, d7
	bl	pi_number
	vstr.64	d0, [r7, #8]
	add	r3, r7, #28
	mov	r1, r3
	movs	r0, #4
	bl	clock_gettime
	ldrd	r2, [r7, #8]
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	printf
	ldr	r2, [r7, #28]
	ldr	r3, [r7, #20]
	subs	r3, r2, r3
	vmov	s15, r3	@ int
	vcvt.f64.s32	d6, s15
	ldr	r2, [r7, #32]
	ldr	r3, [r7, #24]
	subs	r3, r2, r3
	vmov	s15, r3	@ int
	vcvt.f64.s32	d7, s15
	vldr.64	d5, .L8
	vmul.f64	d7, d7, d5
	vadd.f64	d7, d6, d7
	vmov	r2, r3, d7
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	printf
	movs	r3, #0
	mov	r0, r3
	movw	r3, #:lower16:__stack_chk_guard
	movt	r3, #:upper16:__stack_chk_guard
	ldr	r2, [r7, #36]
	ldr	r3, [r3]
	cmp	r2, r3
	beq	.L7
	bl	__stack_chk_fail
.L7:
	adds	r7, r7, #44
	mov	sp, r7
	@ sp needed
	pop	{r4, r7, pc}
.L9:
	.align	3
.L8:
	.word	3894859413
	.word	1041313291
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits
