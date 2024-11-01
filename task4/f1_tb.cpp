//
// Created by James Conway on 01/11/2024.
//
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
#include <iostream>

int main(int argc, char **argv, char **env) {

    int simcyc;
    int tick;

    Verilated::commandArgs(argc, argv);
    Vtop *top = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("top.vcd");

    if (vbdOpen() != 1) return -1;

    vbdHeader("F1 Lights");
    vbdSetMode(1);

    top->clk = 1;
    top->rst = 1;
    top->trigger = 0;

    bool timing = false;

    for (simcyc = 0; simcyc < 10000; simcyc++) {
        vbdCycle(simcyc);
        for (tick = 0; tick < 2; tick++) {
            tfp->dump(2 * simcyc + tick);
            top->clk = !top->clk;
            top->eval();
        }

        top->trigger = vbdFlag();
        top->rst = (simcyc < 2);
        vbdBar(top->data_out & 0xFF);

        if (!timing && top->data_out == 0b11111111) {
            timing = 1;
        }
        if (top->data_out == 0 && timing){
            vbdInitWatch();
            while (timing){
                if (vbdFlag()){
                    u_int millis = vbdElapsed();
                    int idx = 1;
                    while (millis > 0) {
                        vbdHex(idx, millis % 10);
                        millis /= 10;
                        idx++;
                    }
                    while (idx <= 5) {
                        vbdHex(idx, 0);
                        idx++;
                    }
                    timing = 0;
                }
            }
        }
    }

    vbdClose();
    tfp->close();
    delete top;
    exit(0);
}
