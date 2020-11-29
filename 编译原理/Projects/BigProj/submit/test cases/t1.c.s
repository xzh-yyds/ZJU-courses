	.text
	.file	"t1.c"
	.globl	gcd                     # -- Begin function gcd
	.p2align	4, 0x90
	.type	gcd,@function
gcd:                                    # @gcd
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	testl	%esi, %esi
	je	.LBB0_1
# %bb.2:                                # %else
	movl	4(%rsp), %edi
	movl	(%rsp), %eax
	cltd
	idivl	%edi
	movl	%edx, %esi
	callq	gcd
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.LBB0_1:                                # %then
	.cfi_def_cfa_offset 16
	movl	(%rsp), %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	gcd, .Lfunc_end0-gcd
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$9, %edi
	movl	$36, %esi
	callq	gcd
	movl	%eax, %ebx
	movl	$3, %edi
	movl	$6, %esi
	callq	gcd
	imull	%ebx, %eax
	movl	%eax, ans(%rip)
	movl	$.L__unnamed_1, %edi
	movl	%eax, %esi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_2, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	ans,@object             # @ans
	.local	ans
	.comm	ans,4,4
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"ans = %d"
	.size	.L__unnamed_1, 9

	.type	.L__unnamed_2,@object   # @1
.L__unnamed_2:
	.asciz	"\n"
	.size	.L__unnamed_2, 2

	.section	".note.GNU-stack","",@progbits
