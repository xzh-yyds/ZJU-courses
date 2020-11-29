	.text
	.file	"t4.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$7, (%rsp)
	movl	$.L__unnamed_1, %edi
	movl	$7, %esi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_2, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$1, 4(%rsp)
	movl	(%rsp), %esi
	addl	%esi, %esi
	movl	%esi, (%rsp)
	movl	$.L__unnamed_3, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_4, %edi
	xorl	%eax, %eax
	callq	printf
	cmpl	$100, (%rsp)
	jge	.LBB0_3
	.p2align	4, 0x90
.LBB0_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	movl	(%rsp), %eax
	addl	%eax, 4(%rsp)
	incl	%eax
	movl	%eax, (%rsp)
	cmpl	$100, (%rsp)
	jl	.LBB0_1
.LBB0_3:                                # %outer
	movl	(%rsp), %esi
	movl	$.L__unnamed_5, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_6, %edi
	xorl	%eax, %eax
	callq	printf
	movl	4(%rsp), %esi
	movl	$.L__unnamed_7, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_8, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"a = %d"
	.size	.L__unnamed_1, 7

	.type	.L__unnamed_2,@object   # @1
.L__unnamed_2:
	.asciz	"\n"
	.size	.L__unnamed_2, 2

	.type	.L__unnamed_3,@object   # @2
.L__unnamed_3:
	.asciz	"a = %d"
	.size	.L__unnamed_3, 7

	.type	.L__unnamed_4,@object   # @3
.L__unnamed_4:
	.asciz	"\n"
	.size	.L__unnamed_4, 2

	.type	.L__unnamed_5,@object   # @4
.L__unnamed_5:
	.asciz	"a = %d"
	.size	.L__unnamed_5, 7

	.type	.L__unnamed_6,@object   # @5
.L__unnamed_6:
	.asciz	"\n"
	.size	.L__unnamed_6, 2

	.type	.L__unnamed_7,@object   # @6
.L__unnamed_7:
	.asciz	"b = %d"
	.size	.L__unnamed_7, 7

	.type	.L__unnamed_8,@object   # @7
.L__unnamed_8:
	.asciz	"\n"
	.size	.L__unnamed_8, 2

	.section	".note.GNU-stack","",@progbits
