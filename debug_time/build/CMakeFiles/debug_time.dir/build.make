# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/johnmper/Documents/gits/cc_code_bits/debug_time

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/johnmper/Documents/gits/cc_code_bits/debug_time/build

# Include any dependencies generated for this target.
include CMakeFiles/debug_time.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/debug_time.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/debug_time.dir/flags.make

CMakeFiles/debug_time.dir/debug_time.cc.o: CMakeFiles/debug_time.dir/flags.make
CMakeFiles/debug_time.dir/debug_time.cc.o: ../debug_time.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/johnmper/Documents/gits/cc_code_bits/debug_time/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/debug_time.dir/debug_time.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/debug_time.dir/debug_time.cc.o -c /home/johnmper/Documents/gits/cc_code_bits/debug_time/debug_time.cc

CMakeFiles/debug_time.dir/debug_time.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/debug_time.dir/debug_time.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/johnmper/Documents/gits/cc_code_bits/debug_time/debug_time.cc > CMakeFiles/debug_time.dir/debug_time.cc.i

CMakeFiles/debug_time.dir/debug_time.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/debug_time.dir/debug_time.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/johnmper/Documents/gits/cc_code_bits/debug_time/debug_time.cc -o CMakeFiles/debug_time.dir/debug_time.cc.s

CMakeFiles/debug_time.dir/debug_time.cc.o.requires:

.PHONY : CMakeFiles/debug_time.dir/debug_time.cc.o.requires

CMakeFiles/debug_time.dir/debug_time.cc.o.provides: CMakeFiles/debug_time.dir/debug_time.cc.o.requires
	$(MAKE) -f CMakeFiles/debug_time.dir/build.make CMakeFiles/debug_time.dir/debug_time.cc.o.provides.build
.PHONY : CMakeFiles/debug_time.dir/debug_time.cc.o.provides

CMakeFiles/debug_time.dir/debug_time.cc.o.provides.build: CMakeFiles/debug_time.dir/debug_time.cc.o


CMakeFiles/debug_time.dir/main.cc.o: CMakeFiles/debug_time.dir/flags.make
CMakeFiles/debug_time.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/johnmper/Documents/gits/cc_code_bits/debug_time/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/debug_time.dir/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/debug_time.dir/main.cc.o -c /home/johnmper/Documents/gits/cc_code_bits/debug_time/main.cc

CMakeFiles/debug_time.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/debug_time.dir/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/johnmper/Documents/gits/cc_code_bits/debug_time/main.cc > CMakeFiles/debug_time.dir/main.cc.i

CMakeFiles/debug_time.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/debug_time.dir/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/johnmper/Documents/gits/cc_code_bits/debug_time/main.cc -o CMakeFiles/debug_time.dir/main.cc.s

CMakeFiles/debug_time.dir/main.cc.o.requires:

.PHONY : CMakeFiles/debug_time.dir/main.cc.o.requires

CMakeFiles/debug_time.dir/main.cc.o.provides: CMakeFiles/debug_time.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/debug_time.dir/build.make CMakeFiles/debug_time.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/debug_time.dir/main.cc.o.provides

CMakeFiles/debug_time.dir/main.cc.o.provides.build: CMakeFiles/debug_time.dir/main.cc.o


# Object files for target debug_time
debug_time_OBJECTS = \
"CMakeFiles/debug_time.dir/debug_time.cc.o" \
"CMakeFiles/debug_time.dir/main.cc.o"

# External object files for target debug_time
debug_time_EXTERNAL_OBJECTS =

debug_time: CMakeFiles/debug_time.dir/debug_time.cc.o
debug_time: CMakeFiles/debug_time.dir/main.cc.o
debug_time: CMakeFiles/debug_time.dir/build.make
debug_time: CMakeFiles/debug_time.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/johnmper/Documents/gits/cc_code_bits/debug_time/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable debug_time"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/debug_time.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/debug_time.dir/build: debug_time

.PHONY : CMakeFiles/debug_time.dir/build

CMakeFiles/debug_time.dir/requires: CMakeFiles/debug_time.dir/debug_time.cc.o.requires
CMakeFiles/debug_time.dir/requires: CMakeFiles/debug_time.dir/main.cc.o.requires

.PHONY : CMakeFiles/debug_time.dir/requires

CMakeFiles/debug_time.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/debug_time.dir/cmake_clean.cmake
.PHONY : CMakeFiles/debug_time.dir/clean

CMakeFiles/debug_time.dir/depend:
	cd /home/johnmper/Documents/gits/cc_code_bits/debug_time/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/johnmper/Documents/gits/cc_code_bits/debug_time /home/johnmper/Documents/gits/cc_code_bits/debug_time /home/johnmper/Documents/gits/cc_code_bits/debug_time/build /home/johnmper/Documents/gits/cc_code_bits/debug_time/build /home/johnmper/Documents/gits/cc_code_bits/debug_time/build/CMakeFiles/debug_time.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/debug_time.dir/depend

