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
CMAKE_SOURCE_DIR = /mnt/c/Users/Arthur/CLionProjects/programas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Arthur/CLionProjects/programas/cmake-build-debug-wsl

# Include any dependencies generated for this target.
include CMakeFiles/programas.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/programas.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/programas.dir/flags.make

CMakeFiles/programas.dir/selectionsort.c.o: CMakeFiles/programas.dir/flags.make
CMakeFiles/programas.dir/selectionsort.c.o: ../selectionsort.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Arthur/CLionProjects/programas/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/programas.dir/selectionsort.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/programas.dir/selectionsort.c.o   -c /mnt/c/Users/Arthur/CLionProjects/programas/selectionsort.c

CMakeFiles/programas.dir/selectionsort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/programas.dir/selectionsort.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Arthur/CLionProjects/programas/selectionsort.c > CMakeFiles/programas.dir/selectionsort.c.i

CMakeFiles/programas.dir/selectionsort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/programas.dir/selectionsort.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Arthur/CLionProjects/programas/selectionsort.c -o CMakeFiles/programas.dir/selectionsort.c.s

# Object files for target programas
programas_OBJECTS = \
"CMakeFiles/programas.dir/selectionsort.c.o"

# External object files for target programas
programas_EXTERNAL_OBJECTS =

programas: CMakeFiles/programas.dir/selectionsort.c.o
programas: CMakeFiles/programas.dir/build.make
programas: CMakeFiles/programas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Arthur/CLionProjects/programas/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable programas"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/programas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/programas.dir/build: programas

.PHONY : CMakeFiles/programas.dir/build

CMakeFiles/programas.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/programas.dir/cmake_clean.cmake
.PHONY : CMakeFiles/programas.dir/clean

CMakeFiles/programas.dir/depend:
	cd /mnt/c/Users/Arthur/CLionProjects/programas/cmake-build-debug-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Arthur/CLionProjects/programas /mnt/c/Users/Arthur/CLionProjects/programas /mnt/c/Users/Arthur/CLionProjects/programas/cmake-build-debug-wsl /mnt/c/Users/Arthur/CLionProjects/programas/cmake-build-debug-wsl /mnt/c/Users/Arthur/CLionProjects/programas/cmake-build-debug-wsl/CMakeFiles/programas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/programas.dir/depend

