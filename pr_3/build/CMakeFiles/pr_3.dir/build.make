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
CMAKE_SOURCE_DIR = /home/amir/Desktop/luxoft-home-works/pr_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amir/Desktop/luxoft-home-works/pr_3

# Include any dependencies generated for this target.
include CMakeFiles/pr_3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pr_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pr_3.dir/flags.make

CMakeFiles/pr_3.dir/pr_3.cpp.o: CMakeFiles/pr_3.dir/flags.make
CMakeFiles/pr_3.dir/pr_3.cpp.o: pr_3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amir/Desktop/luxoft-home-works/pr_3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pr_3.dir/pr_3.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pr_3.dir/pr_3.cpp.o -c /home/amir/Desktop/luxoft-home-works/pr_3/pr_3.cpp

CMakeFiles/pr_3.dir/pr_3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pr_3.dir/pr_3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amir/Desktop/luxoft-home-works/pr_3/pr_3.cpp > CMakeFiles/pr_3.dir/pr_3.cpp.i

CMakeFiles/pr_3.dir/pr_3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pr_3.dir/pr_3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amir/Desktop/luxoft-home-works/pr_3/pr_3.cpp -o CMakeFiles/pr_3.dir/pr_3.cpp.s

# Object files for target pr_3
pr_3_OBJECTS = \
"CMakeFiles/pr_3.dir/pr_3.cpp.o"

# External object files for target pr_3
pr_3_EXTERNAL_OBJECTS =

pr_3: CMakeFiles/pr_3.dir/pr_3.cpp.o
pr_3: CMakeFiles/pr_3.dir/build.make
pr_3: CMakeFiles/pr_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amir/Desktop/luxoft-home-works/pr_3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pr_3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pr_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pr_3.dir/build: pr_3

.PHONY : CMakeFiles/pr_3.dir/build

CMakeFiles/pr_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pr_3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pr_3.dir/clean

CMakeFiles/pr_3.dir/depend:
	cd /home/amir/Desktop/luxoft-home-works/pr_3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amir/Desktop/luxoft-home-works/pr_3 /home/amir/Desktop/luxoft-home-works/pr_3 /home/amir/Desktop/luxoft-home-works/pr_3 /home/amir/Desktop/luxoft-home-works/pr_3 /home/amir/Desktop/luxoft-home-works/pr_3/CMakeFiles/pr_3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pr_3.dir/depend

