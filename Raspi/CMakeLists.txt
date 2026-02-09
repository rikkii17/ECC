cmake_minimum_required(VERSION 3.10)

project(ECC_device CXX)

set(
    SOURCES
        main.cpp
        src/app_tasks/clock_system.cpp
<<<<<<< HEAD
        config/hardconfig.cpp

)

add_executable(
    ECC_device
    ${SOURCES}
)

target_include_directories(
    ECC_device
    PUBLIC
<<<<<<< HEAD
    config
    inc/
    inc/app_tasks
=======
        config
        inc/
        inc/app_tasks
>>>>>>> 681d0418d4895eccdba423a24d64f1d71c8cda2e
)