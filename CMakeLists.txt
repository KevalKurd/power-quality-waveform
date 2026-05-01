cmake_minimum_required(VERSION 3.20)
project(PowerQualityAnalyser C)

set(CMAKE_C_STANDARD 99)

add_executable(PowerQualityAnalyser
        main.c
        waveform.c
        io.c)