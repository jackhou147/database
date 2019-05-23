cmake_minimum_required(VERSION 3.13)
project(database)

set(CMAKE_CXX_STANDARD 14)

add_executable(database main.cpp Record.cpp Record.h Parser.cpp Parser.h Table.cpp Table.h BPlusTree.h constants.h Pair.h utils.h MMap.h Map.h MPair.h stokenizer.cpp stokenizer.h token.h twoD.h SQL.cpp SQL.h)