set(CMAKE_CXX_COMPILER /Users/hhughe11/research/gcc_compiler/bin/g++-6.3.0)
set(CMAKE_C_COMPILER /Users/hhughe11/research/gcc_compiler/bin/gcc-6.3.0)
        
include_directories(
                   /opt/intel/mkl/include
                   /Users/hhughe11/research/dare/fake_data_test
                   /Users/hhughe11/research/dare
                   /Users/hhughe11/plasma-17.1/include
                   )


project(optimize C CXX)

add_library(
           profile_lib SHARED
           hooks.cpp
           autogen.cpp
           profile.cpp
           dare_base.cpp
           fake_data_test/fake_data.cpp
           autotune.cpp
           )


target_link_libraries(
                     profile_lib
                     /Users/hhughe11/plasma-17.1/lib/libcoreblas.so
                     /Users/hhughe11/plasma-17.1/lib/libplasma.so
                     -fopenmp
                     )

