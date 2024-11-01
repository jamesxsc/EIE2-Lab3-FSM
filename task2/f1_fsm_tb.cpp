//
// Created by eliott on 11/1/2024.
//
#include "Vf1_fsm.h"
#include "verilated.h"
#include "vbuddy.cpp"     // Include Vbuddy header
#include <iostream>

int main(int argc, char **argv, char **env) {
    Verilated::commandArgs(argc, argv);
    Vf1_fsm* top = new Vf1_fsm;  // Instantiate the FSM module

    // Initialize Vbuddy
    if (vbdOpen() != 1) return -1;
    vbdHeader("Lab FSM Test");    // Display header in Vbuddy

    top->clk = 0; // Initialize clock
    top->rst = 1; // Start with reset high
    top->en = 0;  // Initialize enable signal

    // Run simulation for a specific number of cycles
    for (int i = 0; i < 500; i++) {
        // Toggle the clock signal
        top->clk = !top->clk;
        top->eval();

        // Release reset after a few cycles
        if (i == 10) {
            top->rst = 0;
        }

        // Read the rotary switch flag to control enable
        top->en = vbdFlag(); // Use rotary switch to drive `en`

        // Display the FSM output on Vbuddy's neopixel strip
        vbdBar(top->data_out & 0xFF); // Mask data_out to 8 bits

        // Print out data for debugging (optional)
        std::cout << "Cycle: " << i << " | Data out: " << (int)top->data_out << std::endl;

        // Delay to observe changes
        vbdCycle(i); // Display cycle count in Vbuddy
    }

    // Cleanup
    vbdClose(); // Close Vbuddy
    delete top;
    return 0;
}
