cmake_minimum_required(VERSION 3.31.6)
project(ephemeral)

set(CMAKE_CXX_STANDARD 26)

add_library(wallet STATIC Wallet.cpp Wallet.h)
add_library(ephemeral STATIC Ephemeral.cpp Ephemeral.h
        Ephemeral.cpp
        Ephemeral.h)

install(FILES Ephemeral.h Wallet.h DESTINATION include)
install(TARGETS wallet ephemeral  DESTINATION lib)