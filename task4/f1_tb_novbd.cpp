#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>

int main(int argc, char **argv, char **env) {
    int simcyc;
    int tick;

    Verilated::commandArgs(argc, argv);
    Vtop *top = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);

    top->clk = 1;
    top->rst = 1;
    top->trigger = 0;

    // This is a basic implementation omitting the timer logic

    for (simcyc = 0; simcyc < 10000; simcyc++) {
        for (tick = 0; tick < 2; tick++) {
            tfp->dump(2 * simcyc + tick);
            top->clk = !top->clk;
            top->eval();
        }

        top->rst = (simcyc < 2) || (simcyc % 1000 == 0);
    }

    tfp->close();
    delete top;
    delete tfp;
    exit(0);
}
