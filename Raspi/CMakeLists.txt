cmake_minimum_required(VERSION 3.10)

project(ECC_device CXX)

set(
    SOURCES
        main.cpp
        src/app_tasks/clock_system.cpp
<<<<<<< HEAD
        
=======
        config/hardconfig.cpp
>>>>>>> main

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
)