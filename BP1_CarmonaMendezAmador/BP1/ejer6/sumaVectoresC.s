	.file	"sumaVectoresC.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\303\202\302\272 componentes del vector"
	.align 8
.LC1:
	.string	"No hay suficiente espacio para los vectores "
	.align 8
.LC3:
	.string	"/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC4:
	.string	"Tiempo:%11.9f\t / Tama\303\203\302\261o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC6:
	.string	"Tiempo:%11.9f\t / Tama\303\203\302\261o Vectores:%u\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L28
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movl	%eax, %r13d
	movq	%rax, %rbx
	movl	%eax, %r14d
	salq	$3, %r13
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%r13, %rdi
	movq	%rax, %rbp
	call	malloc@PLT
	movq	%r13, %rdi
	movq	%rax, %r12
	call	malloc@PLT
	testq	%rbp, %rbp
	movq	%rax, %r13
	je	.L18
	testq	%r12, %r12
	je	.L18
	cmpl	$8, %ebx
	ja	.L5
	testl	%ebx, %ebx
	je	.L6
	pxor	%xmm1, %xmm1
	xorl	%eax, %eax
	movsd	.LC2(%rip), %xmm3
	cvtsi2sd	%ebx, %xmm1
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L7:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	movapd	%xmm1, %xmm7
	cvtsi2sd	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	subsd	%xmm0, %xmm7
	movsd	%xmm2, 0(%rbp,%rax,8)
	movsd	%xmm7, (%r12,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %r14d
	ja	.L7
	leal	-1(%rbx), %eax
	movl	%eax, 4(%rsp)
.L8:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movl	4(%rsp), %eax
	leaq	8(,%rax,8), %rdx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L10:
	movsd	0(%rbp,%rax), %xmm0
	addsd	(%r12,%rax), %xmm0
	movsd	%xmm0, 0(%r13,%rax)
	addq	$8, %rax
	cmpq	%rax, %rdx
	jne	.L10
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	cmpl	$9, %ebx
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	jbe	.L15
	movl	4(%rsp), %eax
	movsd	0(%r13), %xmm3
	movsd	(%r12), %xmm2
	leaq	.LC4(%rip), %rsi
	movsd	0(%rbp), %xmm1
	movl	%ebx, %edx
	movl	$1, %edi
	movsd	0(%r13,%rax,8), %xmm6
	movq	%rax, %rcx
	movl	%eax, %r9d
	movsd	(%r12,%rax,8), %xmm5
	movl	%eax, %r8d
	movsd	0(%rbp,%rax,8), %xmm4
	movl	$7, %eax
	call	__printf_chk@PLT
.L12:
	movq	%rbp, %rdi
	call	free@PLT
	movq	%r12, %rdi
	call	free@PLT
	movq	%r13, %rdi
	call	free@PLT
	xorl	%eax, %eax
	movq	56(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L29
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	leaq	.LC6(%rip), %rsi
	movl	%ebx, %edx
	movl	$1, %edi
	movl	$1, %eax
	leaq	.LC3(%rip), %r15
	xorl	%ebx, %ebx
	call	__printf_chk@PLT
	movl	4(%rsp), %r14d
	addq	$1, %r14
	.p2align 4,,10
	.p2align 3
.L13:
	movsd	0(%r13,%rbx,8), %xmm2
	movl	%ebx, %r8d
	movl	%ebx, %ecx
	movsd	(%r12,%rbx,8), %xmm1
	movl	%ebx, %edx
	movsd	0(%rbp,%rbx,8), %xmm0
	movq	%r15, %rsi
	movl	$1, %edi
	movl	$3, %eax
	addq	$1, %rbx
	call	__printf_chk@PLT
	cmpq	%r14, %rbx
	jne	.L13
	jmp	.L12
.L5:
	xorl	%edi, %edi
	xorl	%r15d, %r15d
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	leal	-1(%rbx), %eax
	movl	%eax, 4(%rsp)
	leaq	8(,%rax,8), %rax
	movq	%rax, 8(%rsp)
	.p2align 4,,10
	.p2align 3
.L9:
	call	rand@PLT
	movl	%eax, %r14d
	call	rand@PLT
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sd	%r14d, %xmm0
	cvtsi2sd	%eax, %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, 0(%rbp,%r15)
	call	rand@PLT
	movl	%eax, %r14d
	call	rand@PLT
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sd	%r14d, %xmm0
	cvtsi2sd	%eax, %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, (%r12,%r15)
	addq	$8, %r15
	cmpq	%r15, 8(%rsp)
	jne	.L9
	jmp	.L8
.L6:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	leaq	.LC6(%rip), %rsi
	pxor	%xmm0, %xmm0
	xorl	%edx, %edx
	pxor	%xmm1, %xmm1
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	jmp	.L12
.L29:
	call	__stack_chk_fail@PLT
.L18:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movl	$-2, %edi
	call	exit@PLT
.L28:
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	orl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	2576980378
	.long	1069128089
	.align 8
.LC5:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
