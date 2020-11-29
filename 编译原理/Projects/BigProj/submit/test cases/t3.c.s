	.text
	.file	"t3.c"
	.globl	go                      # -- Begin function go
	.p2align	4, 0x90
	.type	go,@function
go:                                     # @go
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movl	%edi, 12(%rsp)
	cmpl	$1, %edi
	je	.LBB0_1
# %bb.3:                                # %else
	cmpl	$2, 12(%rsp)
	jne	.LBB0_4
.LBB0_1:                                # %then
	movl	$1, %eax
	jmp	.LBB0_2
.LBB0_4:                                # %else3
	movl	12(%rsp), %edi
	decl	%edi
	callq	go
	movl	%eax, %ebx
	movl	12(%rsp), %edi
	addl	$-2, %edi
	callq	go
	addl	%ebx, %eax
.LBB0_2:                                # %then
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	go, .Lfunc_end0-go
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$10, %edi
	callq	go
	movl	%eax, i(%rip)
	movl	$.L__unnamed_1, %edi
	movl	%eax, %esi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	i,@object               # @i
	.local	i
	.comm	i,4,4
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"\"hello,%d\\0D\""
	.size	.L__unnamed_1, 14

	.section	".note.GNU-stack","",@progbits
