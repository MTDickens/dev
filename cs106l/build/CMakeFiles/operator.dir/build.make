# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/dev/CS106L

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/dev/CS106L/build

# Include any dependencies generated for this target.
include CMakeFiles/operator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/operator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/operator.dir/flags.make

CMakeFiles/operator.dir/operator.cpp.o: CMakeFiles/operator.dir/flags.make
CMakeFiles/operator.dir/operator.cpp.o: ../operator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/dev/CS106L/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/operator.dir/operator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/operator.dir/operator.cpp.o -c /workspaces/dev/CS106L/operator.cpp

CMakeFiles/operator.dir/operator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/operator.dir/operator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/dev/CS106L/operator.cpp > CMakeFiles/operator.dir/operator.cpp.i

CMakeFiles/operator.dir/operator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/operator.dir/operator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/dev/CS106L/operator.cpp -o CMakeFiles/operator.dir/operator.cpp.s

# Object files for target operator
operator_OBJECTS = \
"CMakeFiles/operator.dir/operator.cpp.o"

# External object files for target operator
operator_EXTERNAL_OBJECTS =

operator: CMakeFiles/operator.dir/operator.cpp.o
operator: CMakeFiles/operator.dir/build.make
operator: CMakeFiles/operator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/dev/CS106L/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable operator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/operator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/operator.dir/build: operator

.PHONY : CMakeFiles/operator.dir/build

CMakeFiles/operator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/operator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/operator.dir/clean

CMakeFiles/operator.dir/depend:
	cd /workspaces/dev/CS106L/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/dev/CS106L /workspaces/dev/CS106L /workspaces/dev/CS106L/build /workspaces/dev/CS106L/build /workspaces/dev/CS106L/build/CMakeFiles/operator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/operator.dir/depend

