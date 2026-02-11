cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#c++ÇÃç≈í·ÉoÅ[ÉWÉáÉìãKíˆ

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  csv_parser
  GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(csv_parser)

project(ECC_device CXX)

set(
    SOURCES
        main.cpp
        src/app_tasks/clock_system.cpp
        src/helper/initialization.cpp
        src/helper/filesystem.cpp
        config/softconfig.cpp
        config/errror.cpp
        


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
    inc/helper
)

target_link_libraries(
    ECC_device 
    sfml-window
    sfml-graphics
    csv
)