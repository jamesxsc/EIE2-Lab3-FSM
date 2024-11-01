#!/bin/bash

rm -rf obj_dir/

# Translate Verilog -> C++ including testbench
verilator   -Wall --trace \
            -cc f1_fsm.sv \
            --exe f1_fsm_tb.cpp \
            --prefix "Vdut" \
            -o Vdut \

# Build C++ project with automatically generated Makefile
make -j -C obj_dir/ -f Vdut.mk

# Run executable simulation file
./obj_dir/Vdut
    