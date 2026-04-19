file(GLOB _SOURCES
        *.cpp
        *.h
    )

add_executable(robotFSM
                ${_SOURCES}
            )
