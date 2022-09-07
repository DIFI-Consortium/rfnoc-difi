#include <uhd/exception.hpp>
#include <uhd/rfnoc_graph.hpp>
#include <uhd/utils/safe_main.hpp>
#include <rfnoc/difi/difi_block_control.hpp>
#include <boost/program_options.hpp>
#include <difipack/standard_context_packet.hpp>
#include <uhd/rfnoc/radio_control.hpp>

namespace po = boost::program_options;

int UHD_SAFE_MAIN(int argc, char *argv[])
{
  // To be honest, I don't know if this is how you are supposed to run something like this.
  std::string args;

  // setup the program options
  po::options_description desc("Allowed options");
  // clang-format off
    desc.add_options()
        ("help", "help message")
        ("args", po::value<std::string>(&args)->default_value(""), "USRP device address args")
    ;
  // clang-format on
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  // print the help message
  if (vm.count("help"))
  {
    std::cout << "Init RFNoC DIFI block " << desc << std::endl;
    std::cout << std::endl
              << "This application attempts to find a DIFI block in a USRP "
                 "and tries to peek/poke registers..\n"
              << std::endl;
    return EXIT_SUCCESS;
  }

  uhd::time_spec_t asd = uhd::time_spec_t::from_ticks(0x7FFFFFFFFFFFFFFFLL, 160000000.0);
  std::cout << std::to_string(asd.get_full_secs()) << std::endl;
  std::cout << std::to_string(asd.get_frac_secs()) << std::endl;

  // Create RFNoC graph object:
  auto graph = uhd::rfnoc::rfnoc_graph::make(args);

  // Verify we have a DIFI block:
  auto difi_blocks = graph->find_blocks<rfnoc::difi::difi_block_control>("");
  if (difi_blocks.empty())
  {
    std::cout << "No DIFI block found." << std::endl;
    return EXIT_FAILURE;
  }

  auto difi_block = graph->get_block<rfnoc::difi::difi_block_control>(difi_blocks.front());
  if (!difi_block)
  {
    std::cout << "ERROR: Failed to extract block controller!" << std::endl;
    return EXIT_FAILURE;
  }
  difipack::standard_context_packet new_context_packet = difipack::standard_context_packet::builder().build();
  difi_block->set_standard_context_packet(new_context_packet);

  // Create handle for radio object
  uhd::rfnoc::block_id_t radio_ctrl_id(0, "Radio", 0);
  // This next line will fail if the radio is not actually available
  auto radio_ctrl = graph->get_block<uhd::rfnoc::radio_control>(radio_ctrl_id);
  std::cout << "Using radio " << 0 << ", channel " << 0 << std::endl;

  std::cout << "Requesting samples per packet of: " << 20 << std::endl;
  radio_ctrl->set_property<int>("spp", 20, 0);
  int spp = radio_ctrl->get_property<int>("spp", 0);
  std::cout << "Actual samples per packet = " << spp << std::endl;

  radio_ctrl->set_rx_frequency(0, 0);

  /************************************************************************
   * Set up streaming
   ***********************************************************************/

  // create a receive streamer
  uhd::stream_args_t stream_args("sc16", "sc16"); // We should read the wire format from the blocks
  stream_args.args = "addr=172.22.185.13,port=7777,adapter=sfp0,stream_mode=raw_payload";
  std::cout << "Using streamer args: " << stream_args.args.to_string() << std::endl;
  auto rx_stream = graph->create_rx_streamer(1, stream_args);
  uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
  rx_stream->issue_stream_cmd(stream_cmd);

  return EXIT_SUCCESS;
}