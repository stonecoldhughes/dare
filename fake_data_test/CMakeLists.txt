set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)

project(fake_data_test C CXX)

if(NOT DEFINED PLASMA_DIR)
    message(FATAL_ERROR "Run CMake with -DPLASMA_DIR=/example/path")
else()
    message(STATUS "PLASMA_DIR=${PLASMA_DIR}")
endif()

include_directories(
                   /Users/hhughe11/research/dare/fake_data_test
                   /Users/hhughe11/research/dare
                   /opt/intel/mkl/include
                   ${PLASMA_DIR}/include
                   )

add_executable(fake_data_test.bin main.cpp fake_data.cpp)

target_link_libraries(
                     fake_data_test.bin
                     ${PLASMA_DIR}/lib/libplasma.so
                     ${PLASMA_DIR}/lib/libcoreblas.so
                     -fopenmp
                     -Wl,-rpath,${PLASMA_DIR}/lib
                     )
