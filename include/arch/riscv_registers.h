//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_RISCV_REGISTERS_H
#define UNWIND_RISCV_REGISTERS_H

#include "common_registers.h"

#define _UNWIND_TARGET_RISCV

// RISC-V registers. These match the DWARF register numbers defined by section
// 4 of the RISC-V ELF psABI specification, which can be found at:
//
// https://github.com/riscv/riscv-elf-psabi-doc/blob/master/riscv-elf.md
enum {
    UNW_RISCV_X0  = 0,
    UNW_RISCV_X1  = 1,
    UNW_RISCV_X2  = 2,
    UNW_RISCV_X3  = 3,
    UNW_RISCV_X4  = 4,
    UNW_RISCV_X5  = 5,
    UNW_RISCV_X6  = 6,
    UNW_RISCV_X7  = 7,
    UNW_RISCV_X8  = 8,
    UNW_RISCV_X9  = 9,
    UNW_RISCV_X10 = 10,
    UNW_RISCV_X11 = 11,
    UNW_RISCV_X12 = 12,
    UNW_RISCV_X13 = 13,
    UNW_RISCV_X14 = 14,
    UNW_RISCV_X15 = 15,
    UNW_RISCV_X16 = 16,
    UNW_RISCV_X17 = 17,
    UNW_RISCV_X18 = 18,
    UNW_RISCV_X19 = 19,
    UNW_RISCV_X20 = 20,
    UNW_RISCV_X21 = 21,
    UNW_RISCV_X22 = 22,
    UNW_RISCV_X23 = 23,
    UNW_RISCV_X24 = 24,
    UNW_RISCV_X25 = 25,
    UNW_RISCV_X26 = 26,
    UNW_RISCV_X27 = 27,
    UNW_RISCV_X28 = 28,
    UNW_RISCV_X29 = 29,
    UNW_RISCV_X30 = 30,
    UNW_RISCV_X31 = 31,
    UNW_RISCV_F0  = 32,
    UNW_RISCV_F1  = 33,
    UNW_RISCV_F2  = 34,
    UNW_RISCV_F3  = 35,
    UNW_RISCV_F4  = 36,
    UNW_RISCV_F5  = 37,
    UNW_RISCV_F6  = 38,
    UNW_RISCV_F7  = 39,
    UNW_RISCV_F8  = 40,
    UNW_RISCV_F9  = 41,
    UNW_RISCV_F10 = 42,
    UNW_RISCV_F11 = 43,
    UNW_RISCV_F12 = 44,
    UNW_RISCV_F13 = 45,
    UNW_RISCV_F14 = 46,
    UNW_RISCV_F15 = 47,
    UNW_RISCV_F16 = 48,
    UNW_RISCV_F17 = 49,
    UNW_RISCV_F18 = 50,
    UNW_RISCV_F19 = 51,
    UNW_RISCV_F20 = 52,
    UNW_RISCV_F21 = 53,
    UNW_RISCV_F22 = 54,
    UNW_RISCV_F23 = 55,
    UNW_RISCV_F24 = 56,
    UNW_RISCV_F25 = 57,
    UNW_RISCV_F26 = 58,
    UNW_RISCV_F27 = 59,
    UNW_RISCV_F28 = 60,
    UNW_RISCV_F29 = 61,
    UNW_RISCV_F30 = 62,
    UNW_RISCV_F31 = 63,
};


#endif //UNWIND_RISCV_REGISTERS_H
