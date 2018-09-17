	.file	"main.c"
	.intel_syntax noprefix
	.globl	a
	.data
	.align 4
a:
	.long	51
	.globl	a2
	.align 4
a2:
	.long	51
	.align 4
b:
	.long	52
	.globl	c
	.section .rdata,"dr"
	.align 4
c:
	.long	53
	.comm	m, 4, 2
	.comm	n, 4, 2
	.def	__main;	.scl	2;	.type	32;	.endef
.LC0:
	.ascii "hello world\0"
.LC1:
	.ascii "miao world\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 64
	.seh_stackalloc	64
	.seh_endprologue
	call	__main
	lea	rax, .LC0[rip]
	mov	QWORD PTR -8[rbp], rax
	lea	rax, .LC0[rip]
	mov	QWORD PTR -16[rbp], rax
	lea	rax, .LC1[rip]
	mov	QWORD PTR -24[rbp], rax
	mov	rax, QWORD PTR -8[rbp]
	mov	rcx, rax
	call	func
	mov	rax, QWORD PTR -16[rbp]
	mov	rcx, rax
	call	func
	mov	rax, QWORD PTR -24[rbp]
	mov	rcx, rax
	call	func
	mov	eax, 0
	add	rsp, 64
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC2:
	.ascii "c:%d e:%d\0"
	.text
	.globl	func
	.def	func;	.scl	2;	.type	32;	.endef
	.seh_proc	func
func:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 64
	.seh_stackalloc	64
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	DWORD PTR -4[rbp], 54
	mov	DWORD PTR -28[rbp], 55
	lea	rax, -28[rbp]
	mov	QWORD PTR -16[rbp], rax
	mov	rax, QWORD PTR -16[rbp]
	mov	DWORD PTR [rax], 60
	lea	rax, c[rip]
	mov	QWORD PTR -24[rbp], rax
	mov	rax, QWORD PTR -16[rbp]
	mov	edx, DWORD PTR [rax]
	mov	rax, QWORD PTR -24[rbp]
	mov	eax, DWORD PTR [rax]
	mov	r8d, edx
	mov	edx, eax
	lea	rcx, .LC2[rip]
	call	printf
	mov	eax, 0
	add	rsp, 64
	pop	rbp
	ret
	.seh_endproc
	.data
	.align 4
f.2832:
	.long	59
	.ident	"GCC: (GNU) 4.8.3"
	.def	printf;	.scl	2;	.type	32;	.endef
