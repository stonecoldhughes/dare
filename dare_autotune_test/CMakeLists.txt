set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)
set(CMAKE_BUILD_TYPE Debug)

project(optimize C CXX)

if(NOT DEFINED PLASMA_DIR)
    message(FATAL_ERROR "Run CMake with -DPLASMA_DIR=/example/path")
else()
    message(STATUS "PLASMA_DIR=${PLASMA_DIR}")
endif()

if(NOT DEFINED DARE_DIR)
    message(FATAL_ERROR "Run CMake with -DDARE_DIR=/example/path")
else()
    message(STATUS "DARE_DIR=${DARE_DIR}")
endif()

include_directories(
                   ${PLASMA_DIR}/include
                   )

add_executable(dpotrf_test.bin main.c)

target_link_libraries(
                     dpotrf_test.bin
                     ${DARE_DIR}/libprofile_lib.dylib
                     ${PLASMA_DIR}/lib/libplasma.so
                     ${PLASMA_DIR}/lib/libcoreblas.so
                     -Wl,-rpath,${PLASMA_DIR}/lib
                     -g
                     )
