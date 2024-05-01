cmake_minimum_required(VERSION 3.19)
project(WaveCollapse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT boost_unordered_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            boost_unordered
            GIT_REPOSITORY https://github.com/MikePopoloski/boost_unordered
            GIT_TAG v1.0
            GIT_SHALLOW ON)

    FetchContent_MakeAvailable(boost_unordered)
endif()

if (NOT pybind11_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG v2.8.0
            GIT_SHALLOW ON)

    FetchContent_MakeAvailable(pybind11)

    # Configuration file generation
    configure_file(config.ini.in config.ini @ONLY)
endif()

include_directories(boost_unordered)
include_directories(pybind11)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)



#add_subdirectory(pybind11)
#target_link_libraries(boost_unordered raylib raylib_cpp)

add_library(WaveCollapse STATIC
src/Chunk.h src/Chunk.cpp src/WaveCollapse.cpp 
src/WaveCollapse.h src/WaveCollapseInt.cpp 
src/WaveCollapseInt.h)

target_link_libraries(WaveCollapse boost_unordered pybind11::module)


pybind11_add_module(WaveCollapseInterface src/WaveCollapseInt.cpp)
target_link_libraries(WaveCollapseInterface PRIVATE WaveCollapse)


#install(TARGETS WaveCollapseInterface LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib)
