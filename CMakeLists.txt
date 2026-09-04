cmake_minimum_required(VERSION 4.2)
project(For_Monte)

set(CMAKE_CXX_STANDARD 20)

add_executable(For_Monte src/main.cpp
        include/Option.h
        include/EuropeanCall.h
        include/EuropeanPut.h
        include/BlackScholesPricer.h
        src/StressTests.cpp
)
