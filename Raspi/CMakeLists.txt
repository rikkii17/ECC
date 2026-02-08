cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#c++ÇÃç≈í·ÉoÅ[ÉWÉáÉìãKíˆ

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
)

project(ECC_device CXX)

set(
    SOURCES
        main.cpp
        src/app_tasks/clock_system.cpp
        config/hardconfig.cpp


)

add_executable(
    ECC_device
    ${SOURCES}
)

target_include_directories(
    ECC_device
    PUBLIC
    config
    inc/
    inc/app_tasks
    sfml-all
)