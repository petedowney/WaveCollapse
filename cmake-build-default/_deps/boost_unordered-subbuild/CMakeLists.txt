# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.19.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(boost_unordered-populate NONE)

include(ExternalProject)
ExternalProject_Add(boost_unordered-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/MikePopoloski/boost_unordered" "GIT_TAG" "v1.0" "GIT_SHALLOW" "ON"
                    SOURCE_DIR          "/Users/petedowney/Documents/GitHub/WaveCollapse/cmake-build-default/_deps/boost_unordered-src"
                    BINARY_DIR          "/Users/petedowney/Documents/GitHub/WaveCollapse/cmake-build-default/_deps/boost_unordered-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


