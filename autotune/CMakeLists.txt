set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)

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
                   ${DARE_DIR}/matrix_classes
                   )

add_executable(
              autotune.bin
              main.cpp
              ${DARE_DIR}/matrix_classes/matrix_classes.cpp
              )

target_link_libraries(
                     autotune.bin
                     ${DARE_DIR}/libprofile_lib.dylib
                     ${PLASMA_DIR}/lib/libplasma.so
                     ${PLASMA_DIR}/lib/libcoreblas.so
                     -Wl,-rpath,${PLASMA_DIR}/lib
                     -fopenmp
                     )

add_executable(
              autotune_raw.bin
              main.cpp
              ${DARE_DIR}/matrix_classes/matrix_classes.cpp
              )

target_link_libraries(
                     autotune_raw.bin
                     ${PLASMA_DIR}/lib/libplasma.so
                     ${PLASMA_DIR}/lib/libcoreblas.so
                     -Wl,-rpath,${PLASMA_DIR}/lib
                     -fopenmp
                     )
