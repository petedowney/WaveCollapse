# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.3_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.3_1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/petedowney/Documents/GitHub/WaveCollapse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/petedowney/Documents/GitHub/WaveCollapse/build

# Include any dependencies generated for this target.
include CMakeFiles/WaveCollapseInterface.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/WaveCollapseInterface.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/WaveCollapseInterface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WaveCollapseInterface.dir/flags.make

CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o: CMakeFiles/WaveCollapseInterface.dir/flags.make
CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o: ../src/WaveCollapseInt.cpp
CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o: CMakeFiles/WaveCollapseInterface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/petedowney/Documents/GitHub/WaveCollapse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o -MF CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o.d -o CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o -c /Users/petedowney/Documents/GitHub/WaveCollapse/src/WaveCollapseInt.cpp

CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/petedowney/Documents/GitHub/WaveCollapse/src/WaveCollapseInt.cpp > CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.i

CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/petedowney/Documents/GitHub/WaveCollapse/src/WaveCollapseInt.cpp -o CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.s

# Object files for target WaveCollapseInterface
WaveCollapseInterface_OBJECTS = \
"CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o"

# External object files for target WaveCollapseInterface
WaveCollapseInterface_EXTERNAL_OBJECTS =

WaveCollapseInterface.cpython-311-darwin.so: CMakeFiles/WaveCollapseInterface.dir/src/WaveCollapseInt.cpp.o
WaveCollapseInterface.cpython-311-darwin.so: CMakeFiles/WaveCollapseInterface.dir/build.make
WaveCollapseInterface.cpython-311-darwin.so: libWaveCollapse.a
WaveCollapseInterface.cpython-311-darwin.so: CMakeFiles/WaveCollapseInterface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/petedowney/Documents/GitHub/WaveCollapse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module WaveCollapseInterface.cpython-311-darwin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WaveCollapseInterface.dir/link.txt --verbose=$(VERBOSE)
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip -x /Users/petedowney/Documents/GitHub/WaveCollapse/build/WaveCollapseInterface.cpython-311-darwin.so

# Rule to build all files generated by this target.
CMakeFiles/WaveCollapseInterface.dir/build: WaveCollapseInterface.cpython-311-darwin.so
.PHONY : CMakeFiles/WaveCollapseInterface.dir/build

CMakeFiles/WaveCollapseInterface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WaveCollapseInterface.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WaveCollapseInterface.dir/clean

CMakeFiles/WaveCollapseInterface.dir/depend:
	cd /Users/petedowney/Documents/GitHub/WaveCollapse/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/petedowney/Documents/GitHub/WaveCollapse /Users/petedowney/Documents/GitHub/WaveCollapse /Users/petedowney/Documents/GitHub/WaveCollapse/build /Users/petedowney/Documents/GitHub/WaveCollapse/build /Users/petedowney/Documents/GitHub/WaveCollapse/build/CMakeFiles/WaveCollapseInterface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WaveCollapseInterface.dir/depend

