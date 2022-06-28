//
// Created by user on 2022/6/26.
//

#include "dwarf5.h"
#include "local_address_space.h"

inline uint8_t LocalAddressSpace::get8(uintptr_t addr) {
    uint8_t val = *reinterpret_cast<uint8_t *>(addr);
    return val;
}

inline uint16_t LocalAddressSpace::get16(uintptr_t addr) {
    uint16_t val = *reinterpret_cast<uint16_t *>(addr);
    return val;
}

inline uint32_t LocalAddressSpace::get32(uintptr_t addr) {
    uint32_t val = *reinterpret_cast<uint32_t *>(addr);
    return val;
}

inline uint64_t LocalAddressSpace::get64(uintptr_t addr) {
    uint64_t val = *reinterpret_cast<uint64_t *>(addr);
    return val;
}

inline double LocalAddressSpace::getDouble(uintptr_t addr) {
    double val = *reinterpret_cast<double *>(addr);
    return val;
}

inline v128 LocalAddressSpace::getVector(uintptr_t addr) {
    v128 val = *reinterpret_cast<v128 *>(addr);
    return val;
}

inline uintptr_t LocalAddressSpace::getPointer(uintptr_t addr) {
#if __SIZEOF_POINTER__ == 8
    return get64(addr);
#else
    return get32(addr);
#endif
}

inline uint64_t LocalAddressSpace::getRegister(uintptr_t addr) {
#if __SIZEOF_POINTER__ == 8
    return get64(addr);
#else
    return get32(addr);
#endif
}

inline uint64_t LocalAddressSpace::getULEB128(uintptr_t &start, uintptr_t end) {
    const uint8_t *pStart = reinterpret_cast<uint8_t *>(start);
    const uint8_t *pEnd = reinterpret_cast<uint8_t *>(end);
    uint64_t low7bit;
    uint64_t result = 0;
    int bit = 0;

    do {
        if (pStart == pEnd) {
            // todo 如果还有data需要decode就继续解码，一旦解码失败就立即退出
            // todo 所以每次都需要检查
            // todo ULEB128 格式不合法，直接退出
        }

        low7bit = *pStart & 0x7F;

        if (bit >= 64 || low7bit << bit >> bit != low7bit) {
            // todo 超过64位限制 或者 64个bit位剩余位数容纳不了最后7位，直接退出
        }

        result |= low7bit << bit;
        bit += 7;
    } while (*pStart++ & 0x80);

    start = reinterpret_cast<uintptr_t>(pStart);
    return result;
}

inline int64_t LocalAddressSpace::getSLEB128(uintptr_t &start, uintptr_t end) {
    const uint8_t *pStart = reinterpret_cast<uint8_t *>(start);
    const uint8_t *pEnd = reinterpret_cast<uint8_t *>(end);
    uint64_t low7bit;
    int64_t result = 0;
    uint8_t byte;
    int bit = 0;

    do {
        if (pStart == pEnd) {
            // todo ULEB128 格式不合法，直接退出
        }

        byte = *pStart++;
        low7bit = byte & 0x7F;

        if (bit >= 64 || low7bit << bit >> bit != low7bit) {
            // todo 超过64位限制 或者 64个bit位剩余位数容纳不了最后7位，直接退出
        }

        result |= static_cast<int64_t>(low7bit << bit);
        bit += 7;
    } while (byte & 0x80);

    if (byte & 0x40) {
        result |= static_cast<int64_t>((-1ULL) << bit);
    }

    start = reinterpret_cast<uintptr_t>(pStart);
    return result;
}

inline uintptr_t LocalAddressSpace::getEncodingPointer(uintptr_t &start,
                                                       uintptr_t end,
                                                       uint8_t encoding,
                                                       uintptr_t dataRelBase) {
    const uintptr_t startAddr = start;
    const uint8_t *pos = reinterpret_cast<uint8_t *>(start);
    uintptr_t result;

    // first get value
    switch (encoding & 0x0F) {
        case DW_EH_PE_absptr:
            result = getPointer(start);
            pos += sizeof(uintptr_t);
            start = reinterpret_cast<uintptr_t>(pos);
            break;
        case DW_EH_PE_uleb128:
            result = getULEB128(start, end);
            break;
        case DW_EH_PE_udata2:
            result = get16(start);
            pos += 2;
            start = reinterpret_cast<uintptr_t>(pos);
            break;
        case DW_EH_PE_udata4:
            result = get32(start);
            pos += 4;
            start = reinterpret_cast<uintptr_t>(pos);
            break;
        case DW_EH_PE_udata8:
            result = get64(start);
            pos += 8;
            start = reinterpret_cast<uintptr_t>(pos);
            break;
        case DW_EH_PE_sleb128:
            result = static_cast<uintptr_t>(getSLEB128(start, end));
            break;
        case DW_EH_PE_sdata2:
            // Sign extend from signed 16-bit value.
            // 64 位中的 uintptr_t 的字节宽度 比 int16_t 的宽度大，所以int16_t转换到uintptr_t时需要对符号位进行宽度扩展
            result = static_cast<uintptr_t>(static_cast<int16_t>(get16(start)));
            pos += 2;
            start = reinterpret_cast<uintptr_t>(pos);
            break;
        case DW_EH_PE_sdata4:
            // Sign extend from signed 32-bit value.
            // 64 位中的 uintptr_t 的字节宽度 比 int32_t 的宽度大，所以int32_t转换到uintptr_t时需要对符号位进行宽度扩展
            result = static_cast<uintptr_t>(static_cast<int32_t>(get32(start)));
            pos += 4;
            start = reinterpret_cast<uintptr_t>(pos);
            break;
        case DW_EH_PE_sdata8:
            result = static_cast<uintptr_t>(static_cast<int64_t>(get64(start)));
            pos += 8;
            start = reinterpret_cast<uintptr_t>(pos);
            break;
        default:
            // todo 此处遇到不支持的value类型 应该退出程序
            break;
    }

    // then add relative offset
    switch (encoding & 0x70) {
        case DW_EH_PE_absptr:
            //do nothing
            break;
        case DW_EH_PE_pcrel:
            result += startAddr;
            break;
        case DW_EH_PE_textrel:
            // todo 遇到不支持类型的偏移地址， 应该退出程序
            break;
        case DW_EH_PE_datarel:
            // DW_EH_PE_datarel is only valid in a few places, so the parameter has a
            // default value of 0, and we abort in the event that someone calls this
            // function with a datarelBase of 0 and DW_EH_PE_datarel encoding.
            if (dataRelBase == 0) {
                // todo 此处不支持，应该退出程序
            }
            result += dataRelBase;
            break;
        case DW_EH_PE_funcrel:
            // todo 此处不支持，应该退出程序
            break;
        case DW_EH_PE_aligned:
            // todo 此处不支持，应该退出程序
            break;
        default:
            // todo 此处不支持，应该退出程序
            break;
    }

    if (encoding & DW_EH_PE_indirect) {
        result = getPointer(result);
    }

    return result;
}

inline bool LocalAddressSpace::findUnwindSection(UnwindSectionInfo &info) {
#if defined(_UNWIND_ARM_EHABI)
    info.arm_section =        (uintptr_t)(&__exidx_start);
    info.arm_section_length = (size_t)(&__exidx_end - &__exidx_start);
    if (info.arm_section && info.arm_section_length)
        return true;
#else
    info.dso_base = 0;
    info.dwarf_section = (uintptr_t) (&__eh_frame_start);
    info.dwarf_section_length = (size_t) (&__eh_frame_end - &__eh_frame_start);
    info.dwarf_index_section = (uintptr_t) (&__eh_frame_hdr_start);
    info.dwarf_index_section_length = (size_t) (&__eh_frame_hdr_end - &__eh_frame_hdr_start);
    if (info.dwarf_section_length)
        return true;
#endif

    return false;
}