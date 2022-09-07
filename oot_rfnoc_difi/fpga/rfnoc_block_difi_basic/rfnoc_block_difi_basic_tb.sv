//
// Copyright 2022 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// Module: rfnoc_block_difi_basic_tb
//
// Description: Testbench for the difi_basic RFNoC block.
//

`default_nettype none


module rfnoc_block_difi_basic_tb;

  `include "test_exec.svh"

  import PkgTestExec::*;
  import PkgChdrUtils::*;
  import PkgRfnocBlockCtrlBfm::*;
  import PkgRfnocItemUtils::*;

  //---------------------------------------------------------------------------
  // Testbench Configuration
  //---------------------------------------------------------------------------

  localparam [31:0] NOC_ID          = 32'h000BD1F1;
  localparam [ 9:0] THIS_PORTID     = 10'h123;
  localparam int    CHDR_W          = 64;    // CHDR size in bits
  localparam int    MTU             = 10;    // Log2 of max transmission unit in CHDR words
  localparam int    NUM_PORTS_I     = 1;
  localparam int    NUM_PORTS_O     = 1;
  localparam int    ITEM_W          = 32;    // Sample size in bits
  localparam int    SPP             = 64;    // Samples per packet
  localparam int    PKT_SIZE_BYTES  = SPP * (ITEM_W/8);
  localparam int    STALL_PROB      = 25;    // Default BFM stall probability
  localparam real   CHDR_CLK_PER    = 5.0;   // 200 MHz
  localparam real   CTRL_CLK_PER    = 8.0;   // 125 MHz

  //---------------------------------------------------------------------------
  // Clocks and Resets
  //---------------------------------------------------------------------------

  bit rfnoc_chdr_clk;
  bit rfnoc_ctrl_clk;

  sim_clock_gen #(CHDR_CLK_PER) rfnoc_chdr_clk_gen (.clk(rfnoc_chdr_clk), .rst());
  sim_clock_gen #(CTRL_CLK_PER) rfnoc_ctrl_clk_gen (.clk(rfnoc_ctrl_clk), .rst());

  //---------------------------------------------------------------------------
  // Bus Functional Models
  //---------------------------------------------------------------------------

  // Backend Interface
  RfnocBackendIf backend (rfnoc_chdr_clk, rfnoc_ctrl_clk);

  // AXIS-Ctrl Interface
  AxiStreamIf #(32) m_ctrl (rfnoc_ctrl_clk, 1'b0);
  AxiStreamIf #(32) s_ctrl (rfnoc_ctrl_clk, 1'b0);

  // AXIS-CHDR Interfaces
  AxiStreamIf #(CHDR_W) m_chdr [NUM_PORTS_I] (rfnoc_chdr_clk, 1'b0);
  AxiStreamIf #(CHDR_W) s_chdr [NUM_PORTS_O] (rfnoc_chdr_clk, 1'b0);

  // Block Controller BFM
  RfnocBlockCtrlBfm #(CHDR_W, ITEM_W) blk_ctrl = new(backend, m_ctrl, s_ctrl);

  // CHDR word and item/sample data types
  typedef ChdrData #(CHDR_W, ITEM_W)::chdr_word_t chdr_word_t;
  typedef ChdrData #(CHDR_W, ITEM_W)::item_t      item_t;

  // Connect block controller to BFMs
  for (genvar i = 0; i < NUM_PORTS_I; i++) begin : gen_bfm_input_connections
    initial begin
      blk_ctrl.connect_master_data_port(i, m_chdr[i], PKT_SIZE_BYTES);
      blk_ctrl.set_master_stall_prob(i, STALL_PROB);
    end
  end
  for (genvar i = 0; i < NUM_PORTS_O; i++) begin : gen_bfm_output_connections
    initial begin
      blk_ctrl.connect_slave_data_port(i, s_chdr[i]);
      blk_ctrl.set_slave_stall_prob(i, STALL_PROB);
    end
  end

  //---------------------------------------------------------------------------
  // Device Under Test (DUT)
  //---------------------------------------------------------------------------

  // DUT Slave (Input) Port Signals
  logic [CHDR_W*NUM_PORTS_I-1:0] s_rfnoc_chdr_tdata;
  logic [       NUM_PORTS_I-1:0] s_rfnoc_chdr_tlast;
  logic [       NUM_PORTS_I-1:0] s_rfnoc_chdr_tvalid;
  logic [       NUM_PORTS_I-1:0] s_rfnoc_chdr_tready;

  // DUT Master (Output) Port Signals
  logic [CHDR_W*NUM_PORTS_O-1:0] m_rfnoc_chdr_tdata;
  logic [       NUM_PORTS_O-1:0] m_rfnoc_chdr_tlast;
  logic [       NUM_PORTS_O-1:0] m_rfnoc_chdr_tvalid;
  logic [       NUM_PORTS_O-1:0] m_rfnoc_chdr_tready;

  // Map the array of BFMs to a flat vector for the DUT connections
  for (genvar i = 0; i < NUM_PORTS_I; i++) begin : gen_dut_input_connections
    // Connect BFM master to DUT slave port
    assign s_rfnoc_chdr_tdata[CHDR_W*i+:CHDR_W] = m_chdr[i].tdata;
    assign s_rfnoc_chdr_tlast[i]                = m_chdr[i].tlast;
    assign s_rfnoc_chdr_tvalid[i]               = m_chdr[i].tvalid;
    assign m_chdr[i].tready                     = s_rfnoc_chdr_tready[i];
  end
  for (genvar i = 0; i < NUM_PORTS_O; i++) begin : gen_dut_output_connections
    // Connect BFM slave to DUT master port
    assign s_chdr[i].tdata        = m_rfnoc_chdr_tdata[CHDR_W*i+:CHDR_W];
    assign s_chdr[i].tlast        = m_rfnoc_chdr_tlast[i];
    assign s_chdr[i].tvalid       = m_rfnoc_chdr_tvalid[i];
    assign m_rfnoc_chdr_tready[i] = s_chdr[i].tready;
  end

  rfnoc_block_difi_basic #(
    .THIS_PORTID         (THIS_PORTID),
    .CHDR_W              (CHDR_W),
    .MTU                 (MTU)
  ) dut (
    .rfnoc_chdr_clk      (rfnoc_chdr_clk),
    .rfnoc_ctrl_clk      (rfnoc_ctrl_clk),
    .rfnoc_core_config   (backend.cfg),
    .rfnoc_core_status   (backend.sts),
    .s_rfnoc_chdr_tdata  (s_rfnoc_chdr_tdata),
    .s_rfnoc_chdr_tlast  (s_rfnoc_chdr_tlast),
    .s_rfnoc_chdr_tvalid (s_rfnoc_chdr_tvalid),
    .s_rfnoc_chdr_tready (s_rfnoc_chdr_tready),
    .m_rfnoc_chdr_tdata  (m_rfnoc_chdr_tdata),
    .m_rfnoc_chdr_tlast  (m_rfnoc_chdr_tlast),
    .m_rfnoc_chdr_tvalid (m_rfnoc_chdr_tvalid),
    .m_rfnoc_chdr_tready (m_rfnoc_chdr_tready),
    .s_rfnoc_ctrl_tdata  (m_ctrl.tdata),
    .s_rfnoc_ctrl_tlast  (m_ctrl.tlast),
    .s_rfnoc_ctrl_tvalid (m_ctrl.tvalid),
    .s_rfnoc_ctrl_tready (m_ctrl.tready),
    .m_rfnoc_ctrl_tdata  (s_ctrl.tdata),
    .m_rfnoc_ctrl_tlast  (s_ctrl.tlast),
    .m_rfnoc_ctrl_tvalid (s_ctrl.tvalid),
    .m_rfnoc_ctrl_tready (s_ctrl.tready)
  );

  //---------------------------------------------------------------------------
  // Helper Logic
  //---------------------------------------------------------------------------

  // Rand#(WIDTH)::rand_logic() returns a WIDTH-bit random number. We avoid
  // std::randomize() due to license requirements and limited tool support.
  class Rand #(WIDTH = 32);
    static function logic [WIDTH-1:0] rand_logic();
      logic [WIDTH-1:0] result;
      int num_rand32 = (WIDTH + 31) / 32;
      for (int i = 0; i < num_rand32; i++) begin
        result = {result, $urandom()};
      end
      return result;
    endfunction : rand_logic
  endclass : Rand

  typedef struct {
    item_t        samples[$];
    chdr_word_t   mdata[$];
    packet_info_t pkt_info;
  } test_packet_t;

  typedef struct packed {
    bit [15:0] i;
    bit [15:0] q;
  } sc16_t;

  function [31:0] unpack_word(input [31:0] word);
    begin
      unpack_word = { word[23:16], word[31:24], word[7:0], word[15:8] };
    end
  endfunction

  //---------------------------------------------------------------------------
  // Test Tasks
  //---------------------------------------------------------------------------

  task automatic test_register(
    logic [19:0] register_address,
    logic [31:0] write_value,
    logic [31:0] default_value
  );
    string str;
    logic [31:0] read_value;
    
    blk_ctrl.reg_read(register_address, read_value);
    $sformat(str, "Initial value is not the default value Expected: %d, Received: %d", default_value, read_value);
    `ASSERT_ERROR(read_value == default_value, str);

    blk_ctrl.reg_write(register_address, write_value);
    blk_ctrl.reg_read(register_address, read_value);
    $sformat(str, "Read value is not the default value Expected: %d, Received: %d", write_value, read_value);
    `ASSERT_ERROR(read_value == write_value, str);
  endtask

  task automatic test_register64(
    logic [19:0] register_address_ms,
    logic [19:0] register_address_ls,
    logic [63:0] write_value,
    logic [63:0] default_value
  );
    string str;
    logic [63:0] read_value;
    
    blk_ctrl.reg_read(register_address_ms, read_value[63:32]);
    blk_ctrl.reg_read(register_address_ls, read_value[31:0]);
    $sformat(str, "Initial value is not the default value Expected: %d, Received: %d", default_value, read_value);
    `ASSERT_ERROR(read_value == default_value, str);

    blk_ctrl.reg_write(register_address_ms, write_value[63:32]);
    blk_ctrl.reg_write(register_address_ls, write_value[31:0]);
    blk_ctrl.reg_read(register_address_ms, read_value[63:32]);
    blk_ctrl.reg_read(register_address_ls, read_value[31:0]);
    $sformat(str, "Read value is not the default value Expected: %d, Received: %d", write_value, read_value);
    `ASSERT_ERROR(read_value == write_value, str);
  endtask

  task automatic test_rand(
    int num_packets,
    int max_spp = SPP,
    int prob_in = STALL_PROB,
    int prob_out = STALL_PROB
  );
    mailbox #(test_packet_t) packets_mb_in = new();

    // Set the BFM TREADY behavior
    blk_ctrl.set_master_stall_prob(0, prob_in);
    blk_ctrl.set_slave_stall_prob(0, prob_out);

    fork
      repeat (num_packets) begin : send_process
        test_packet_t packet_in;
        int packet_length;

        packet_length = $urandom_range(1, max_spp);

        // Generate random data and header
        packet_in.samples = {};
        for (int i = 0; i < packet_length; i++) begin
          packet_in.samples.push_back($urandom());
        end

        // Generate random metadata
        packet_in.mdata = {};
        for (int i = 0; i < $urandom_range(0,31); i++)
          packet_in.mdata.push_back(Rand #(CHDR_W)::rand_logic());

        // Generate random header info
        packet_in.pkt_info = Rand #($bits(packet_in.pkt_info))::rand_logic();

        // Enqueue the packets for each port
        blk_ctrl.send_items(0, packet_in.samples, packet_in.mdata, packet_in.pkt_info);

        // Enqueue what we sent for the receiver to check the output
        packets_mb_in.put(packet_in);
      end
      begin
        repeat (num_packets) begin : recv_process
          // Data packet testing
          test_packet_t packet_in, packet_out;
          string str;
          int difi_header_out, difi_streamid_out, difi_oui_out, difi_icc_pcc_out, difi_int_timestamp_out, difi_frac_timestamp_ms_out, difi_frac_timestamp_ls_out;

          // Grab the next pair of packets that was input
          packets_mb_in.get(packet_in);

          // Receive a packet
          blk_ctrl.recv_items_adv(0, packet_out.samples,
            packet_out.mdata, packet_out.pkt_info);

          // Make sure the output packet length matches the input + DIFI
            $sformat(str,
              "Output packet length didn't match input + 7 Expected: %d, Received: %d",
              packet_in.samples.size() + 7, packet_out.samples.size());
          `ASSERT_ERROR(packet_in.samples.size() + 7 == packet_out.samples.size(), str);

          // Check that the output packet header info matches the input
          `ASSERT_ERROR(packet_info_equal(packet_in.pkt_info, packet_out.pkt_info),
            "Output packet header info didn't match input");

          // Check the metadata
          `ASSERT_ERROR(ChdrData #(CHDR_W)::chdr_equal(packet_in.mdata, packet_out.mdata),
            "Output metadata info didn't match input");

          // Verify DIFI data is correct
          difi_header_out = unpack_word(packet_out.samples[0]);
          difi_streamid_out = unpack_word(packet_out.samples[1]);
          difi_oui_out = unpack_word(packet_out.samples[2]);
          difi_icc_pcc_out = unpack_word(packet_out.samples[3]);
          difi_int_timestamp_out = unpack_word(packet_out.samples[4]);
          difi_frac_timestamp_ms_out = unpack_word(packet_out.samples[5]);
          difi_frac_timestamp_ls_out = unpack_word(packet_out.samples[6]);

          $sformat(str,
              "Output packet DIFI TSI didn't match Expected: %x, Received: %x",
              2'b01, difi_header_out[23:22]);
          `ASSERT_ERROR(2'b01 == difi_header_out[23:22], str);

          $sformat(str,
              "Output packet DIFI Packet size didn't match Expected: %x, Received: %x",
              packet_in.samples.size() + 7, difi_header_out[15:0]);
          `ASSERT_ERROR(packet_in.samples.size() + 7 == difi_header_out[15:0], str);

          $sformat(str,
              "Output packet DIFI Stream ID didn't match Expected: %x, Received: %x",
              32'h88888888, difi_streamid_out);
          `ASSERT_ERROR(32'h88888888 == difi_streamid_out, str);

          $sformat(str,
              "Output packet DIFI OUI didn't match Expected: %x, Received: %x",
              24'h123456, difi_oui_out);
          `ASSERT_ERROR(24'h123456 == difi_oui_out, str);

          $sformat(str,
              "Output packet DIFI ICC didn't match Expected: %x, Received: %x",
              16'hdead, difi_icc_pcc_out[31:16]);
          `ASSERT_ERROR(16'hdead == difi_icc_pcc_out[31:16], str);

          $sformat(str,
              "Output packet DIFI PCC didn't match Expected: %x, Received: %x",
              16'hbeef, difi_icc_pcc_out[15:0]);
          `ASSERT_ERROR(16'hbeef == difi_icc_pcc_out[15:0], str);

          $sformat(str,
              "Output packet DIFI Int Timestamp didn't match Expected: %x, Received: %x",
              32'h66666666, difi_int_timestamp_out);
          `ASSERT_ERROR(32'h66666666 == difi_int_timestamp_out, str);

          $sformat(str,
              "Output packet DIFI Frac Timestamp MS didn't match Expected: %x, Received: %x",
              32'hf0f0f0f0, difi_frac_timestamp_ms_out);
          `ASSERT_ERROR(32'hf0f0f0f0 == difi_frac_timestamp_ms_out, str);

          $sformat(str,
              "Output packet DIFI Frac Timestmap LS didn't match Expected: %x, Received: %x",
              32'h0f0f0f0f, difi_frac_timestamp_ls_out);
          `ASSERT_ERROR(32'h0f0f0f0f == difi_frac_timestamp_ls_out, str);

          // Verify that the data has the expected values
          for (int i = 7; i < packet_out.samples.size(); i++) begin
            sc16_t in, out;

            // Grab the input and output samples
            in = packet_in.samples[i - 7];
            out = packet_out.samples[i];

            // Check that the results match
            $sformat(str,
              "Incorrect value received on output [%X]! Expected: 0x%X, Received: 0x%X",
              i, in, out);
            `ASSERT_ERROR(in == out, str);
          end
        end
      end
    join
  endtask : test_rand

  //---------------------------------------------------------------------------
  // Main Test Process
  //---------------------------------------------------------------------------

  initial begin : tb_main

    // Initialize the test exec object for this testbench
    test.start_tb("rfnoc_block_difi_basic_tb");

    // Start the BFMs running
    blk_ctrl.run();

    //--------------------------------
    // Reset
    //--------------------------------

    test.start_test("Flush block then reset it", 10us);
    blk_ctrl.flush_and_reset();
    test.end_test();

    //--------------------------------
    // Verify Block Info
    //--------------------------------

    test.start_test("Verify Block Info", 2us);
    `ASSERT_ERROR(blk_ctrl.get_noc_id() == NOC_ID, "Incorrect NOC_ID Value");
    `ASSERT_ERROR(blk_ctrl.get_num_data_i() == NUM_PORTS_I, "Incorrect NUM_DATA_I Value");
    `ASSERT_ERROR(blk_ctrl.get_num_data_o() == NUM_PORTS_O, "Incorrect NUM_DATA_O Value");
    `ASSERT_ERROR(blk_ctrl.get_mtu() == MTU, "Incorrect MTU Value");
    test.end_test();

    //--------------------------------
    // Test Sequences
    //--------------------------------

    begin
      const int NUM_PACKETS = 500;

      test.start_test("Test random packets", 1ms);
      test_rand(NUM_PACKETS);
      test.end_test();

      test.start_test("Test without back pressure", 1ms);
      test_rand(NUM_PACKETS, SPP, 0, 0);
      test.end_test();

      test.start_test("Test back pressure", 1ms);
      test_rand(NUM_PACKETS, SPP, 25, 50);
      test.end_test();

      //test.start_test("Test underflow", 2ms);
      //test_rand(NUM_PACKETS, SPP, 50, 25);
      //test.end_test();

      test.start_test("Test min packet size", 1ms);
      test_rand(10, 1);
      test.end_test();
    end

    //--------------------------------
    // Finish Up
    //--------------------------------

    // Display final statistics and results
    test.end_tb();
  end : tb_main

endmodule : rfnoc_block_difi_basic_tb


`default_nettype wire
