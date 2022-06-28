//
// Created by user on 2022/6/26.
//

#ifndef UNWIND_EH_ABI_CONFIG_H
#define UNWIND_EH_ABI_CONFIG_H

#if defined(__arm__) && !defined(__ARM_DWARF_EH__)
#define _UNWIND_ARM_EHABI
#endif

#endif //UNWIND_EH_ABI_CONFIG_H
