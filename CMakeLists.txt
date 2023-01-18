cmake_minimum_required(VERSION 3.22)

project(gomoku-ai)

set(SOURCES
    src/Gomoku.cpp
    src/Defence.cpp
    src/Attack.cpp
    src/main.cpp
    src/Protocol.cpp
)


#set(EXECUTABLE_OUTPUT_PATH C:/Users/Mona/ETIPECH/B-AIA-500-BDX-5-1-gomoku-juliette.dupin/)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g")

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 PREFIX "pbrain-")

target_include_directories(${PROJECT_NAME}
    PUBLIC include
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(EXISTS ${CLANG_TIDY_EXE})
    set(CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        "-extra-arg=-std=c++17"
        "-warnings-as-errors=-*"
        "-header-filter=^.*(?:third-party).*gm")
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()
