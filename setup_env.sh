#!/bin/bash

# Install cmake
sudo apt-get install cmake

# Install ncurses
sudo apt-get install libncurses5-dev

# Install boost
sudo apt-get install libboost-all-dev

# Install gmock
sudo apt-get install google-mock
cd /usr/src/gmock
sudo mkdir build && cd build
cmake ..
make gmock_main
make gtest_main
sudo cp libgmock* /usr/lib
sudo cp gtest/libgtest* /usr/lib
sudo cp -r ../gtest/include/gtest /usr/include


