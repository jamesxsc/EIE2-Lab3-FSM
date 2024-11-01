cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)
project(lab3_task1)

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})

if (NOT verilator_FOUND)
    message(FATAL_ERROR "Verilator not found!")
endif()

add_executable(lfsr ./verify.cpp)
target_compile_features(lfsr PRIVATE cxx_std_17)

verilate(lfsr TRACE
        VERILATOR_ARGS -Wall
        SOURCES ./lfsr.sv
        --prefix Vdut
        -CFLAGS "-isystem /opt/homebrew/Cellar/googletest/1.15.2/include"
        -LDFLAGS "-L/opt/homebrew/Cellar/googletest/1.15.2/lib -lgtest -lgtest_main -lpthread"
)

