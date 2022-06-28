//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_REGISTERS_H
#define UNWIND_REGISTERS_H

#include "stdint.h"

#if defined(__i386__)
#include "arch/x86_registers.h"
#elif defined(__x86_64__)
#include "arch/x86_64_registers.h"
#elif defined(__aarch64__)
#include "arch/aarch64_registers.h"
#elif defined(__arm__)
#include "arch/arm_registers.h"
#elif defined((__riscv)
#include "arch/riscv_registers.h"
#endif

#endif //UNWIND_REGISTERS_H
