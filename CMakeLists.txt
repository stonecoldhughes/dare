set(CMAKE_C_COMPILER /Users/hhughe11/llvm_dir/build/bin/clang-4.0)

project(optimize C CXX)

include_directories(
                   /Users/hhughe11/libomp_oss/src
                   /Users/hhughe11/plasma/include
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
           )

target_link_libraries(
                     profile_lib
                     /Users/hhughe11/libomp_oss/src/libiomp5.dylib
                     -flat_namespace
                     )

target_link_libraries(
                     main
                     profile_lib
                     /Users/hhughe11/plasma/lib/libcoreblas.so
                     /Users/hhughe11/plasma/lib/libplasma.so
                     -lpthread
                     -lm
                     -ldl
                     -flat_namespace
                     -g
                     )
