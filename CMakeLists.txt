cmake_minimum_required(VERSION 3.10)
project(21su-srch-eng)

set(CMAKE_CXX_STANDARD 20)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(21su-srch-eng main.cpp DSVector.h DSString.h DSString.cpp DSTree.h DocumentParser.cpp DocumentParser.h Paper.cpp Paper.h porter2_stemmer.cpp porter2_stemmer.h Index.cpp Index.h DSHash.h list.h QueryEngine.cpp QueryEngine.h)