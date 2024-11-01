module lfsr_7 (
    input   logic       clk,
    input   logic       rst,
    input   logic       en,
    output  logic [6:0] data_out

);
    logic [6:0] sreg;
    always_ff @(posedge clk or posedge reset) begin
        if (reset)
            prbs <= 7'b0000001; // Initial non-zero seed value
        else begin
            prbs <= {prbs[5:0], prbs[6] ^ prbs[2]}; // Shift and XOR taps at positions 7 and 3
        end
    end


endmodule