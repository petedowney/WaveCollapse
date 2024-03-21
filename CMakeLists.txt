cmake_minimum_required(VERSION 3.19)
project(WaveCollapse)

set(CMAKE_CXX_STANDARD 20)



if (NOT boost_unordered_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            boost_unordered
            GIT_REPOSITORY https://github.com/MikePopoloski/boost_unordered
            GIT_TAG v1.0
            GIT_SHALLOW ON)

    FetchContent_MakeAvailable(boost_unordered)
endif()

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 4.0.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG v4.1.0
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

include_directories(boost_unordered)
#target_link_libraries(boost_unordered raylib raylib_cpp)

add_executable(WaveCollapse source/main.cpp
        source/Chunk.h source/Chunk.cpp source/WaveCollapse.cpp source/WaveCollapse.h)

target_link_libraries(WaveCollapse raylib raylib_cpp boost_unordered)
        