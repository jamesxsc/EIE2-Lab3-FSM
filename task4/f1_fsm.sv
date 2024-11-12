module f1_fsm (
    input logic clk,          // Clock signal
    input logic rst,          // Reset signal
    input logic en,
    input logic trigger,
    output logic [7:0] data_out, // Output for light sequence
    output logic cmd_seq,
    output logic cmd_delay
);

    typedef enum logic [3:0] {
        S0 = 4'b0000,
        S1 = 4'b0001,
        S2 = 4'b0010,
        S3 = 4'b0011,
        S4 = 4'b0100,
        S5 = 4'b0101,
        S6 = 4'b0110,
        S7 = 4'b0111,
        S8 = 4'b1000
    } state_t;

    state_t state, next_state;

    // Output logic based on state
    always_comb begin
        case (state)
            S0: data_out = 8'b00000000;
            S1: data_out = 8'b00000001;
            S2: data_out = 8'b00000011;
            S3: data_out = 8'b00000111;
            S4: data_out = 8'b00001111;
            S5: data_out = 8'b00011111;
            S6: data_out = 8'b00111111;
            S7: data_out = 8'b01111111;
            S8: data_out = 8'b11111111;
            default: data_out = 8'b00000000;
        endcase
    end

    // Next state logic
    always_comb begin
         case (state)
             S0: next_state = (trigger) ? S1 : S0;
             S1: next_state = en ? S2 : S1;
             S2: next_state = en ? S3 : S2;
             S3: next_state = en ? S4 : S3;
             S4: next_state = en ? S5 : S4;
             S5: next_state = en ? S6 : S5;
             S6: next_state = en ? S7 : S6;
             S7: next_state = en ? S8 : S7;
             S8: next_state = en ? S0 : S8;
             default: next_state = S0;
         endcase
    end

    // State transition on clock edge
    always_ff @(posedge clk) begin
        if (rst)
            state <= S0;
        else
            state <= next_state;
    end

    assign cmd_delay = (state == S8);
    assign cmd_seq = (!cmd_delay && state != S0);
endmodule

