set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)

#Check value of variable and if it isn't set, comment something to the user
if(NOT DEFINED PLASMA_INCLUDE)
    message(FATAL_ERROR "Run CMake with -DPLASMA_INCLUDE=/example/path")
else()
    message(STATUS "PLASMA_INCLUDE=${PLASMA_INCLUDE}")
endif()

project(optimize C CXX)

#/Users/hhughe11/plasma/include is plasma include directory
include_directories(
                   ${PLASMA_INCLUDE}
                   )

#Add a DEPENDS clause in this command so it builds if any of the files in plasma.h change
#Test it out by changing shit and seeing what it does
#add_custom_command(
#                  OUTPUT autogen_prelim.cpp
 #                 COMMAND python hello.py ${PLASMA_INCLUDE}
  #                DEPENDS ${PLASMA_INCLUDE}
   #               )

add_executable(main main.c)

add_library(
           profile_lib SHARED 
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
