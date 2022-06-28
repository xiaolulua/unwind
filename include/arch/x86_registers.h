//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_X86_REGISTERS_H
#define UNWIND_X86_REGISTERS_H

#include "common_registers.h"

#include <string.h>

#define _UNWIND_TARGET_I386

// 32-bit x86 registers
enum {
    UNW_X86_EAX = 0,
    UNW_X86_ECX = 1,
    UNW_X86_EDX = 2,
    UNW_X86_EBX = 3,
    UNW_X86_ESP = 4,
    UNW_X86_EBP = 5,
    UNW_X86_ESI = 6,
    UNW_X86_EDI = 7,
};

struct GPRs_x86 {
    typedef uint32_t reg_t;

    GPRs_x86():__eax(0), __ebx(0), __ecx(0), __edx(0), __edi(0), __esi(0),
                __ebp(0), __esp(0), __ss(0), __eflags(0), __eip(0), __cs(0),
                __ds(0), __es(0), __fs(0), __gs(0){}

    explicit GPRs_x86(const void * registers){
        memcpy(this,registers,sizeof(GPRs_x86));
    }

    reg_t __eax;
    reg_t __ebx;
    reg_t __ecx;
    reg_t __edx;
    reg_t __edi;
    reg_t __esi;
    reg_t __ebp;
    reg_t __esp;
    reg_t __ss;
    reg_t __eflags;
    reg_t __eip;
    reg_t __cs;
    reg_t __ds;
    reg_t __es;
    reg_t __fs;
    reg_t __gs;
};

template<>
class  CommonRegisters<GPRs_x86>;

extern "C" void __load_registers_x86(CommonRegisters<GPRs_x86> *);

template<>
class CommonRegisters<GPRs_x86> {
public:
    CommonRegisters();
    explicit CommonRegisters(const void * registers);

    static bool validRegister(int regId);
    GPRs_x86::reg_t getRegister(int regId) const;
    void setRegister(int regId, GPRs_x86::reg_t val);

    static const char * getRegisterName(int regId);
    void jumpTo();
    static int lastDwarfRegNum();
    static int getArch();

    GPRs_x86::reg_t getSP() const;
    void setSP(GPRs_x86::reg_t val);

    GPRs_x86::reg_t getIP() const;
    void setIP(GPRs_x86::reg_t val);

private:
    GPRs_x86 _registers;
};

inline CommonRegisters<GPRs_x86>::CommonRegisters():_registers() {}

inline CommonRegisters<GPRs_x86>::CommonRegisters(const void *registers): _registers(registers) {}

inline bool CommonRegisters<GPRs_x86>::validRegister(int regId) {
    if (regId == UNW_REG_IP)
        return true;
    if (regId == UNW_REG_SP)
        return true;
    if (regId < UNW_X86_EAX)
        return false;
    if (regId > UNW_X86_EDI)
        return false;
    return true;
}

inline GPRs_x86::reg_t CommonRegisters<GPRs_x86>::getRegister(int regId) const {
    switch (regId) {
        case UNW_REG_IP:
            return _registers.__eip;
        case UNW_REG_SP:
        case UNW_X86_ESP:
            return _registers.__esp;
        case UNW_X86_EAX:
            return _registers.__eax;
        case UNW_X86_ECX:
            return _registers.__ecx;
        case UNW_X86_EDX:
            return _registers.__edx;
        case UNW_X86_EBX:
            return _registers.__ebx;
        case UNW_X86_EBP:
            return _registers.__ebp;
        case UNW_X86_ESI:
            return _registers.__esi;
        case UNW_X86_EDI:
            return _registers.__edi;
        default:
            //todo 此处应该终止运行
            break;
    }
}

inline void CommonRegisters<GPRs_x86>::setRegister(int regId, GPRs_x86::reg_t val) {
    switch (regId) {
        case UNW_REG_IP:
            _registers.__eip = val;
            return;
        case UNW_REG_SP:
        case UNW_X86_ESP:
            _registers.__esp = val;
            return;
        case UNW_X86_EAX:
            _registers.__eax = val;
            return;
        case UNW_X86_ECX:
            _registers.__ecx = val;
            return;
        case UNW_X86_EDX:
            _registers.__edx = val;
            return;
        case UNW_X86_EBX:
            _registers.__ebx = val;
            return;
        case UNW_X86_EBP:
            _registers.__ebp = val;
            return;
        case UNW_X86_ESI:
            _registers.__esi = val;
            return;
        case UNW_X86_EDI:
            _registers.__edi = val;
            return;
        default:
            //todo 此处应该终止运行
            return;
    }
}

inline const char *CommonRegisters<GPRs_x86>::getRegisterName(int regId) {
    switch (regId) {
        case UNW_REG_IP:
            return "ip";
        case UNW_REG_SP:
        case UNW_X86_ESP:
            return "esp";
        case UNW_X86_EAX:
            return "eax";
        case UNW_X86_ECX:
            return "ecx";
        case UNW_X86_EDX:
            return "edx";
        case UNW_X86_EBX:
            return "ebx";
        case UNW_X86_EBP:
            return "ebp";
        case UNW_X86_ESI:
            return "esi";
        case UNW_X86_EDI:
            return "edi";
        default:
            //todo 此处应该终止运行
            break;
    }
}

inline void CommonRegisters<GPRs_x86>::jumpTo() {
    __load_registers_x86(this);
}

inline int CommonRegisters<GPRs_x86>::lastDwarfRegNum() {
    //todo 等待实现
}

inline int CommonRegisters<GPRs_x86>::getArch() {
    return ARCH_X86;
}

inline GPRs_x86::reg_t CommonRegisters<GPRs_x86>::getSP() const {
    return _registers.__esp;
}

inline void CommonRegisters<GPRs_x86>::setSP(GPRs_x86::reg_t val) {
    _registers.__esp = val;
}

inline GPRs_x86::reg_t CommonRegisters<GPRs_x86>::getIP() const {
    return _registers.__eip;
}

inline void CommonRegisters<GPRs_x86>::setIP(GPRs_x86::reg_t val) {
    _registers.__eip = val;
}

#endif //UNWIND_X86_REGISTERS_H
