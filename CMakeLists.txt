cmake_minimum_required(VERSION 3.22)
project(test_generator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(lib/ /home/rvc1/Documents/dev/lib/include/)
link_directories(/home/rvc1/Documents/dev/lib/lib/)

add_executable(test_generator src/main.cpp
        src/generators/cholesky_matrix.h
        src/data/matrix.h
        src/tools/metafunctions.h
        src/tools/cli.h
        src/tools/cli.cpp)
target_link_libraries(test_generator openblas)
