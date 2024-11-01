module top (
    input logic clk,
    input logic rst,
    input logic trigger,
    output logic [7:0] data_out,
);

logic tick;
logic time_out;
logic cmd_seq;
logic cmd_delay;
logic [6:0] delay_time;
logic fsm_en;

always_comb
    fsm_en = cmd_seq ? tick : time_out;

clktick clktick (
    .clk(clk),
    .rst(rst),
    .en(cmd_seq),
    .N(16'd32),
    .tick(tick)
);

delay #(
    .WIDTH(7)
) delay (
    .clk(clk),
    .rst(rst),
    .trigger(cmd_delay),
    .n(delay_time),
    .time_out(time_out)
);

lfsr_7 lfsr (
    .clk(clk),
    .rst(rst),
    .data_out(delay_time)
);

f1_fsm fsm (
    .clk(clk),
    .rst(rst),
    .en(fsm_en),
    .trigger(trigger),
    .data_out(data_out),
    .cmd_seq(cmd_seq),
    .cmd_delay(cmd_delay)
);

endmodule: top
