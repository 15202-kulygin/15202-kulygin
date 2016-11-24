	.file	"lab3.c"
	.text
	.globl	_Z9pi_numberd
	.type	_Z9pi_numberd, @function
_Z9pi_numberd:  // функция pi_number
.LFB0:
	.cfi_startproc
	pushl	%ebp // сохраняем указатель кадра стека из main
	.cfi_def_cfa_offset 8 // память, выделенная под адрес возврата вызывающей функции
	.cfi_offset 5, -8
	movl	%esp, %ebp // создаем новый указатель кадра стека для нашей функции
	.cfi_def_cfa_register 5
	subl	$40, %esp // выделяем память в кадре стека под переменные
	movl	8(%ebp), %eax // вытаскиваем из кадра мэйна n
	movl	%eax, -32(%ebp) //  записываем n в наш кадр 
	movl	12(%ebp), %eax // 
	movl	%eax, -28(%ebp)
	movl	$0, -20(%ebp) // int i = 0
	fldz  // (load zero) загружаем вещественное +0 в стек сопроцессора -- result = 0
	fstpl	-16(%ebp) // засовываем result в кадр
	movl	$0, -20(%ebp) // i = 0
.L4:
	fildl	-20(%ebp) //загрузить целое число i в стек сопроцессора
	fldl	-32(%ebp) // загружаем вещественное n из нашего кадра в стек сопроцессора
	// (предварительно n вытащили из кадра main, строки 14-15)
	fucomip	%st(1), %st // неупорядоченное вещественное сравнение с установкой флага и выталкиванием (i <= n)
	fstp	%st(0) // записать и вытолкнуть вещественное число в наш кадр (в память)
	jb	.L7 // jump below -- проверка условий цикла и переход на конец функции
	fildl	-20(%ebp) // загрузить целое число i в стек сопроцессора
	leal	-8(%esp), %esp 
	fstpl	(%esp)
	fld1 // (load 1) загружаем +1.0 в стек сопроцессора
	fchs // меняем +1 на -1
	leal	-8(%esp), %esp 
	fstpl	(%esp) // модифицируем стек перед вызовом pow
	call	pow // вызываем функцию pow(-1, i)
	addl	$16, %esp // возвращаем стек в исходное состояние после вызова функции
	fldl	.LC2 // загрузили 4 в стек сопроцессора
	fmulp	%st, %st(1) // умножение с выталкиванием в память
	movl	-20(%ebp), %eax // загружаем i в регистр
	addl	%eax, %eax // (2 * i)
	addl	$1, %eax // (2 * i + 1)
	movl	%eax, -36(%ebp) // загружаем 2i+1 в кадр
	fildl	-36(%ebp) // загружаем 2i+1 в стек сопроцессора
	fdivrp	%st, %st(1) // 4*pow(-1, i) / (2 * i + 1)
	fldl	-16(%ebp) // загружаем result из кадра в стек
	faddp	%st, %st(1) // result += 4*pow(-1,i)/(2*i+1) сложение с выталкиванием в память
	fstpl	-16(%ebp) // выталкиваем конечный(новый) result в наш кадр
	addl	$1, -20(%ebp) // ++i
	jmp	.L4 // следующая итерация
.L7:
	fldl	-16(%ebp) // загружаем конечный результат в стек сопроцессора
	leave // movl %ebp, %esp ; popl %ebp 
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret // выход из функции pi_number
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
	movl	%esp, %ebp // формируем указатель кадра
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$68, %esp // выделяем память под кадр
	movl	%gs:20, %eax // для проверки переполнения стека (инициализация спец значением)
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax // еах = 0
	subl	$12, %esp
	pushl	$.LC4
	call	puts // printf("Put int the n parameter :\n");
	addl	$16, %esp 
	fldz // double n = 0
	fstpl	-48(%ebp) // загружаем n в кадр
	subl	$8, %esp 
	leal	-48(%ebp), %eax
	pushl	%eax // n на вершину стека для scanf
	pushl	$.LC5
	call	scanf // scanf("%lf", &n);
	addl	$16, %esp
	subl	$8, %esp
	leal	-28(%ebp), %eax // это адрес start
	pushl	%eax // загружаем параметр &start
	pushl	$4 // загружаем параметр 4 (CLOCK_MONOTONIC_RAW)
	call	clock_gettime // clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	addl	$16, %esp
	fldl	-48(%ebp)
	subl	$8, %esp
	leal	-8(%esp), %esp
	fstpl	(%esp) // 
	call	_Z9pi_numberd // double result = pi_number(n);
	addl	$16, %esp
	fstpl	-40(%ebp) // пишем result в память
	subl	$8, %esp
	leal	-20(%ebp), %eax // загружаем параметры для второго clock_gettime (это адрес end)
	pushl	%eax
	pushl	$4 
	call	clock_gettime // clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	addl	$16, %esp
	subl	$4, %esp
	pushl	-36(%ebp)
	// загрузка параметров для printf("Result : %f\n", result);
	pushl	-40(%ebp) // загружаем result
	pushl	$.LC6 //загружаем строку
	call	printf // printf("Result : %f\n", result);
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
	call	printf // printf("Time : %lf sec\n", end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
	addl	$16, %esp
	movl	$0, %eax
	movl	-12(%ebp), %ecx
	xorl	%gs:20, %ecx // проверка переполнения
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
