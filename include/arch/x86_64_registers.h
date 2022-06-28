//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_X86_64_REGISTERS_H
#define UNWIND_X86_64_REGISTERS_H

#include "common_registers.h"

#include <string.h>

#define _UNWIND_TARGET_X86_64

// 64-bit x86_64 registers
enum {
    UNW_X86_64_RAX = 0,
    UNW_X86_64_RDX = 1,
    UNW_X86_64_RCX = 2,
    UNW_X86_64_RBX = 3,
    UNW_X86_64_RSI = 4,
    UNW_X86_64_RDI = 5,
    UNW_X86_64_RBP = 6,
    UNW_X86_64_RSP = 7,
    UNW_X86_64_R8  = 8,
    UNW_X86_64_R9  = 9,
    UNW_X86_64_R10 = 10,
    UNW_X86_64_R11 = 11,
    UNW_X86_64_R12 = 12,
    UNW_X86_64_R13 = 13,
    UNW_X86_64_R14 = 14,
    UNW_X86_64_R15 = 15,
    UNW_X86_64_RIP = 16,
};

struct GPRs_x86_64 {
    typedef uint64_t reg_t;

    GPRs_x86_64():__rax(0), __rbx(0), __rcx(0), __rdx(0), __rdi(0), __rsi(0),
                    __rbp(0), __rsp(0), __r8(0), __r9(0), __r10(0), __r11(0),
                    __r12(0), __r13(0), __r14(0), __r15(0), __rip(0), __rflags(0),
                    __cs(0), __fs(0), __gs(0){}

    explicit GPRs_x86_64(const void * registers) {
        memcpy(this,registers,sizeof(GPRs_x86_64));
    }

    reg_t __rax;
    reg_t __rbx;
    reg_t __rcx;
    reg_t __rdx;
    reg_t __rdi;
    reg_t __rsi;
    reg_t __rbp;
    reg_t __rsp;
    reg_t __r8;
    reg_t __r9;
    reg_t __r10;
    reg_t __r11;
    reg_t __r12;
    reg_t __r13;
    reg_t __r14;
    reg_t __r15;
    reg_t __rip;
    reg_t __rflags;
    reg_t __cs;
    reg_t __fs;
    reg_t __gs;
};

template<>
class CommonRegisters<GPRs_x86_64>;

extern "C" void __load_registers_x86_64(CommonRegisters<GPRs_x86_64> *);

template<>
class CommonRegisters<GPRs_x86_64> {
public:
    CommonRegisters();
    explicit CommonRegisters(const void * registers);

    static bool validRegister(int regId);
    GPRs_x86_64::reg_t getRegister(int regId) const;
    void setRegister(int regId, GPRs_x86_64::reg_t val);

    static const char * getRegisterName(int regId);
    void jumpTo();
    static int lastDwarfRegNum();
    static int getArch();

    GPRs_x86_64::reg_t getSP() const;
    void setSP(GPRs_x86_64::reg_t val);

    GPRs_x86_64::reg_t getIP() const;
    void setIP(GPRs_x86_64::reg_t val);

private:
    GPRs_x86_64 _registers;
};

inline CommonRegisters<GPRs_x86_64>::CommonRegisters():_registers() {}

inline CommonRegisters<GPRs_x86_64>::CommonRegisters(const void *registers):_registers(registers) {}

inline bool CommonRegisters<GPRs_x86_64>::validRegister(int regId) {
    if (regId == UNW_REG_IP)
        return true;
    if (regId == UNW_REG_SP)
        return true;
    if (regId < UNW_X86_64_RAX)
        return false;
    if (regId > UNW_X86_64_RIP)
        return false;
    return true;
}

inline GPRs_x86_64::reg_t CommonRegisters<GPRs_x86_64>::getRegister(int regId) const {
    switch (regId) {
        case UNW_REG_IP:
        case UNW_X86_64_RIP :
            return _registers.__rip;
        case UNW_REG_SP:
        case UNW_X86_64_RSP :
            return _registers.__rsp;
        case UNW_X86_64_RAX:
            return _registers.__rax;
        case UNW_X86_64_RDX :
            return _registers.__rdx;
        case UNW_X86_64_RCX :
            return _registers.__rcx;
        case UNW_X86_64_RBX :
            return _registers.__rbx;
        case UNW_X86_64_RSI :
            return _registers.__rsi;
        case UNW_X86_64_RDI :
            return _registers.__rdi;
        case UNW_X86_64_RBP :
            return _registers.__rbp;
        case UNW_X86_64_R8  :
            return _registers.__r8;
        case UNW_X86_64_R9  :
            return _registers.__r9;
        case UNW_X86_64_R10 :
            return _registers.__r10;
        case UNW_X86_64_R11 :
            return _registers.__r11;
        case UNW_X86_64_R12 :
            return _registers.__r12;
        case UNW_X86_64_R13 :
            return _registers.__r13;
        case UNW_X86_64_R14 :
            return _registers.__r14;
        case UNW_X86_64_R15 :
            return _registers.__r15;
        default:
            //todo 此处应该终止运行
            break;
    }
}

inline void CommonRegisters<GPRs_x86_64>::setRegister(int regId, GPRs_x86_64::reg_t val) {
    switch (regId) {
        case UNW_REG_IP:
        case UNW_X86_64_RIP :
            _registers.__rip = val;
            return;
        case UNW_REG_SP:
        case UNW_X86_64_RSP :
            _registers.__rsp = val;
            return;
        case UNW_X86_64_RAX:
             _registers.__rax = val;
             return;
        case UNW_X86_64_RDX :
             _registers.__rdx = val;
             return;
        case UNW_X86_64_RCX :
             _registers.__rcx = val;
             return;
        case UNW_X86_64_RBX :
             _registers.__rbx = val;
             return;
        case UNW_X86_64_RSI :
             _registers.__rsi = val;
             return;
        case UNW_X86_64_RDI :
             _registers.__rdi = val;
             return;
        case UNW_X86_64_RBP :
             _registers.__rbp = val;
             return;
        case UNW_X86_64_R8  :
             _registers.__r8 = val;
             return;
        case UNW_X86_64_R9  :
             _registers.__r9 = val;
             return;
        case UNW_X86_64_R10 :
             _registers.__r10 = val;
             return;
        case UNW_X86_64_R11 :
             _registers.__r11 = val;
             return;
        case UNW_X86_64_R12 :
             _registers.__r12 = val;
             return;
        case UNW_X86_64_R13 :
             _registers.__r13 = val;
             return;
        case UNW_X86_64_R14 :
             _registers.__r14 = val;
             return;
        case UNW_X86_64_R15 :
             _registers.__r15 = val;
             return;
        default:
            //todo 此处应该终止运行
            break;
    }
}

inline const char *CommonRegisters<GPRs_x86_64>::getRegisterName(int regId) {
    switch (regId) {
        case UNW_REG_IP:
        case UNW_X86_64_RIP:
            return "rip";
        case UNW_REG_SP:
        case UNW_X86_64_RSP:
            return "rsp";
        case UNW_X86_64_RAX:
            return "rax";
        case UNW_X86_64_RDX:
            return "rdx";
        case UNW_X86_64_RCX:
            return "rcx";
        case UNW_X86_64_RBX:
            return "rbx";
        case UNW_X86_64_RSI:
            return "rsi";
        case UNW_X86_64_RDI:
            return "rdi";
        case UNW_X86_64_RBP:
            return "rbp";
        case UNW_X86_64_R8 :
            return "r8";
        case UNW_X86_64_R9 :
            return "r9";
        case UNW_X86_64_R10:
            return "r10";
        case UNW_X86_64_R11:
            return "r11";
        case UNW_X86_64_R12:
            return "r12";
        case UNW_X86_64_R13:
            return "r13";
        case UNW_X86_64_R14:
            return "r14";
        case UNW_X86_64_R15:
            return "r15";
        default:
            //todo 此处应该终止运行
            break;
    }
}

inline void CommonRegisters<GPRs_x86_64>::jumpTo() {
    __load_registers_x86_64(this);
}

inline int CommonRegisters<GPRs_x86_64>::lastDwarfRegNum() {
    // todo 等待实现
}

inline int CommonRegisters<GPRs_x86_64>::getArch() {
    return ARCH_X86_64;
}

inline GPRs_x86_64::reg_t CommonRegisters<GPRs_x86_64>::getSP() const {
    return _registers.__rsp;
}

inline void CommonRegisters<GPRs_x86_64>::setSP(GPRs_x86_64::reg_t val) {
    _registers.__rsp = val;
}

inline GPRs_x86_64::reg_t CommonRegisters<GPRs_x86_64>::getIP() const {
    return _registers.__rip;
}

inline void CommonRegisters<GPRs_x86_64>::setIP(GPRs_x86_64::reg_t val) {
    _registers.__rip = val;
}

#endif //UNWIND_X86_64_REGISTERS_H
