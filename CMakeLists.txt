cmake_minimum_required(VERSION 3.13)
project(database)

set(CMAKE_CXX_STANDARD 14)

add_executable(database main.cpp Record.cpp Record.h Parser.cpp Parser.h Table.cpp Table.h BPlusTree.h constants.h Pair.cpp Pair.h utils.h MMap.cpp MMap.h Map.cpp Map.h MPair.cpp MPair.h stokenizer.cpp stokenizer.h token.cpp token.h twoD.cpp twoD.h)