# RFNoC: A DIFI out-of-tree module

This directory contains a fully functional out-of-tree module with a gain block.
It serves as an example for OOT modules with UHD 4.0 and above.

## Directory Structure

* `blocks`: This directory contains all the block definitions. These block
  definitions can be read by the RFNoC tools, and will get installed into the
  system for use by other out-of-tree modules.

* `cmake`: This directory only needs to be modified if this OOT module will
  come with its own custom CMake modules.

* `fpga`: This directory contains the source code for the HDL modules of the
  individual RFNoC blocks, along with their testbenches, and additional modules
  required to build the blocks. There is one subdirectory for every block.

* `include/rfnoc/difi`: Here, all the header files for the block controllers
  are stored, along with any other include files that should be installed when
  installing this OOT module.

* `lib`: Here, all the non-header source files for the block controllers are stored,
  along with any other include file that should be installed when installing
  this OOT module. This includes the block controller cpp files.

* `apps`: This contains an example application that links against UHD and this
  OOT module. The app does not get installed, it resides in the build directory.

  ## Zach's Notes

  `blocks` and `fpga` are mainly for the HDL development.

  `include`, `lib`, and `apps` are for C++ register editing and testing.

  `icores` is for making FPGA images with the OOT block. Make sure to add it to CMake.

  ### RFNoC Blocks

  `rfnoc_block_difi` is a working-in-testbench, *not-working-on-the-x410* full implementation of the DIFI block.

  `rfnoc_block_difi_basic` is a working on both the testbench and x410 DIFI rfnoc block, but this does not send a context packet, have customizable registers, nor timestamp calculation.

  The idea is we want to convert `rfnoc_block_difi_basic` into `rfnoc_block_difi`, but like make it actually work on the x410.

  I would first try adding the customizable registers, add the context packet, and then the timestamp--building and running on the x410 between *each of the steps*.

  Careful: timestamp are only correct if there is a GPS lock on the x410 and the timestamp calculations occur (hopefully there is a better way?).

  ### Building stuff

  ```bash
  mkdir build
  cmake -DUHD_FPGA_PATH=/path/to/chdr_difi/rfnoc-difi/uhddev/fpga ../
  make help
  ```