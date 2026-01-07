#root Directory CMakeListes

cmake_minimum_required(VERSION 3.10)

project(ECC_device CXX)

add_subdirectory(config)
add_subdirectory(drivers)
add_subdirectory(inc)
add_subdirectory(lib)
add_subdirectory(src)

target_link_libraries(
    clock_system
)



add_executable(ECC_device main.cpp)
