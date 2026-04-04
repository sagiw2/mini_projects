cmake_minimum_required(VERSION 3.10)
project(SevenSegmentsClock)

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


file(GLOB _SOURCES
        *.cpp
        *.h
    )

add_executable(app
                app.cpp
                ${_SOURCES}
            )

target_link_libraries(app
                        PRIVATE
                        sfml-graphics sfml-window sfml-system
                    )
