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
CMAKE_SOURCE_DIR = /mnt/c/Users/Arthur/CLionProjects/TADponto!

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Arthur/CLionProjects/TADponto!/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TADponto_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TADponto_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TADponto_.dir/flags.make

CMakeFiles/TADponto_.dir/main.c.o: CMakeFiles/TADponto_.dir/flags.make
CMakeFiles/TADponto_.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Arthur/CLionProjects/TADponto!/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TADponto_.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TADponto_.dir/main.c.o   -c /mnt/c/Users/Arthur/CLionProjects/TADponto!/main.c

CMakeFiles/TADponto_.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TADponto_.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Arthur/CLionProjects/TADponto!/main.c > CMakeFiles/TADponto_.dir/main.c.i

CMakeFiles/TADponto_.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TADponto_.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Arthur/CLionProjects/TADponto!/main.c -o CMakeFiles/TADponto_.dir/main.c.s

# Object files for target TADponto_
TADponto__OBJECTS = \
"CMakeFiles/TADponto_.dir/main.c.o"

# External object files for target TADponto_
TADponto__EXTERNAL_OBJECTS =

TADponto_: CMakeFiles/TADponto_.dir/main.c.o
TADponto_: CMakeFiles/TADponto_.dir/build.make
TADponto_: CMakeFiles/TADponto_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Arthur/CLionProjects/TADponto!/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TADponto_"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TADponto_.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TADponto_.dir/build: TADponto_

.PHONY : CMakeFiles/TADponto_.dir/build

CMakeFiles/TADponto_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TADponto_.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TADponto_.dir/clean

CMakeFiles/TADponto_.dir/depend:
	cd /mnt/c/Users/Arthur/CLionProjects/TADponto!/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Arthur/CLionProjects/TADponto! /mnt/c/Users/Arthur/CLionProjects/TADponto! /mnt/c/Users/Arthur/CLionProjects/TADponto!/cmake-build-debug /mnt/c/Users/Arthur/CLionProjects/TADponto!/cmake-build-debug /mnt/c/Users/Arthur/CLionProjects/TADponto!/cmake-build-debug/CMakeFiles/TADponto_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TADponto_.dir/depend

