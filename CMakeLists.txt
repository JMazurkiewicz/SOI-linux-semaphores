cmake_minimum_required(VERSION 3.10)

if(NOT UNIX OR APPLE)
    message(FATAL_ERROR "This project is only supported on Linux.")
endif()

project("SOI-LinuxSemaphores")

add_executable(
    semaphores

    src/main.c
    src/proc_data.c
    src/production.c
    src/qsem.c
    src/queue.c
    src/utility.c
)

find_package(Threads REQUIRED)
target_link_libraries(semaphores PRIVATE Threads::Threads rt)
target_include_directories(semaphores PUBLIC include)
