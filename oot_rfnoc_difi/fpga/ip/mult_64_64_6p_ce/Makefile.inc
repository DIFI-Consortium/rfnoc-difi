include $(TOOLS_DIR)/make/viv_ip_builder.mak

LIB_IP_MULT_64_64_6P_CE_SRCS = $(IP_BUILD_DIR)/mult_64_64_6p_ce/mult_64_64_6p_ce.xci

LIB_IP_MULT_64_64_6P_CE_OUTS = $(addprefix $(IP_BUILD_DIR)/mult_64_64_6p_ce/, \
mult_64_64_6p_ce.xci.out \
synth/mult_64_64_6p_ce.vhd \
) 

$(LIB_IP_MULT_64_64_6P_CE_SRCS) $(LIB_IP_MULT_64_64_6P_CE_OUTS) : $(OOT_FPGA_DIR)/ip/mult_64_64_6p_ce/mult_64_64_6p_ce.xci
	$(call BUILD_VIVADO_IP,mult_64_64_6p_ce,$(ARCH),$(PART_ID),$(OOT_FPGA_DIR)/ip,$(IP_BUILD_DIR),0)