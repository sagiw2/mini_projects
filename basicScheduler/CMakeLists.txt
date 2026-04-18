file(GLOB _SOURCES
        *.cpp
        *.h
    )

add_executable(basicScheduler
                ${_SOURCES}
            )
