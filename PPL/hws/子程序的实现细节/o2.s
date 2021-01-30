	.file	"main.c"
	.text
	.p2align 4
	.globl	func1
	.def	func1;	.scl	2;	.type	32;	.endef
	.seh_proc	func1
func1:
	.seh_endprologue
	movl	%ecx, %r8d
	movl	%edx, %eax
	subl	%edx, %r8d
	subl	%ecx, %eax
	cmpl	%edx, %ecx
	cmovg	%r8d, %eax
	ret
	.seh_endproc
	.p2align 4
	.globl	func2
	.def	func2;	.scl	2;	.type	32;	.endef
	.seh_proc	func2
func2:
	.seh_endprologue
	cmpl	%r8d, %edx
	movq	%rcx, %rax
	cmovl	%r8d, %edx
	movl	%edx, (%rcx)
	movl	%edx, 4(%rcx)
	movl	%edx, 8(%rcx)
	movl	%edx, 12(%rcx)
	movl	%edx, 16(%rcx)
	ret
	.seh_endproc
	.p2align 4
	.globl	func3
	.def	func3;	.scl	2;	.type	32;	.endef
	.seh_proc	func3
func3:
	.seh_endprologue
	cmpl	%r8d, %edx
	movq	%rcx, %rax
	cmovg	%r8d, %edx
	movl	%edx, (%rcx)
	movl	%edx, 4(%rcx)
	movl	%edx, 8(%rcx)
	movl	%edx, 12(%rcx)
	movl	%edx, 16(%rcx)
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "%d\12\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	movl	$1, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	$5, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	xorl	%eax, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 10.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
