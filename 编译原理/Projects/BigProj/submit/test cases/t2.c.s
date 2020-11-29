	.text
	.file	"t2.c"
	.globl	go                      # -- Begin function go
	.p2align	4, 0x90
	.type	go,@function
go:                                     # @go
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -16
	movl	%edi, 16(%rsp)
	movl	%esi, 12(%rsp)
	movl	$0, 20(%rsp)
	movq	$0, 24(%rsp)
	testl	%esi, %esi
	jle	.LBB0_2
# %bb.1:                                # %then
	movl	12(%rsp), %ebx
	movl	16(%rsp), %edi
	leal	-1(%rbx), %esi
	callq	go
	imull	%ebx, %eax
	jmp	.LBB0_3
.LBB0_2:                                # %else
	movl	$1, %eax
.LBB0_3:                                # %else
	addq	$32, %rsp
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
	movl	$0, k(%rip)
	xorl	%edi, %edi
	movl	$5, %esi
	callq	go
	movl	%eax, f(%rip)
	movl	$.L__unnamed_1, %edi
	movl	%eax, %esi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_2, %edi
	xorl	%eax, %eax
	callq	printf
	movl	k(%rip), %esi
	movl	$.L__unnamed_3, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_4, %edi
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
	.type	k,@object               # @k
	.local	k
	.comm	k,4,4
	.type	f,@object               # @f
	.local	f
	.comm	f,4,4
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"%d"
	.size	.L__unnamed_1, 3

	.type	.L__unnamed_2,@object   # @1
.L__unnamed_2:
	.asciz	"\n"
	.size	.L__unnamed_2, 2

	.type	.L__unnamed_3,@object   # @2
.L__unnamed_3:
	.asciz	"%d"
	.size	.L__unnamed_3, 3

	.type	.L__unnamed_4,@object   # @3
.L__unnamed_4:
	.asciz	"\n"
	.size	.L__unnamed_4, 2

	.section	".note.GNU-stack","",@progbits
