cmake_minimum_required(VERSION 3.28)
project(test_generator)

set(CMAKE_CXX_STANDARD 23)

include_directories(lib/)

add_executable(test_generator src/main.cpp
        src/generators/cholesky_matrix.h
        src/data/matrix.h
        src/tools/metafunctions.h
        src/tools/cli.h
        src/tools/cli.cpp)
target_link_libraries(test_generator cblas)