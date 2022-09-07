//
// Copyright 2022 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// Module: rfnoc_block_difi
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


module rfnoc_block_difi #(
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
  reg                m_ctrlport_resp_ack;
  reg  [31:0]        m_ctrlport_resp_data;
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

  noc_shell_difi #(
    .CHDR_W              (CHDR_W),
    .THIS_PORTID         (THIS_PORTID),
    .MTU                 (MTU)
  ) noc_shell_difi_i (
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

  // Registers ----------------------------------------------------------------
  
  `include "rfnoc_difi_regs.vh"

  // Register list
  reg [1:0] difi_tsi = REG_DIFI_TSI_DEFAULT;
  reg [31:0] difi_streamid = REG_DIFI_STREAMID_DEFAULT;
  reg [23:0] difi_oui = REG_DIFI_OUI_DEFAULT;
  reg [15:0] difi_icc = REG_DIFI_ICC_DEFAULT;
  reg [15:0] difi_pcc = REG_DIFI_PCC_DEFAULT;
  reg [63:0] tick_period = REG_DIFI_TICK_PERIOD_DEFAULT;
  reg [31:0] standard_context_packet_payload [26:0];
  integer i;

  // Register reading/writing
  always @(posedge ctrlport_clk) begin
    if (ctrlport_rst) begin
      difi_tsi <= REG_DIFI_TSI_DEFAULT;
      difi_streamid <= REG_DIFI_STREAMID_DEFAULT;
      difi_oui <= REG_DIFI_OUI_DEFAULT;
      difi_icc <= REG_DIFI_ICC_DEFAULT;
      difi_pcc <= REG_DIFI_PCC_DEFAULT;
      tick_period = REG_DIFI_TICK_PERIOD_DEFAULT;
      standard_context_packet_payload[0] = REG_DIFI_STANDARD_CONTEXT_DEFAULT_HEADER;
      for (i = 1; i < 27; i = i + 1) begin
        standard_context_packet_payload[i] = 0;
      end
    end else begin
      m_ctrlport_resp_ack <= 0; // Default assignment

      // Handle read requests
      if (m_ctrlport_req_rd) begin
        if (m_ctrlport_req_addr < REG_DIFI_STANDARD_CONTEXT_ADDR) begin
          case (m_ctrlport_req_addr)
            REG_DIFI_TSI_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              m_ctrlport_resp_data <= { 30'b0, difi_tsi };
            end
            REG_DIFI_STREAMID_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              m_ctrlport_resp_data <= { difi_streamid };
            end
            REG_DIFI_OUI_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              m_ctrlport_resp_data <= { 8'b0, difi_oui };
            end
            REG_DIFI_ICC_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              m_ctrlport_resp_data <= { 16'b0, difi_icc };
            end
            REG_DIFI_PCC_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              m_ctrlport_resp_data <= { 16'b0, difi_pcc };
            end
            REG_DIFI_TICK_PERIOD_MS_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              m_ctrlport_resp_data <= { tick_period[63:32] };
            end
            REG_DIFI_TICK_PERIOD_LS_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              m_ctrlport_resp_data <= { tick_period[31:0] };
            end
          endcase
        end else begin
          m_ctrlport_resp_ack <= 1;
          m_ctrlport_resp_data <= { standard_context_packet_payload[m_ctrlport_req_addr] };
        end
      end

      // Handle write requests
      if (m_ctrlport_req_wr) begin
        if (m_ctrlport_req_addr < REG_DIFI_STANDARD_CONTEXT_ADDR) begin
          case (m_ctrlport_req_addr)
            REG_DIFI_TSI_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              difi_tsi <= m_ctrlport_req_data[1:0];
            end
            REG_DIFI_STREAMID_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              difi_streamid <= m_ctrlport_req_data;
            end
            REG_DIFI_OUI_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              difi_oui <= m_ctrlport_req_data[23:0];
            end
            REG_DIFI_ICC_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              difi_icc <= m_ctrlport_req_data[15:0];
            end
            REG_DIFI_PCC_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              difi_pcc <= m_ctrlport_req_data[15:0];
            end
            REG_DIFI_TICK_PERIOD_MS_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              tick_period[63:32] <= m_ctrlport_req_data;
            end
            REG_DIFI_TICK_PERIOD_LS_ADDR : begin
              m_ctrlport_resp_ack <= 1;
              tick_period[31:0] <= m_ctrlport_req_data;
            end
          endcase
        end else begin
          m_ctrlport_resp_ack <= 1;
          standard_context_packet_payload[m_ctrlport_req_addr] <= m_ctrlport_resp_data;
        end
      end
    end
  end

  // Logic --------------------------------------------------------------------

  // Calculated Fields from CHDR
  reg [3:0] difi_seqnum = 0;
  reg [15:0] difi_packet_size = 0;
  wire [31:0] difi_int_timestamp;
  reg [63:0] difi_frac_timestamp = 0;

  // Update CHDR header with new bytes
  wire [CHDR_W-1:0] updated_header;
  assign updated_header = chdr_set_length(m_in_context_tdata, chdr_get_length(m_in_context_tdata) + 28);

  // Or for context packets, let's edit it a bit
  wire [CHDR_W-1:0] chdr_context_header;
  assign chdr_context_header = chdr_set_num_mdata(chdr_set_seq_num(chdr_set_pkt_type(chdr_set_length(m_in_context_tdata, 108 + (CHDR_W >> 3)), CHDR_PKT_TYPE_DATA), chdr_seqnum - 1), 0);

  // Snag SeqNum
  wire [15:0] chdr_seqnum;
  assign chdr_seqnum = chdr_get_seq_num(m_in_context_tdata);

  // Calculate the DIFI packet size from the CHDR packet size
  wire [15:0] chdr_timestamp_and_metadata_bytes;
  assign chdr_timestamp_and_metadata_bytes = (chdr_get_has_time(m_in_context_tdata) ? 8 : 0) + (chdr_get_num_mdata(m_in_context_tdata) << 3);
  wire [15:0] calc_difi_packet_size;
  assign calc_difi_packet_size = (chdr_get_length(m_in_context_tdata) - chdr_timestamp_and_metadata_bytes + 20) >> 2;

  // Timestamp Converter

  reg [63:0] chdr_timestamp = 0;

  reg cdtc_i_tvalid = 0;
  wire cdtc_i_tready;
  wire cdtc_int_timestamp_tvalid;
  reg cdtc_int_timestamp_tready = 0;
  wire [63:0] cdtc_frac_timestamp_tdata;
  wire cdtc_frac_timestamp_tvalid;
  reg cdtc_frac_timestamp_tready = 0;

  chdr_difi_timestamp_converter chdr_difi_timestamp_converter_i (
    .clk(axis_data_clk),
    .rst(axis_data_rst),
    .chdr_timestamp(chdr_timestamp),
    .tick_period(tick_period),
    .i_tvalid(cdtc_i_tvalid),
    .i_tready(cdtc_i_tready),
    .int_timestamp_tdata(difi_int_timestamp),
    .int_timestamp_tvalid(cdtc_int_timestamp_tvalid),
    .int_timestamp_tready(cdtc_int_timestamp_tready),
    .frac_timestamp_tdata(cdtc_frac_timestamp_tdata),
    .frac_timestamp_tvalid(cdtc_frac_timestamp_tvalid),
    .frac_timestamp_tready(cdtc_frac_timestamp_tready)
  );

  // State Machine ------------------------------------------------------------

  reg sent_context_packet = 1;
  reg [4:0] context_packet_counter = 0;

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
      sent_context_packet <= 0;
      context_packet_counter <= 0;
    end else begin
      case(state)
        DIFI_MODIFY_CHDR_ST : begin
          if (m_in_context_tvalid && s_out_context_tready) begin
            if (!sent_context_packet) begin
              state <= DIFI_SEND_CONTEXT_PACKET;
            end else begin
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
        end
        DIFI_SEND_CONTEXT_PACKET : begin
          if (s_out_payload_tready) begin
            if (context_packet_counter == 26) begin
              state <= DIFI_MODIFY_CHDR_ST;
              sent_context_packet <= 1;
              context_packet_counter <= 0;
            end else begin
              context_packet_counter <= context_packet_counter + 1;
            end
          end
        end
        DIFI_CHDR_TIMESTAMP_ST : begin
          if (m_in_context_tvalid && s_out_context_tready && cdtc_i_tready) begin
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
          if (s_out_payload_tready && (cdtc_int_timestamp_tvalid || chdr_timestamp == 0)) begin
            state <= DIFI_ADD_FRAC_TS_MS_ST;
          end
        end
        DIFI_ADD_FRAC_TS_MS_ST : begin
          if (s_out_payload_tready && (cdtc_frac_timestamp_tvalid || chdr_timestamp == 0)) begin
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
        out_context_tdata <= !sent_context_packet ? chdr_context_header : updated_header;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast || !sent_context_packet;
        out_context_tvalid <= m_in_context_tvalid;
        in_context_tready <= s_out_context_tready && sent_context_packet;

        out_payload_tdata <= 32'b0;
        out_payload_tkeep <= 1'b0;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b0;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= 0;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_SEND_CONTEXT_PACKET : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= standard_context_packet_payload[context_packet_counter];
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= (context_packet_counter == 26 && s_out_payload_tready);
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= 0;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_CHDR_TIMESTAMP_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= m_in_context_tvalid && (cdtc_i_tready || !chdr_timestamp);
        in_context_tready <= s_out_context_tready && (cdtc_i_tready || !chdr_timestamp);

        out_payload_tdata <= 32'b0;
        out_payload_tkeep <= 1'b0;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b0;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= m_in_context_tdata;
        cdtc_i_tvalid <= m_in_context_tdata != 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
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

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_ADD_HEADER_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= { 8'b00011000, difi_tsi, 2'b10, difi_seqnum, difi_packet_size };
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_ADD_STREAMID_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= { difi_streamid };
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_ADD_OUI_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= { 8'b00000000, difi_oui };
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_ADD_ICC_PCC_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= { difi_icc, difi_pcc };
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_ADD_INT_TS_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= chdr_timestamp == 0 ? 0 : { difi_int_timestamp };
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= (cdtc_int_timestamp_tvalid || !chdr_timestamp);
        in_payload_tready <= 1'b0;

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= chdr_timestamp != 0;
        cdtc_frac_timestamp_tready <= 0;
      end
      DIFI_ADD_FRAC_TS_MS_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= chdr_timestamp == 0 ? 0 : { cdtc_frac_timestamp_tdata[63:32] };
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= (cdtc_frac_timestamp_tvalid || !chdr_timestamp);
        in_payload_tready <= 1'b0;

        difi_frac_timestamp <= chdr_timestamp == 0 ? 0 : { cdtc_frac_timestamp_tdata[31:0] };

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= chdr_timestamp != 0;
      end
      DIFI_ADD_FRAC_TS_LS_ST : begin
        out_context_tdata <= m_in_context_tdata;
        out_context_tuser <= m_in_context_tuser;
        out_context_tlast <= m_in_context_tlast;
        out_context_tvalid <= 1'b0;
        in_context_tready <= 1'b0;

        out_payload_tdata <= { difi_frac_timestamp[31:0] };
        out_payload_tkeep <= 1'b1;
        out_payload_tlast <= 1'b0;
        out_payload_tvalid <= 1'b1;
        in_payload_tready <= 1'b0;

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
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

        chdr_timestamp <= chdr_timestamp;
        cdtc_i_tvalid <= 0;
        cdtc_int_timestamp_tready <= 0;
        cdtc_frac_timestamp_tready <= 0;
      end
    endcase
  end

endmodule // rfnoc_block_difi


`default_nettype wire
