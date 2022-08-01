cmake_minimum_required(VERSION 3.17)
project(ProjetoPratico C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

add_executable(ProjetoPratico main.c)