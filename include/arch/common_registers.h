//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_COMMON_REGISTERS_H
#define UNWIND_COMMON_REGISTERS_H

#include "stdint.h"

// For emulating 128-bit arch
struct v128 {
    uint32_t vec[4];
};

// architecture independent register numbers
enum {
    UNW_REG_IP = -1, // instruction pointer
    UNW_REG_SP = -2, // stack pointer
};

// support architectures
enum {
    ARCH_X86,
    ARCH_X86_64,
    ARCH_ARM64,
    ARCH_ARM,
    ARCH_RISCV,
};

// architecture common type
template<typename GPRs>
class CommonRegisters;

//        {
//public:
//    bool validRegister(int regId) const;
//    typename GPRs::reg_t getRegister(int regId) const;
//    void setRegister(int regId, typename GPRs::reg_t val);
//
//    bool validFloatRegister(int regId) const;
//    double getFloatRegister(int regId) const;
//    void setFloatRegister(int regId, double val);
//
//    bool validVectorRegister(int regId) const;
//    v128 getVectorRegister(int regId) const;
//    void setVectorRegister(int regId, v128 val);
//
//    const char *getRegisterName(int regId) const;
//    void jumpTo();
//    int lastDwarfRegNum() const;
//    int getArch() const;
//
//    typename GPRs::reg_t getSP() const;
//    void setSP(typename GPRs::reg_t val);
//
//    typename GPRs::reg_t getIP() const;
//    void setIP(typename GPRs::reg_t val);
//};

#endif //UNWIND_COMMON_REGISTERS_H
