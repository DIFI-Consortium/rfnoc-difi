`default_nettype none

module chdr_difi_timestamp_converter (
  input wire clk,
  input wire rst,
  input wire [63:0] chdr_timestamp,
  input wire [63:0] tick_period,
  input wire i_tvalid,
  output logic i_tready,
  output logic [31:0] int_timestamp_tdata,
  output logic int_timestamp_tvalid,
  input wire int_timestamp_tready,
  output logic [63:0] frac_timestamp_tdata,
  output logic frac_timestamp_tvalid,
  input wire frac_timestamp_tready
);

  // First multiplication (for integer timestamp)

  logic [63:0] mult_1_a = 0;
  logic [63:0] mult_1_b = 0;
  logic mult_1_enable = 1;
  wire [127:0] mult_1_result;

  mult_64_64_6p_ce mult_64_64_i (
    .CLK(clk),
    .A(mult_1_a),
    .B(mult_1_b),
    .CE(mult_1_enable),
    .P(mult_1_result)
  );

  // Second multiplication (for fractional timestamp)

  logic [63:0] mult_2_a = 0;
  logic mult_2_enable = 1;
  wire [103:0] mult_2_result;

  mult_64_1e12_5p_ce mult_64_1e12_i (
    .CLK(clk),
    .A(mult_2_a),
    .CE(mult_2_enable),
    .P(mult_2_result)
  );

  logic [3:0] mult_1_counter = 0;
  logic [3:0] mult_2_counter = 0;

  enum {
    WAIT_FOR_VALID,
    MULT_1,
    MULT_2,
    FINISHED
  } state;

  // Mealy State Machine
  // This doesn't pipeline for now, should probably make it do that later
  always_ff @(posedge clk) begin : transitions
    if (rst) begin
      mult_1_counter <= 0;
      mult_2_counter <= 0;
      state <= WAIT_FOR_VALID;
      i_tready <= 1;
      int_timestamp_tdata <= 0;
      int_timestamp_tvalid <= 0;
      frac_timestamp_tdata <= 0;
      frac_timestamp_tvalid <= 0;
    end else begin
      case (state)
        WAIT_FOR_VALID : begin
          if (i_tvalid) begin
            state <= MULT_1;

            // No longer ready for a value
            i_tready <= 0;

            // Setup first multiplication
            mult_1_a <= chdr_timestamp;
            mult_1_b <= tick_period;
            mult_1_counter <= 0;
          end else begin
            i_tready <= 1;
          end
        end
        MULT_1 : begin
          if (mult_1_counter == 6) begin
            // Finished first multiplication, move to second
            state <= MULT_2;
            mult_1_counter <= 0;
            int_timestamp_tdata <= mult_1_result[95:64];
            int_timestamp_tvalid <= 1;

            // Setup second multiplication
            mult_2_counter <= 0;
            mult_2_a <= mult_1_result[63:0];
          end else begin
            // Waiting... (6 Stages)
            mult_1_counter <= mult_1_counter + 1;
          end
        end
        MULT_2 : begin
          if (mult_2_counter == 5) begin
            // Finished second multiplication, move to second
            state <= FINISHED;
            mult_2_counter <= 0;
            frac_timestamp_tdata <= mult_2_result[103:40];
            frac_timestamp_tvalid <= 1;
          end else begin
            // Waiting... (5 Stages)
            mult_2_counter <= mult_2_counter + 1;
          end
        end
        FINISHED : begin
          if (!int_timestamp_tvalid && !frac_timestamp_tvalid) begin
            // If we've passed on both values, we're ready again
            state <= WAIT_FOR_VALID;
            i_tready <= 1;
          end
        end
      endcase

      if (int_timestamp_tready && int_timestamp_tvalid) begin
        // We've passed a valid int_timestamp value
        int_timestamp_tvalid <= 0;
      end

      if (frac_timestamp_tready && frac_timestamp_tvalid) begin
        // We've passed a valid frac_timestamp value
        frac_timestamp_tvalid <= 0;
      end
    end
  end
  
endmodule

`default_nettype wire