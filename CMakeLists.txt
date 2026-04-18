cmake_minimum_required(VERSION 3.14)
project(mini_projects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g -O0
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -D_GLIBCXX_ASSERTIONS
    )
    add_link_options(-fsanitize=address,undefined)
endif()

add_subdirectory(7SegmentsClock)
add_subdirectory(basicScheduler)
add_subdirectory(hangman)

# To build only a single project, comment out the above and uncomment below:
# set(TARGET_PROJECT "" CACHE STRING "Which project to build")
# if (NOT TARGET_PROJECT)
#     message(FATAL_ERROR "Set -DTARGET_PROJECT=project_name")
# endif()
# add_subdirectory(${TARGET_PROJECT})
