cmake_minimum_required (VERSION 3.0)
project (RSA_Algorithm)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O2 -g")
add_executable(run src/rsa.cpp src/main.cpp)
