file(GLOB _SOURCES
        *.cpp
        *.h
    )

add_executable(7SegmentsClock
                ${_SOURCES}
            )

target_link_libraries(7SegmentsClock
                        PRIVATE
                        sfml-graphics sfml-window sfml-system
                    )
