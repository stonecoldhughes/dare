set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)

#Check value of variable and if it isn't set, comment something to the user
if(NOT DEFINED PLASMA_DIR)
    message(FATAL_ERROR "Run CMake with -DPLASMA_DIR=/example/path")
else()
    message(STATUS "PLASMA_DIR=${PLASMA_DIR}")
endif()

#Captain! This is kind of a hack to invoke default behavior
if(NOT DEFINED WRAPPER_CONFIG)
    set(WRAPPER_CONFIG time_kernel)
endif()

project(optimize C CXX)

#/Users/hhughe11/plasma/include is plasma include directory
include_directories(
                   ${PLASMA_DIR}/include
                   )

add_custom_command(
                  OUTPUT autogen_types.h autogen.cpp hooks.cpp
                  COMMAND python autogen.py -d ${PLASMA_DIR} -w ${WRAPPER_CONFIG}
                  DEPENDS ${PLASMA_DIR/include}
                  )

add_executable(main main.c)

add_library(
           profile_lib SHARED 
           /Users/hhughe11/plasma/tools/trace.cpp
           hooks.cpp
           autogen.cpp
           profile.cpp 
           )

target_link_libraries(
                     profile_lib
                     /Users/hhughe11/plasma/lib/libcoreblas.so
                     /Users/hhughe11/plasma/lib/libplasma.so
                     -fopenmp
                     -flat_namespace
                     -g
                     )

target_link_libraries(
                     main
                     profile_lib
                     /Users/hhughe11/research/intel_compiler/compilers_and_libraries_2017.2.163/mac/mkl/lib/libmkl_intel_lp64.dylib
                     /Users/hhughe11/research/intel_compiler/compilers_and_libraries_2017.2.163/mac/mkl/lib/libmkl_core.dylib
                     /Users/hhughe11/research/intel_compiler/compilers_and_libraries_2017.2.163/mac/mkl/lib/libmkl_intel_thread.dylib
                     -lpthread
                     -lm
                     -ldl
                     -flat_namespace
                     -g
                     )
