
module lfsr4 (
    input logic        clk,        // clock
    input logic        rst,        // reset
    input   logic       en,
    output logic [4:1] data_out    // pseudo-random output
);

    always_ff @ (posedge clk, posedge rst)
        if (rst)
            sreg <= 4'b1;
        else if (en)
            sreg <= {sreg[3:1], sreg[4] ^ sreg[3]};
        else
            sreg<=sreg;

    assign data_out = sreg;
endmodule