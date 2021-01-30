	.file	"main.c"
	.text
	.globl	func1
	.def	func1;	.scl	2;	.type	32;	.endef
	.seh_proc	func1
func1:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	16(%rbp), %eax
	cmpl	24(%rbp), %eax
	jle	.L2
	movl	16(%rbp), %eax
	subl	24(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	jmp	.L3
.L2:
	movl	$1, -4(%rbp)
	movl	24(%rbp), %eax
	subl	16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
.L3:
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	func2
	.def	func2;	.scl	2;	.type	32;	.endef
	.seh_proc	func2
func2:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	24(%rbp), %eax
	cmpl	32(%rbp), %eax
	jle	.L5
	movl	24(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
	jmp	.L6
.L5:
	movl	32(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
.L6:
	movq	16(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	-16(%rbp), %eax
	movl	%eax, 16(%rcx)
	movq	16(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	func3
	.def	func3;	.scl	2;	.type	32;	.endef
	.seh_proc	func3
func3:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	24(%rbp), %eax
	cmpl	32(%rbp), %eax
	jge	.L9
	movl	24(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
	jmp	.L10
.L9:
	movl	32(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
.L10:
	movq	16(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	-16(%rbp), %eax
	movl	%eax, 16(%rcx)
	movq	16(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "%d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	call	__main
	movl	$0, -4(%rbp)
	movl	$2, %edx
	movl	$1, %ecx
	call	func1
	movl	%eax, -4(%rbp)
	leaq	-32(%rbp), %rax
	movl	$3, %r8d
	movl	$2, %edx
	movq	%rax, %rcx
	call	func2
	leaq	-64(%rbp), %rax
	movl	$3, %r8d
	movl	$2, %edx
	movq	%rax, %rcx
	call	func3
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	-32(%rbp), %edx
	movl	-64(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	$0, %eax
	addq	$96, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 10.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
