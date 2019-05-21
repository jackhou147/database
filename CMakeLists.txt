cmake_minimum_required(VERSION 3.13)
project(database)

set(CMAKE_CXX_STANDARD 14)

add_executable(database main.cpp Record.cpp Record.h Parser.cpp Parser.h Table.cpp Table.h BPlusTree.h utils.h stokenizer.cpp stokenizer.h token.cpp token.h constants.h twoD.h MMap.cpp MMap.h MPair.cpp MPair.h Map.cpp Map.h Pair.cpp Pair.h)