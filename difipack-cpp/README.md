# DIFI Packet C++ Library

## Prerequisites

UHD, gcc/g++, CMake, Boost unit testing framework, and some build system compatible with Cmake

We recommend building UHD from source, however you can download from some package managers.

### Linux (Ubuntu/Debian)

``` bash
sudo apt install gcc cmake make libboost-test-dev
```

## Installing

Configure/generate the build files:

``` bash
# chdr_difi/difipack
mkdir build
cd build
cmake ../
```

Make and install the library

``` bash
make
sudo make install
sudo ldconfig
```

## Uninstalling

The package can be uninstalled by running the following from the build directory created during installation.

``` bash
make uninstall
```

## Running the tests

After building the library, the tests can be run with `make test`. You need boost's unit test framework.

## Building the Docs

Before building the docs, you need to install Doxygen and Graphviz (e.g., `sudo apt install doxygen graphviz`).

Run CMake with the option `-DBUILD_WITH_DOCS=ON`, and then use `make docs` to generate the docs.

``` bash
# chdr_difi/difipack
mkdir build
cd build
cmake -DBUILD_WITH_DOCS=ON ../
make docs
```

The index file can be found at `build/docs/html/index.html`.

## Built With

Ubuntu, VSCode (and C++ Extensions)
