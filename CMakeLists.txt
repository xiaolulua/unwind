cmake_minimum_required(VERSION 3.22)
project(unwind)

set(CMAKE_CXX_STANDARD 98)

include_directories(include)

add_library(unwind library.cpp include/eh_abi_config.h include/registers.h include/arch/x86_registers.h include/arch/x86_64_registers.h include/arch/arm_registers.h include/arch/aarch64_registers.h include/local_address_space.h include/dwarf5.h include/arch/common_registers.h include/arch/riscv_registers.h src/local_address_space.cpp include/arch/assembly.h src/arch/CommonRegisterRestore.S src/arch/CommonRegisterSave.S include/dwarf_parser.h)
