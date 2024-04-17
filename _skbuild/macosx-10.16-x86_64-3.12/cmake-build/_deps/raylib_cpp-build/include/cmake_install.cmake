# Install script for directory: /Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-install/src")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/AudioDevice.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/AudioStream.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/BoundingBox.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Camera2D.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Camera3D.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Color.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Font.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Functions.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Gamepad.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Image.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Material.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Matrix.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Mesh.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Model.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/ModelAnimation.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Mouse.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Music.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/physac.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Physics.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Ray.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/RayCollision.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/RaylibException.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/raylib-cpp-utils.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/raylib-cpp.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/raylib.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/raymath.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Rectangle.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/RenderTexture.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Shader.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Sound.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Texture.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Vector2.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Vector3.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Vector4.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/VrStereoConfig.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Wave.hpp"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/_skbuild/macosx-10.16-x86_64-3.12/cmake-build/_deps/raylib_cpp-src/include/Window.hpp"
    )
endif()

