set(CMAKE_C_COMPILER /Users/hhughe11/llvm_dir/build/bin/clang-4.0)

#Check value of variable and if it isn't set, comment something to the user
if(NOT DEFINED PLASMA_INCLUDE)
    message(FATAL_ERROR "Run CMake with -DPLASMA_INCLUDE=/example/path")
else()
    message(STATUS "PLASMA_INCLUDE=${PLASMA_INCLUDE}")
endif()

project(optimize C CXX)

#/Users/hhughe11/plasma/include is plasma include directory
include_directories(
                   /Users/hhughe11/libomp_oss/src
                   ${PLASMA_INCLUDE}
                   )

add_executable(main main.c)

add_library(
           profile_lib SHARED 
           hooks.cpp
           autogen.cpp
           profile.cpp 
           ompt_entry_point.cpp
           callbacks.cpp
           )

#Change this to add_custom_command() to have it create generated output files
#add_custom_command() will create files that the rest of the project depends on
#add_custom_target(
 #                autogenerate ALL 
  #               COMMAND python autogenerate.py
   #              COMMENT "Running autogenerate.py"
    #             )

add_dependencies(main profile_lib autogenerate)

target_link_libraries(
                     profile_lib
                     /Users/hhughe11/libomp_oss/src/libiomp5.dylib
                     /Users/hhughe11/plasma/lib/libcoreblas.so
                     /Users/hhughe11/plasma/lib/libplasma.so
                     -flat_namespace
                     -g
                     )

target_link_libraries(
                     main
                     profile_lib
                     /opt/intel/compilers_and_libraries_2016.3.170/mac/mkl/lib/libmkl_intel_lp64.dylib
                     /opt/intel/compilers_and_libraries_2016.3.170/mac/mkl/lib/libmkl_core.dylib
                     /opt/intel/compilers_and_libraries_2016.3.170/mac/mkl/lib/libmkl_intel_thread.dylib
                     -lpthread
                     -lm
                     -ldl
                     -flat_namespace
                     -g
                     )
