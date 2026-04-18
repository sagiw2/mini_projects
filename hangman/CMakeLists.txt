include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY  https://github.com/nlohmann/json.git
    GIT_TAG         v3.11.2
    GIT_SHALLOW     TRUE
    )

FetchContent_MakeAvailable(nlohmann_json)

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(hangman ${SOURCES})

target_link_libraries(hangman
                        PRIVATE
                        nlohmann_json::nlohmann_json
                    )