set(CMAKE_C_COMPILER /Users/hhughe11/llvm_dir/build/bin/clang-4.0)

project(optimize C CXX)

include_directories(
                   /Users/hhughe11/libomp_oss/src
                   /Users/hhughe11/plasma/include
                   /Users/hhughe11/research/predict
                   /Users/hhughe11/research/generate
                   .
                   )

add_executable(main main.c)

add_library(
           profile_lib SHARED 
           profile.cpp 
           hooks.cpp
           ompt_entry_point.cpp
           callbacks.cpp
           /Users/hhughe11/research/predict/predict.cpp
           /Users/hhughe11/research/generate/generator.cpp
           )

target_link_libraries(
                     profile_lib
                     /Users/hhughe11/libomp_oss/src/libiomp5.dylib
                     /Users/hhughe11/plasma/lib/libplasma.so
                     /Users/hhughe11/plasma/lib/libcoreblas.so
                     -flat_namespace
                     )

#Some dependencies are repeated. This is so that "main" will compile without the profile library
#They should be totally independent
target_link_libraries(
                     main
                     profile_lib
                     /Users/hhughe11/plasma/lib/libplasma.so
                     /opt/intel/compilers_and_libraries_2016.3.170/mac/mkl/lib/libmkl_intel_lp64.dylib
                     /opt/intel/compilers_and_libraries_2016.3.170/mac/mkl/lib/libmkl_core.dylib
                     /opt/intel/compilers_and_libraries_2016.3.170/mac/mkl/lib/libmkl_intel_thread.dylib
                     /Users/hhughe11/plasma/lib/libcoreblas.so
                     -lpthread
                     -lm
                     -ldl
                     -flat_namespace
                     -g
                     )
