//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_LOCAL_ADDRESS_SPACE_H
#define UNWIND_LOCAL_ADDRESS_SPACE_H

#include "eh_abi_config.h"
#include "arch/common_registers.h"

#include "stdint.h"
#include "stddef.h"

#if defined(_UNWIND_ARM_EHABI)
struct EHABIIndexEntry {
  uint32_t functionOffset;
  uint32_t data;
};
#endif

// When statically linked on bare-metal, the symbols for the EH table are looked
// up without going through the dynamic loader.

// The following linker script may be used to produce the necessary sections and symbols.
// Unless the --eh-frame-hdr linker option is provided, the section is not generated
// and does not take space in the output file.
//
//   .eh_frame :
//   {
//       __eh_frame_start = .;
//       KEEP(*(.eh_frame))
//       __eh_frame_end = .;
//   }
//
//   .eh_frame_hdr :
//   {
//       KEEP(*(.eh_frame_hdr))
//   }
//
//   __eh_frame_hdr_start = SIZEOF(.eh_frame_hdr) > 0 ? ADDR(.eh_frame_hdr) : 0;
//   __eh_frame_hdr_end = SIZEOF(.eh_frame_hdr) > 0 ? . : 0;


#if defined(_UNWIND_ARM_EHABI)
// When statically linked on bare-metal, the symbols for the EH table are looked
// up without going through the dynamic loader.
extern char __exidx_start;
extern char __exidx_end;
#else
extern char __eh_frame_start;
extern char __eh_frame_end;
extern char __eh_frame_hdr_start;
extern char __eh_frame_hdr_end;
#endif


struct UnwindSectionInfo {
#if defined(_UNWIND_ARM_EHABI)
    uintptr_t arm_section;
    size_t arm_section_length;
#else
    uintptr_t dso_base; // todo 这个目前不知道有啥用
    uintptr_t dwarf_section;
    size_t dwarf_section_length;
    uintptr_t dwarf_index_section;
    size_t dwarf_index_section_length;
#endif
};

class LocalAddressSpace {
public:
    uint8_t get8(uintptr_t addr);
    uint16_t get16(uintptr_t addr);
    uint32_t get32(uintptr_t addr);
    uint64_t get64(uintptr_t addr);
    double getDouble(uintptr_t addr);
    v128 getVector(uintptr_t addr);

    uintptr_t getPointer(uintptr_t addr);
    uint64_t getRegister(uintptr_t addr);

    static uint64_t getULEB128(uintptr_t &start, uintptr_t end);
    static int64_t getSLEB128(uintptr_t &start, uintptr_t end);

    uintptr_t getEncodingPointer(uintptr_t &start,
                                 uintptr_t end,
                                 uint8_t encoding,
                                 uintptr_t dataRelBase = 0);

    bool findUnwindSection(UnwindSectionInfo &info);

    static LocalAddressSpace localAddressSpace;
};


#endif //UNWIND_LOCAL_ADDRESS_SPACE_H
