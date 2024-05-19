cmake_minimum_required(VERSION 3.28)
project(BigInteger)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/BigInteger.cpp
        src/main.cpp
)

add_executable(BigInteger ${SOURCES})

target_include_directories(BigInteger
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
