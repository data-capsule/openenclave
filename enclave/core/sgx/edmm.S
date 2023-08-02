// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include "asmdefs.h"
#include "asmcommon.inc"

//==============================================================================
// This file implements the necessary wrappers of Intel SGX primitives required
// by the Enclave Memory Manager (emm) library that supports the Enclave Dynamic
// Memory Management (EDMM) feature on SGX2 CPUs.
//==============================================================================

.globl do_eaccept
.type do_eaccept, @function
do_eaccept:
.cfi_startproc

    push %rbx
    push %rcx
    movq %rdi, %rbx
    movq %rsi, %rcx

    // Execute EACCEPT.
    movq $ENCLU_EACCEPT, %rax
    ENCLU

    pop %rcx
    pop %rbx

    ret
.cfi_endproc

.globl do_eacceptcopy
.type do_eacceptcopy, @function
do_eacceptcopy:
.cfi_startproc
    push %rbx
    push %rcx
    movq %rdi, %rbx
    movq %rsi, %rcx

    // Execute EACCEPTCOPY
    movq $ENCLU_EACCEPTCOPY, %rax
    ENCLU

    pop %rcx
    pop %rbx

    ret
.cfi_endproc

.globl do_emodpe
.type do_emodpe, @function
do_emodpe:
.cfi_startproc
    push %rbx
    push %rcx
    movq %rdi, %rbx
    movq %rsi, %rcx

    // Execute EMODPE
    movq $ENCLU_EMODPE, %rax
    ENCLU

    pop %rcx
    pop %rbx

    ret
.cfi_endproc
