cmake_minimum_required(VERSION 2.8)

project(KiwiOS)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_LINKER "/usr/bin/ld")

include_directories(include)

file(GLOB_RECURSE KiwiOS_SOURCES src/*.c src/*.s)

set(CMAKE_C_FLAGS "-m32 -nostdlib -nostartfiles -nostdinc -fno-builtin -fno-stack-protector")

add_executable(kiwios-kernel ${KiwiOS_SOURCES})
set_target_properties(kiwios-kernel PROPERTIES LINK_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel.ld -m elf_i386 -Map ${CMAKE_CURRENT_SOURCE_DIR}/kernel.map")
