# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.21.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(raylib_cpp-populate NONE)

# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[/usr/local/bin/git]==])
set(GIT_VERSION_STRING [==[2.32.0]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[/usr/local/bin/git;2.32.0]==]
)


include(ExternalProject)
ExternalProject_Add(raylib_cpp-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/RobLoach/raylib-cpp.git" "GIT_TAG" "v4.1.0"
                    SOURCE_DIR          "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.11/cmake-build/_deps/raylib_cpp-src"
                    BINARY_DIR          "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.11/cmake-build/_deps/raylib_cpp-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


