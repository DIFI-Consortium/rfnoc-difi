//
// Copyright 2022 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// Module: rfnoc_block_difi_basic
//
// Description:
//
//   <Add block description here>
//
// Parameters:
//
//   THIS_PORTID : Control crossbar port to which this block is connected
//   CHDR_W      : AXIS-CHDR data bus width
//   MTU         : Maximum transmission unit (i.e., maximum packet size in
//                 CHDR words is 2**MTU).
//

`default_nettype none


module rfnoc_block_difi_basic #(
  parameter [9:0] THIS_PORTID     = 10'd0,
  parameter       CHDR_W          = 64,
  parameter [5:0] MTU             = 10
)(
  // RFNoC Framework Clocks and Resets
  input  wire                   rfnoc_chdr_clk,
  input  wire                   rfnoc_ctrl_clk,
  // RFNoC Backend Interface
  input  wire [511:0]           rfnoc_core_config,
  output wire [511:0]           rfnoc_core_status,
  // AXIS-CHDR Input Ports (from framework)
  input  wire [(1)*CHDR_W-1:0] s_rfnoc_chdr_tdata,
  input  wire [(1)-1:0]        s_rfnoc_chdr_tlast,
  input  wire [(1)-1:0]        s_rfnoc_chdr_tvalid,
  output wire [(1)-1:0]        s_rfnoc_chdr_tready,
  // AXIS-CHDR Output Ports (to framework)
  output wire [(1)*CHDR_W-1:0] m_rfnoc_chdr_tdata,
  output wire [(1)-1:0]        m_rfnoc_chdr_tlast,
  output wire [(1)-1:0]        m_rfnoc_chdr_tvalid,
  input  wire [(1)-1:0]        m_rfnoc_chdr_tready,
  // AXIS-Ctrl Input Port (from framework)
  input  wire [31:0]            s_rfnoc_ctrl_tdata,
  input  wire                   s_rfnoc_ctrl_tlast,
  input  wire                   s_rfnoc_ctrl_tvalid,
  output wire                   s_rfnoc_ctrl_tready,
  // AXIS-Ctrl Output Port (to framework)
  output wire [31:0]            m_rfnoc_ctrl_tdata,
  output wire                   m_rfnoc_ctrl_tlast,
  output wire                   m_rfnoc_ctrl_tvalid,
  input  wire                   m_rfnoc_ctrl_tready
);

  //---------------------------------------------------------------------------
  // Signal Declarations
  //---------------------------------------------------------------------------

  // Clocks and Resets
  wire               ctrlport_clk;
  wire               ctrlport_rst;
  wire               axis_data_clk;
  wire               axis_data_rst;
  // CtrlPort Master
  wire               m_ctrlport_req_wr;
  wire               m_ctrlport_req_rd;
  wire [19:0]        m_ctrlport_req_addr;
  wire [31:0]        m_ctrlport_req_data;
  wire               m_ctrlport_resp_ack;
  wire [31:0]        m_ctrlport_resp_data;
  // Payload Stream to User Logic: in
  wire [32*1-1:0]    m_in_payload_tdata;
  wire [1-1:0]       m_in_payload_tkeep;
  wire               m_in_payload_tlast;
  wire               m_in_payload_tvalid;
  wire               m_in_payload_tready;
  // Context Stream to User Logic: in
  wire [CHDR_W-1:0]  m_in_context_tdata;
  wire [3:0]         m_in_context_tuser;
  wire               m_in_context_tlast;
  wire               m_in_context_tvalid;
  wire               m_in_context_tready;
  // Payload Stream from User Logic: out
  wire [32*1-1:0]    s_out_payload_tdata;
  wire [0:0]         s_out_payload_tkeep;
  wire               s_out_payload_tlast;
  wire               s_out_payload_tvalid;
  wire               s_out_payload_tready;
  // Context Stream from User Logic: out
  wire [CHDR_W-1:0]  s_out_context_tdata;
  wire [3:0]         s_out_context_tuser;
  wire               s_out_context_tlast;
  wire               s_out_context_tvalid;
  wire               s_out_context_tready;

  //---------------------------------------------------------------------------
  // NoC Shell
  //---------------------------------------------------------------------------

  noc_shell_difi_basic #(
    .CHDR_W              (CHDR_W),
    .THIS_PORTID         (THIS_PORTID),
    .MTU                 (MTU)
  ) noc_shell_difi_basic_i (
    //---------------------
    // Framework Interface
    //---------------------

    // Clock Inputs
    .rfnoc_chdr_clk      (rfnoc_chdr_clk),
    .rfnoc_ctrl_clk      (rfnoc_ctrl_clk),
    // Reset Outputs
    .rfnoc_chdr_rst      (),
    .rfnoc_ctrl_rst      (),
    // RFNoC Backend Interface
    .rfnoc_core_config   (rfnoc_core_config),
    .rfnoc_core_status   (rfnoc_core_status),
    // CHDR Input Ports  (from framework)
    .s_rfnoc_chdr_tdata  (s_rfnoc_chdr_tdata),
    .s_rfnoc_chdr_tlast  (s_rfnoc_chdr_tlast),
    .s_rfnoc_chdr_tvalid (s_rfnoc_chdr_tvalid),
    .s_rfnoc_chdr_tready (s_rfnoc_chdr_tready),
    // CHDR Output Ports (to framework)
    .m_rfnoc_chdr_tdata  (m_rfnoc_chdr_tdata),
    .m_rfnoc_chdr_tlast  (m_rfnoc_chdr_tlast),
    .m_rfnoc_chdr_tvalid (m_rfnoc_chdr_tvalid),
    .m_rfnoc_chdr_tready (m_rfnoc_chdr_tready),
    // AXIS-Ctrl Input Port (from framework)
    .s_rfnoc_ctrl_tdata  (s_rfnoc_ctrl_tdata),
    .s_rfnoc_ctrl_tlast  (s_rfnoc_ctrl_tlast),
    .s_rfnoc_ctrl_tvalid (s_rfnoc_ctrl_tvalid),
    .s_rfnoc_ctrl_tready (s_rfnoc_ctrl_tready),
    // AXIS-Ctrl Output Port (to framework)
    .m_rfnoc_ctrl_tdata  (m_rfnoc_ctrl_tdata),
    .m_rfnoc_ctrl_tlast  (m_rfnoc_ctrl_tlast),
    .m_rfnoc_ctrl_tvalid (m_rfnoc_ctrl_tvalid),
    .m_rfnoc_ctrl_tready (m_rfnoc_ctrl_tready),

    //---------------------
    // Client Interface
    //---------------------

    // CtrlPort Clock and Reset
    .ctrlport_clk              (ctrlport_clk),
    .ctrlport_rst              (ctrlport_rst),
    // CtrlPort Master
    .m_ctrlport_req_wr         (m_ctrlport_req_wr),
    .m_ctrlport_req_rd         (m_ctrlport_req_rd),
    .m_ctrlport_req_addr       (m_ctrlport_req_addr),
    .m_ctrlport_req_data       (m_ctrlport_req_data),
    .m_ctrlport_resp_ack       (m_ctrlport_resp_ack),
    .m_ctrlport_resp_data      (m_ctrlport_resp_data),

    // AXI-Stream Payload Context Clock and Reset
    .axis_data_clk (axis_data_clk),
    .axis_data_rst (axis_data_rst),
    // Payload Stream to User Logic: in
    .m_in_payload_tdata  (m_in_payload_tdata),
    .m_in_payload_tkeep  (m_in_payload_tkeep),
    .m_in_payload_tlast  (m_in_payload_tlast),
    .m_in_payload_tvalid (m_in_payload_tvalid),
    .m_in_payload_tready (m_in_payload_tready),
    // Context Stream to User Logic: in
    .m_in_context_tdata  (m_in_context_tdata),
    .m_in_context_tuser  (m_in_context_tuser),
    .m_in_context_tlast  (m_in_context_tlast),
    .m_in_context_tvalid (m_in_context_tvalid),
    .m_in_context_tready (m_in_context_tready),
    // Payload Stream from User Logic: out
    .s_out_payload_tdata  (s_out_payload_tdata),
    .s_out_payload_tkeep  (s_out_payload_tkeep),
    .s_out_payload_tlast  (s_out_payload_tlast),
    .s_out_payload_tvalid (s_out_payload_tvalid),
    .s_out_payload_tready (s_out_payload_tready),
    // Context Stream from User Logic: out
    .s_out_context_tdata  (s_out_context_tdata),
    .s_out_context_tuser  (s_out_context_tuser),
    .s_out_context_tlast  (s_out_context_tlast),
    .s_out_context_tvalid (s_out_context_tvalid),
    .s_out_context_tready (s_out_context_tready)
  );

  //---------------------------------------------------------------------------
  // User Logic
  //---------------------------------------------------------------------------

  `define RFNOC_CHDR_UTILS_PATH `"`UHD_FPGA_DIR/usrp3/lib/rfnoc/core/rfnoc_chdr_utils.vh`"
  `include `RFNOC_CHDR_UTILS_PATH

  // Logic --------------------------------------------------------------------

  // Calculated Fields from CHDR
  reg [1:0] difi_tsi = 2'b01;
  reg [31:0] difi_streamid = 32'h88888888;
  reg [15:0] difi_packet_size = 0;
  reg [3:0] difi_seqnum = 0;
  reg [23:0] difi_oui = 24'h123456;
  reg [15:0] difi_icc = 16'hdead;
  reg [15:0] difi_pcc = 16'hbeef;
  wire [31:0] difi_int_timestamp = 32'h66666666;
  reg [63:0] difi_frac_timestamp = 64'hf0f0f0f00f0f0f0f;

  // Update CHDR header with new bytes
  wire [CHDR_W-1:0] updated_header;
  assign updated_header = chdr_set_length(m_in_context_tdata, chdr_get_length(m_in_context_tdata) + 28);

  // Snag SeqNum
  wire [15:0] chdr_seqnum;
  assign chdr_seqnum = chdr_get_seq_num(m_in_context_tdata);

  // Nothing to do yet, so just drive control signals to default values
  assign m_ctrlport_resp_ack = 1'b0;


  // Calculate the DIFI packet size from the CHDR packet size
  wire [15:0] chdr_timestamp_and_metadata_bytes;
  assign chdr_timestamp_and_metadata_bytes = (chdr_get_has_time(m_in_context_tdata) ? 8 : 0) + (chdr_get_num_mdata(m_in_context_tdata) << 3);
  wire [15:0] calc_difi_packet_size;
  assign calc_difi_packet_size = (chdr_get_length(m_in_context_tdata) - chdr_timestamp_and_metadata_bytes + 20) >> 2;

  function [31:0] pack_word(input [31:0] word);
    begin
      pack_word = { word[23:16], word[31:24], word[7:0], word[15:8] };
    end
  endfunction

  // State Machine ------------------------------------------------------------

  // States
  localparam DIFI_MODIFY_CHDR_ST = 4'd0;
  localparam DIFI_SEND_CONTEXT_PACKET = 4'd1;
  localparam DIFI_CHDR_TIMESTAMP_ST = 4'd2;
  localparam DIFI_PASS_CTXT_ST = 4'd3;
  localparam DIFI_ADD_HEADER_ST = 4'd4;
  localparam DIFI_ADD_STREAMID_ST = 4'd5;
  localparam DIFI_ADD_OUI_ST = 4'd6;
  localparam DIFI_ADD_ICC_PCC_ST = 4'd7;
  localparam DIFI_ADD_INT_TS_ST = 4'd8;
  localparam DIFI_ADD_FRAC_TS_MS_ST = 4'd9;
  localparam DIFI_ADD_FRAC_TS_LS_ST = 4'd10;
  localparam DIFI_PASS_PYLD_ST = 4'd11;

  reg [3:0] state = DIFI_MODIFY_CHDR_ST;

  // Transitions
  always @(posedge axis_data_clk) begin
    if (axis_data_rst) begin
      state <= DIFI_MODIFY_CHDR_ST;
    end else begin
      case(state)
        DIFI_MODIFY_CHDR_ST : begin
          if (m_in_context_tvalid && s_out_context_tready) begin
            difi_seqnum <= chdr_seqnum[3:0];
            difi_packet_size <= calc_difi_packet_size;

            if (m_in_context_tlast) begin
              state <= DIFI_ADD_HEADER_ST;
            end else begin
              if (chdr_get_has_time(m_in_context_tdata)) begin
                state <= DIFI_CHDR_TIMESTAMP_ST;
              end else begin
                state <= DIFI_PASS_CTXT_ST;
              end
            end
          end
        end
        DIFI_CHDR_TIMESTAMP_ST : begin
          if (m_in_context_tvalid && s_out_context_tready) begin
              if (m_in_context_tlast) begin
                state <= DIFI_ADD_HEADER_ST;
              end else begin
                state <= DIFI_PASS_CTXT_ST;
              end
          end
        end
        DIFI_PASS_CTXT_ST : begin
          if (m_in_context_tvalid && s_out_context_tready && m_in_context_tlast) begin
            state <= DIFI_ADD_HEADER_ST;
          end
        end
        DIFI_ADD_HEADER_ST : begin
          if (s_out_payload_tready) begin
            state <= DIFI_ADD_STREAMID_ST;
          end
        end
        DIFI_ADD_STREAMID_ST : begin
          if (s_out_payload_tready) begin
            state <= DIFI_ADD_OUI_ST;
          end
        end
        DIFI_ADD_OUI_ST : begin
          if (s_out_payload_tready) begin
            state <= DIFI_ADD_ICC_PCC_ST;
          end
        end
        DIFI_ADD_ICC_PCC_ST : begin
          if (s_out_payload_tready) begin
            state <= DIFI_ADD_INT_TS_ST;
          end
        end
        DIFI_ADD_INT_TS_ST : begin
          if (s_out_payload_tready) begin
            state <= DIFI_ADD_FRAC_TS_MS_ST;
          end
        end
        DIFI_ADD_FRAC_TS_MS_ST : begin
          if (s_out_payload_tready) begin
            state <= DIFI_ADD_FRAC_TS_LS_ST;
          end
        end
        DIFI_ADD_FRAC_TS_LS_ST : begin
          if (s_out_payload_tready) begin
            state <= DIFI_PASS_PYLD_ST;
          end
        end
        DIFI_PASS_PYLD_ST : begin
          if (m_in_payload_tvalid && s_out_payload_tready && m_in_payload_tlast) begin
            state <= DIFI_MODIFY_CHDR_ST;
          end
        end
      endcase 
    end
  end

  // Outputs

  reg [CHDR_W-1:0] out_context_tdata = 0;
  reg [3:0] out_context_tuser = 0;
  reg out_context_tlast = 0;
  reg out_context_tvalid = 0;
  reg in_context_tready = 0;
  assign s_out_context_tuser = out_context_tuser;
  assign s_out_context_tlast = out_context_tlast;
  assign s_out_context_tvalid = out_context_tvalid;
  assign s_out_context_tdata = out_context_tdata;
  assign m_in_context_tready = in_context_tready;

  reg [31:0] out_payload_tdata = 0;
  reg out_payload_tkeep = 0;
  reg out_payload_tlast = 0;
  reg out_payload_tvalid = 0;
  reg in_payload_tready = 0;
  assign s_out_payload_tdata = out_payload_tdata;
  assign s_out_payload_tkeep = out_payload_tkeep;
  assign s_out_payload_tlast = out_payload_tlast;
  assign s_out_payload_tvalid = out_payload_tvalid;
  assign m_in_payload_tready = in_payload_tready;

  always @(*) begin
    case(state)
      DIFI_MODIFY_CHDR_ST : begin
        out_context_tdata <= updated_header;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= m_in_context_tvalid;
        in_context_tready <= s_out_context_tready;

        out_payload_tdata <= 32'b0;
        out_payload_tkeep <= 1'b0;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b0;
        in_payload_tready <= 1'b0;
      end
      DIFI_CHDR_TIMESTAMP_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= m_in_context_tvalid;
        in_context_tready <= s_out_context_tready;

        out_payload_tdata <= 32'b0;
        out_payload_tkeep <= 1'b0;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b0;
        in_payload_tready <= 1'b0;
      end
      DIFI_PASS_CTXT_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= m_in_context_tvalid;
        in_context_tready <= s_out_context_tready;

        out_payload_tdata <= 32'b0;
        out_payload_tkeep <= 1'b0;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b0;
        in_payload_tready <= 1'b0;
      end
      DIFI_ADD_HEADER_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= pack_word({ 8'b00011000, difi_tsi, 2'b10, difi_seqnum, difi_packet_size });
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;
      end
      DIFI_ADD_STREAMID_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= pack_word({ difi_streamid });
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;
      end
      DIFI_ADD_OUI_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= pack_word({ 8'b00000000, difi_oui });
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;
      end
      DIFI_ADD_ICC_PCC_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= pack_word({ difi_icc, difi_pcc });
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;
      end
      DIFI_ADD_INT_TS_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= pack_word({ difi_int_timestamp });
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;
      end
      DIFI_ADD_FRAC_TS_MS_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= pack_word({ difi_frac_timestamp[63:32] });
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;
      end
      DIFI_ADD_FRAC_TS_LS_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= pack_word({ difi_frac_timestamp[31:0] });
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;
      end
      DIFI_PASS_PYLD_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= m_in_payload_tdata;
        out_payload_tkeep <= m_in_payload_tkeep;
        out_payload_tlast <= m_in_payload_tlast;
        out_payload_tvalid <= m_in_payload_tvalid;
        in_payload_tready <= s_out_payload_tready;
      end
    endcase
  end

endmodule // rfnoc_block_difi_basic


`default_nettype wire
