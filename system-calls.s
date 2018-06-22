	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$1, %edi
	movl	$3, %eax
	movl	%eax, %edx
	leaq	L_.str(%rip), %rcx
	movl	$0, -4(%rbp)
	movq	%rcx, -16(%rbp)
	movq	-16(%rbp), %rsi
	callq	_write
	xorl	%edi, %edi
	movq	%rax, -24(%rbp)         ## 8-byte Spill
	movl	%edi, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"123"


.subsections_via_symbols
