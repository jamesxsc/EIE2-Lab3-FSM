module lfsr_7 (
    input   logic       clk,
    input   logic       rst,
    output  logic [6:0] data_out
);

    logic [6:0] sreg;
    always_ff @(posedge clk or posedge rst) begin
        if (rst)
            sreg <= 7'b0000001; // Initial non-zero seed value
        else begin
            sreg <= {sreg[5:0], sreg[6] ^ sreg[2]}; // Shift and XOR taps at positions 7 and 3
        end
    end

   assign data_out = sreg;

endmodule
