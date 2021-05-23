	.text
	.intel_syntax noprefix
	.file	"vector.c"
	.globl	new_vec                 # -- Begin function new_vec
	.p2align	4, 0x90
	.type	new_vec,@function
new_vec:                                # @new_vec
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	qword ptr [rbp - 16], rdi
	mov	edi, 16
	call	malloc
	mov	qword ptr [rbp - 24], rax
	mov	qword ptr [rbp - 32], 0
	cmp	qword ptr [rbp - 24], 0
	jne	.LBB0_2
# %bb.1:
	mov	qword ptr [rbp - 8], 0
	jmp	.LBB0_7
.LBB0_2:
	mov	rax, qword ptr [rbp - 16]
	mov	rcx, qword ptr [rbp - 24]
	mov	qword ptr [rcx], rax
	cmp	qword ptr [rbp - 16], 0
	jle	.LBB0_6
# %bb.3:
	mov	rdi, qword ptr [rbp - 16]
	mov	esi, 8
	call	calloc
	mov	qword ptr [rbp - 32], rax
	cmp	qword ptr [rbp - 32], 0
	jne	.LBB0_5
# %bb.4:
	mov	rax, qword ptr [rbp - 24]
	mov	rdi, rax
	mov	al, 0
	call	free
	mov	qword ptr [rbp - 8], 0
	jmp	.LBB0_7
.LBB0_5:
	jmp	.LBB0_6
.LBB0_6:
	mov	rax, qword ptr [rbp - 32]
	mov	rcx, qword ptr [rbp - 24]
	mov	qword ptr [rcx + 8], rax
	mov	rax, qword ptr [rbp - 24]
	mov	qword ptr [rbp - 8], rax
.LBB0_7:
	mov	rax, qword ptr [rbp - 8]
	add	rsp, 32
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end0:
	.size	new_vec, .Lfunc_end0-new_vec
	.cfi_endproc
                                        # -- End function
	.globl	get_vec_element         # -- Begin function get_vec_element
	.p2align	4, 0x90
	.type	get_vec_element,@function
get_vec_element:                        # @get_vec_element
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 16], rdi
	mov	qword ptr [rbp - 24], rsi
	mov	qword ptr [rbp - 32], rdx
	cmp	qword ptr [rbp - 24], 0
	jl	.LBB1_2
# %bb.1:
	mov	rax, qword ptr [rbp - 24]
	mov	rcx, qword ptr [rbp - 16]
	cmp	rax, qword ptr [rcx]
	jl	.LBB1_3
.LBB1_2:
	mov	dword ptr [rbp - 4], 0
	jmp	.LBB1_4
.LBB1_3:
	mov	rax, qword ptr [rbp - 16]
	mov	rax, qword ptr [rax + 8]
	mov	rcx, qword ptr [rbp - 24]
	mov	rax, qword ptr [rax + 8*rcx]
	mov	rcx, qword ptr [rbp - 32]
	mov	qword ptr [rcx], rax
	mov	dword ptr [rbp - 4], 1
.LBB1_4:
	mov	eax, dword ptr [rbp - 4]
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end1:
	.size	get_vec_element, .Lfunc_end1-get_vec_element
	.cfi_endproc
                                        # -- End function
	.globl	vec_length              # -- Begin function vec_length
	.p2align	4, 0x90
	.type	vec_length,@function
vec_length:                             # @vec_length
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 8], rdi
	mov	rax, qword ptr [rbp - 8]
	mov	rax, qword ptr [rax]
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end2:
	.size	vec_length, .Lfunc_end2-vec_length
	.cfi_endproc
                                        # -- End function
	.globl	combine1                # -- Begin function combine1
	.p2align	4, 0x90
	.type	combine1,@function
combine1:                               # @combine1
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 48
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rax], 0
	mov	qword ptr [rbp - 24], 0
.LBB3_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 24]
	mov	rdi, qword ptr [rbp - 8]
	mov	qword ptr [rbp - 40], rax # 8-byte Spill
	call	vec_length
	mov	rcx, qword ptr [rbp - 40] # 8-byte Reload
	cmp	rcx, rax
	jge	.LBB3_4
# %bb.2:                                #   in Loop: Header=BB3_1 Depth=1
	mov	rdi, qword ptr [rbp - 8]
	mov	rsi, qword ptr [rbp - 24]
	lea	rdx, [rbp - 32]
	call	get_vec_element
	mov	rcx, qword ptr [rbp - 16]
	mov	rcx, qword ptr [rcx]
	add	rcx, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 16]
	mov	qword ptr [rdx], rcx
# %bb.3:                                #   in Loop: Header=BB3_1 Depth=1
	mov	rax, qword ptr [rbp - 24]
	add	rax, 1
	mov	qword ptr [rbp - 24], rax
	jmp	.LBB3_1
.LBB3_4:
	add	rsp, 48
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end3:
	.size	combine1, .Lfunc_end3-combine1
	.cfi_endproc
                                        # -- End function
	.globl	combine2                # -- Begin function combine2
	.p2align	4, 0x90
	.type	combine2,@function
combine2:                               # @combine2
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 48
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	rdi, qword ptr [rbp - 8]
	call	vec_length
	mov	qword ptr [rbp - 32], rax
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rax], 0
	mov	qword ptr [rbp - 24], 0
.LBB4_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 24]
	cmp	rax, qword ptr [rbp - 32]
	jge	.LBB4_4
# %bb.2:                                #   in Loop: Header=BB4_1 Depth=1
	mov	rdi, qword ptr [rbp - 8]
	mov	rsi, qword ptr [rbp - 24]
	lea	rdx, [rbp - 40]
	call	get_vec_element
	mov	rcx, qword ptr [rbp - 16]
	mov	rcx, qword ptr [rcx]
	add	rcx, qword ptr [rbp - 40]
	mov	rdx, qword ptr [rbp - 16]
	mov	qword ptr [rdx], rcx
# %bb.3:                                #   in Loop: Header=BB4_1 Depth=1
	mov	rax, qword ptr [rbp - 24]
	add	rax, 1
	mov	qword ptr [rbp - 24], rax
	jmp	.LBB4_1
.LBB4_4:
	add	rsp, 48
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end4:
	.size	combine2, .Lfunc_end4-combine2
	.cfi_endproc
                                        # -- End function
	.globl	combine3                # -- Begin function combine3
	.p2align	4, 0x90
	.type	combine3,@function
combine3:                               # @combine3
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 48
	mov	qword ptr [rbp - 8], rdi
	mov	qword ptr [rbp - 16], rsi
	mov	rdi, qword ptr [rbp - 8]
	call	vec_length
	mov	qword ptr [rbp - 32], rax
	mov	rdi, qword ptr [rbp - 8]
	mov	al, 0
	call	get_vec_start
	movsxd	rcx, eax
	mov	qword ptr [rbp - 40], rcx
	mov	rcx, qword ptr [rbp - 16]
	mov	qword ptr [rcx], 0
	mov	qword ptr [rbp - 24], 0
.LBB5_1:                                # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 24]
	cmp	rax, qword ptr [rbp - 32]
	jge	.LBB5_4
# %bb.2:                                #   in Loop: Header=BB5_1 Depth=1
	mov	rax, qword ptr [rbp - 16]
	mov	rax, qword ptr [rax]
	mov	rcx, qword ptr [rbp - 40]
	mov	rdx, qword ptr [rbp - 24]
	add	rax, qword ptr [rcx + 8*rdx]
	mov	rcx, qword ptr [rbp - 16]
	mov	qword ptr [rcx], rax
# %bb.3:                                #   in Loop: Header=BB5_1 Depth=1
	mov	rax, qword ptr [rbp - 24]
	add	rax, 1
	mov	qword ptr [rbp - 24], rax
	jmp	.LBB5_1
.LBB5_4:
	add	rsp, 48
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end5:
	.size	combine3, .Lfunc_end5-combine3
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	xor	eax, eax
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end6:
	.size	main, .Lfunc_end6-main
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 10.0.0-4ubuntu1 "
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym malloc
	.addrsig_sym calloc
	.addrsig_sym free
	.addrsig_sym get_vec_element
	.addrsig_sym vec_length
	.addrsig_sym get_vec_start
