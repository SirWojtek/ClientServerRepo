
##ClientServerRepo##

###Building intructions###

1. Run: cmake -G "Unix Makefiles" to generate makefiles needed for compilation
2. Run make <job> for compilation of component:
    - client - client executable
    - clientTest - client UTs
    - server - server executable
    - server UTs coming soon

Compiled binaries are placed in build folder in root of project.

###Preparing environment###
(in case your Ubuntu or Archlinux blows up)

1. Packages required:
 - gcc and g++ 4.9 or newer
 - cmake 2.8 or newer
 - boost 1.57 or newer
 - gmock 1.6 (and gtest 1.7 to fit it)

2. Building gcc/g++ : in case of Ubuntu, you must add repository to be able to fetch gcc 4.9
    ```
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install g++-4.9
    ```
    
3. Building cmake : Version 2.8 is pretty basic and should be availible in default repository
    `sudo apt-get install cmake`

4. Building Boost : if Boost 1.57 is already availible in your repository, just fetch it with apt-get (or yum, or whatever your OS uses). Otherwise Boost must be downloaded from [here](http://www.boost.org/users/history/version_1_57_0.html) and its fragments must be placed in correct places (no compilation needed):
    //TODO - complete this section

5. Building gmock : download gmock from [here](https://code.google.com/p/googlemock/downloads/list) in version 1.6
    This step begins by building gtest. In gmock/gtest there is a corresponding version of gtest to gmock that you just downloaded. Build it with following commands:
    ```
    cd gtest
    ./configure
    make
    sudo cp -a include/gtest /usr/include
    sudo cp -a lib/.libs/* /usr/lib/
    ```
    You can now check if it worked by running following command:
    `sudo ldconfig -v | grep gtest`
    and checking if result is the same as below:
    ```
    libgtest.so.0 -> libgtest.so.0.0.0
    libgtest_main.so.0 -> libgtest_main.so.0.0.0
    ```
    With gtest installed, you can now install gmock. Run the following commands:
    ```
    cd ${GMOCK_ROOT}
    mkdir build
    cd build
    g++ -I../gtest/include -I../gtest -I../include -I.. -c ../gtest/src/gtest-all.cc
    g++ -I../gtest/include -I../gtest -I../include -I.. -c ../src/gmock-all.cc
    ar -rv libgmock.a gtest-all.o gmock-all.o
    ```
    After building, fragments of gmock must be placed in correct places:
    //TODO - complete this section
