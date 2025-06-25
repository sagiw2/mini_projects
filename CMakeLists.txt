cmake_minimum_required(VERSION 3.14)
project(mini_projects)

set(TARGET_PROJECT "" CACHE STRING "Which project to build")
if (NOT TARGET_PROJECT)
    message(FATAL_ERROR "Set -DTARGET_PROJECT=project_name")
endif()

add_subdirectory(${TARGET_PROJECT})
