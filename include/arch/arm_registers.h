//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_ARM_REGISTERS_H
#define UNWIND_ARM_REGISTERS_H

#include "common_registers.h"

#define _UNWIND_TARGET_ARM

// 32-bit ARM registers. Numbers match DWARF for ARM spec #3.1 Table 1.
// Naming scheme uses recommendations given in Note 4 for VFP-v2 and VFP-v3.
// In this scheme, even though the 64-bit floating point registers D0-D31
// overlap physically with the 32-bit floating pointer registers S0-S31,
// they are given a non-overlapping range of register numbers.
//
// Commented out ranges are not preserved during unwinding.
enum {
    UNW_ARM_R0  = 0,
    UNW_ARM_R1  = 1,
    UNW_ARM_R2  = 2,
    UNW_ARM_R3  = 3,
    UNW_ARM_R4  = 4,
    UNW_ARM_R5  = 5,
    UNW_ARM_R6  = 6,
    UNW_ARM_R7  = 7,
    UNW_ARM_R8  = 8,
    UNW_ARM_R9  = 9,
    UNW_ARM_R10 = 10,
    UNW_ARM_R11 = 11,
    UNW_ARM_R12 = 12,
    UNW_ARM_SP  = 13,  // Logical alias for UNW_REG_SP
    UNW_ARM_R13 = 13,
    UNW_ARM_LR  = 14,
    UNW_ARM_R14 = 14,
    UNW_ARM_IP  = 15,  // Logical alias for UNW_REG_IP
    UNW_ARM_R15 = 15,
    // 16-63 -- OBSOLETE. Used in VFP1 to represent both S0-S31 and D0-D31.
    UNW_ARM_S0  = 64,
    UNW_ARM_S1  = 65,
    UNW_ARM_S2  = 66,
    UNW_ARM_S3  = 67,
    UNW_ARM_S4  = 68,
    UNW_ARM_S5  = 69,
    UNW_ARM_S6  = 70,
    UNW_ARM_S7  = 71,
    UNW_ARM_S8  = 72,
    UNW_ARM_S9  = 73,
    UNW_ARM_S10 = 74,
    UNW_ARM_S11 = 75,
    UNW_ARM_S12 = 76,
    UNW_ARM_S13 = 77,
    UNW_ARM_S14 = 78,
    UNW_ARM_S15 = 79,
    UNW_ARM_S16 = 80,
    UNW_ARM_S17 = 81,
    UNW_ARM_S18 = 82,
    UNW_ARM_S19 = 83,
    UNW_ARM_S20 = 84,
    UNW_ARM_S21 = 85,
    UNW_ARM_S22 = 86,
    UNW_ARM_S23 = 87,
    UNW_ARM_S24 = 88,
    UNW_ARM_S25 = 89,
    UNW_ARM_S26 = 90,
    UNW_ARM_S27 = 91,
    UNW_ARM_S28 = 92,
    UNW_ARM_S29 = 93,
    UNW_ARM_S30 = 94,
    UNW_ARM_S31 = 95,
    //  96-103 -- OBSOLETE. F0-F7. Used by the FPA system. Superseded by VFP.
    // 104-111 -- wCGR0-wCGR7, ACC0-ACC7 (Intel wireless MMX)
    UNW_ARM_WR0 = 112,
    UNW_ARM_WR1 = 113,
    UNW_ARM_WR2 = 114,
    UNW_ARM_WR3 = 115,
    UNW_ARM_WR4 = 116,
    UNW_ARM_WR5 = 117,
    UNW_ARM_WR6 = 118,
    UNW_ARM_WR7 = 119,
    UNW_ARM_WR8 = 120,
    UNW_ARM_WR9 = 121,
    UNW_ARM_WR10 = 122,
    UNW_ARM_WR11 = 123,
    UNW_ARM_WR12 = 124,
    UNW_ARM_WR13 = 125,
    UNW_ARM_WR14 = 126,
    UNW_ARM_WR15 = 127,
    // 128-133 -- SPSR, SPSR_{FIQ|IRQ|ABT|UND|SVC}
    // 134-142 -- Reserved
    UNW_ARM_RA_AUTH_CODE = 143,
    // 144-150 -- R8_USR-R14_USR
    // 151-157 -- R8_FIQ-R14_FIQ
    // 158-159 -- R13_IRQ-R14_IRQ
    // 160-161 -- R13_ABT-R14_ABT
    // 162-163 -- R13_UND-R14_UND
    // 164-165 -- R13_SVC-R14_SVC
    // 166-191 -- Reserved
    UNW_ARM_WC0 = 192,
    UNW_ARM_WC1 = 193,
    UNW_ARM_WC2 = 194,
    UNW_ARM_WC3 = 195,
    // 196-199 -- wC4-wC7 (Intel wireless MMX control)
    // 200-255 -- Reserved
    UNW_ARM_D0  = 256,
    UNW_ARM_D1  = 257,
    UNW_ARM_D2  = 258,
    UNW_ARM_D3  = 259,
    UNW_ARM_D4  = 260,
    UNW_ARM_D5  = 261,
    UNW_ARM_D6  = 262,
    UNW_ARM_D7  = 263,
    UNW_ARM_D8  = 264,
    UNW_ARM_D9  = 265,
    UNW_ARM_D10 = 266,
    UNW_ARM_D11 = 267,
    UNW_ARM_D12 = 268,
    UNW_ARM_D13 = 269,
    UNW_ARM_D14 = 270,
    UNW_ARM_D15 = 271,
    UNW_ARM_D16 = 272,
    UNW_ARM_D17 = 273,
    UNW_ARM_D18 = 274,
    UNW_ARM_D19 = 275,
    UNW_ARM_D20 = 276,
    UNW_ARM_D21 = 277,
    UNW_ARM_D22 = 278,
    UNW_ARM_D23 = 279,
    UNW_ARM_D24 = 280,
    UNW_ARM_D25 = 281,
    UNW_ARM_D26 = 282,
    UNW_ARM_D27 = 283,
    UNW_ARM_D28 = 284,
    UNW_ARM_D29 = 285,
    UNW_ARM_D30 = 286,
    UNW_ARM_D31 = 287,
    // 288-319 -- Reserved for VFP/Neon
    // 320-8191 -- Reserved
    // 8192-16383 -- Unspecified vendor co-processor register.
};


#endif //UNWIND_ARM_REGISTERS_H
