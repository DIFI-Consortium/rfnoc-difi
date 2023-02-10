## UHD USRP Samples to DIFI UDP Output Application

### Prerequisites

UHD, gcc/g++, cmake, make, difipack

We recommend building UHD from source, however you can download it from some package managers.

Works with gr-difi!

**Linux (Ubuntu/Debian)**

``` bash
sudo apt install gcc cmake make
```

### Running

The executable is created in the `build/examples` directory of difipack. It can be run like any command line executable, and arguments
are formatted as `--[argument_name]=[value]`. For example:

``` bash
./uhd_to_difi --args="addr=192.168.9.2" --addr=192.168.9.1 --port=7777 --stream-id=42 --freq=223000000
```

To view a list of allowed arguments and defaults, run:

``` bash
./uhd_to_difi --help
```
