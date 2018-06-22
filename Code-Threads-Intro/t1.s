	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_Pthread_mutex_lock     ## -- Begin function Pthread_mutex_lock
	.p2align	4, 0x90
_Pthread_mutex_lock:                    ## @Pthread_mutex_lock
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
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_pthread_mutex_lock
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	sete	%cl
	xorb	$-1, %cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movslq	%eax, %rdi
	cmpq	$0, %rdi
	je	LBB0_2
## BB#1:
	leaq	L___func__.Pthread_mutex_lock(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	movl	$10, %edx
	leaq	L_.str.1(%rip), %rcx
	callq	___assert_rtn
LBB0_2:
	jmp	LBB0_3
LBB0_3:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_Pthread_mutex_unlock   ## -- Begin function Pthread_mutex_unlock
	.p2align	4, 0x90
_Pthread_mutex_unlock:                  ## @Pthread_mutex_unlock
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_pthread_mutex_unlock
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	sete	%cl
	xorb	$-1, %cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movslq	%eax, %rdi
	cmpq	$0, %rdi
	je	LBB1_2
## BB#1:
	leaq	L___func__.Pthread_mutex_unlock(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	movl	$15, %edx
	leaq	L_.str.1(%rip), %rcx
	callq	___assert_rtn
LBB1_2:
	jmp	LBB1_3
LBB1_3:
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_Pthread_create         ## -- Begin function Pthread_create
	.p2align	4, 0x90
_Pthread_create:                        ## @Pthread_create
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi6:
	.cfi_def_cfa_offset 16
Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi8:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rcx
	callq	_pthread_create
	movl	%eax, -36(%rbp)
	cmpl	$0, -36(%rbp)
	sete	%r8b
	xorb	$-1, %r8b
	andb	$1, %r8b
	movzbl	%r8b, %eax
	movslq	%eax, %rcx
	cmpq	$0, %rcx
	je	LBB2_2
## BB#1:
	leaq	L___func__.Pthread_create(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	movl	$20, %edx
	leaq	L_.str.1(%rip), %rcx
	callq	___assert_rtn
LBB2_2:
	jmp	LBB2_3
LBB2_3:
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_Pthread_join           ## -- Begin function Pthread_join
	.p2align	4, 0x90
_Pthread_join:                          ## @Pthread_join
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi9:
	.cfi_def_cfa_offset 16
Lcfi10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi11:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	callq	_pthread_join
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	sete	%cl
	xorb	$-1, %cl
	andb	$1, %cl
	movzbl	%cl, %eax
	movslq	%eax, %rsi
	cmpq	$0, %rsi
	je	LBB3_2
## BB#1:
	leaq	L___func__.Pthread_join(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	movl	$25, %edx
	leaq	L_.str.1(%rip), %rcx
	callq	___assert_rtn
LBB3_2:
	jmp	LBB3_3
LBB3_3:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_mythread               ## -- Begin function mythread
	.p2align	4, 0x90
_mythread:                              ## @mythread
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi12:
	.cfi_def_cfa_offset 16
Lcfi13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi14:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str.2(%rip), %rax
	leaq	-20(%rbp), %rdx
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -20(%rbp)
	movl	%eax, -24(%rbp)         ## 4-byte Spill
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	_max@GOTPCREL(%rip), %rax
	movl	-20(%rbp), %ecx
	cmpl	(%rax), %ecx
	jge	LBB4_4
## BB#2:                                ##   in Loop: Header=BB4_1 Depth=1
	movl	_counter(%rip), %eax
	addl	$1, %eax
	movl	%eax, _counter(%rip)
## BB#3:                                ##   in Loop: Header=BB4_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB4_1
LBB4_4:
	leaq	L_.str.3(%rip), %rdi
	movq	-16(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movq	%rsi, %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi15:
	.cfi_def_cfa_offset 16
Lcfi16:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi17:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpl	$2, -8(%rbp)
	je	LBB5_2
## BB#1:
	leaq	L_.str.4(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movb	$0, %al
	callq	_fprintf
	movl	$1, %edi
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	callq	_exit
LBB5_2:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdi
	callq	_atoi
	leaq	L_.str.5(%rip), %rdi
	leaq	_counter(%rip), %rcx
	movl	%ecx, %edx
	movq	_max@GOTPCREL(%rip), %rcx
	movl	%eax, (%rcx)
	movl	_counter(%rip), %esi
	movb	$0, %al
	callq	_printf
	leaq	-24(%rbp), %rdi
	xorl	%edx, %edx
	movl	%edx, %esi
	leaq	_mythread(%rip), %rdx
	leaq	L_.str.6(%rip), %rcx
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	callq	_Pthread_create
	leaq	-32(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	leaq	_mythread(%rip), %rdx
	leaq	L_.str.7(%rip), %rcx
	callq	_Pthread_create
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-24(%rbp), %rdi
	callq	_Pthread_join
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-32(%rbp), %rdi
	callq	_Pthread_join
	leaq	L_.str.8(%rip), %rdi
	movq	_max@GOTPCREL(%rip), %rcx
	movl	_counter(%rip), %esi
	movl	(%rcx), %eax
	shll	$1, %eax
	movl	%eax, %edx
	movb	$0, %al
	callq	_printf
	xorl	%edx, %edx
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	movl	%edx, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L___func__.Pthread_mutex_lock:          ## @__func__.Pthread_mutex_lock
	.asciz	"Pthread_mutex_lock"

L_.str:                                 ## @.str
	.asciz	"./mythreads.h"

L_.str.1:                               ## @.str.1
	.asciz	"rc == 0"

L___func__.Pthread_mutex_unlock:        ## @__func__.Pthread_mutex_unlock
	.asciz	"Pthread_mutex_unlock"

L___func__.Pthread_create:              ## @__func__.Pthread_create
	.asciz	"Pthread_create"

L___func__.Pthread_join:                ## @__func__.Pthread_join
	.asciz	"Pthread_join"

	.globl	_counter                ## @counter
.zerofill __DATA,__common,_counter,4,2
L_.str.2:                               ## @.str.2
	.asciz	"%s: begin [addr of i: %p]\n"

	.comm	_max,4,2                ## @max
L_.str.3:                               ## @.str.3
	.asciz	"%s: done\n"

L_.str.4:                               ## @.str.4
	.asciz	"usage: main-first <loopcount>\n"

L_.str.5:                               ## @.str.5
	.asciz	"main: begin [counter = %d] [%x]\n"

L_.str.6:                               ## @.str.6
	.asciz	"A"

L_.str.7:                               ## @.str.7
	.asciz	"B"

L_.str.8:                               ## @.str.8
	.asciz	"main: done\n [counter: %d]\n [should: %d]\n"


.subsections_via_symbols
