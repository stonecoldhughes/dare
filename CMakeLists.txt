set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
        
include_directories(
                   /sw/intel/2018/compilers_and_libraries_2018.0.128/linux/mkl/include
                   /home/hhughe11/dare/fake_data_test
                   /home/hhughe11/dare
                   /home/hhughe11/plasma-17.1/include
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
                     /home/hhughe11/plasma-17.1/lib/libcoreblas.so
                     /home/hhughe11/plasma-17.1/lib/libplasma.so
                     -fopenmp
                     )

