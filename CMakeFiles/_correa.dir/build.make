# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jl65ai/correa_private

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jl65ai/correa_private

# Include any dependencies generated for this target.
include CMakeFiles/_correa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/_correa.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/_correa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/_correa.dir/flags.make

CMakeFiles/_correa.dir/src/correa.cpp.o: CMakeFiles/_correa.dir/flags.make
CMakeFiles/_correa.dir/src/correa.cpp.o: src/correa.cpp
CMakeFiles/_correa.dir/src/correa.cpp.o: CMakeFiles/_correa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jl65ai/correa_private/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/_correa.dir/src/correa.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/_correa.dir/src/correa.cpp.o -MF CMakeFiles/_correa.dir/src/correa.cpp.o.d -o CMakeFiles/_correa.dir/src/correa.cpp.o -c /Users/jl65ai/correa_private/src/correa.cpp

CMakeFiles/_correa.dir/src/correa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_correa.dir/src/correa.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jl65ai/correa_private/src/correa.cpp > CMakeFiles/_correa.dir/src/correa.cpp.i

CMakeFiles/_correa.dir/src/correa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_correa.dir/src/correa.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jl65ai/correa_private/src/correa.cpp -o CMakeFiles/_correa.dir/src/correa.cpp.s

# Object files for target _correa
_correa_OBJECTS = \
"CMakeFiles/_correa.dir/src/correa.cpp.o"

# External object files for target _correa
_correa_EXTERNAL_OBJECTS =

_correa.cpython-311-darwin.so: CMakeFiles/_correa.dir/src/correa.cpp.o
_correa.cpython-311-darwin.so: CMakeFiles/_correa.dir/build.make
_correa.cpython-311-darwin.so: libnanobind-static.a
_correa.cpython-311-darwin.so: CMakeFiles/_correa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jl65ai/correa_private/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module _correa.cpython-311-darwin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_correa.dir/link.txt --verbose=$(VERBOSE)
	/Library/Developer/CommandLineTools/usr/bin/strip -x /Users/jl65ai/correa_private/_correa.cpython-311-darwin.so

# Rule to build all files generated by this target.
CMakeFiles/_correa.dir/build: _correa.cpython-311-darwin.so
.PHONY : CMakeFiles/_correa.dir/build

CMakeFiles/_correa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/_correa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/_correa.dir/clean

CMakeFiles/_correa.dir/depend:
	cd /Users/jl65ai/correa_private && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jl65ai/correa_private /Users/jl65ai/correa_private /Users/jl65ai/correa_private /Users/jl65ai/correa_private /Users/jl65ai/correa_private/CMakeFiles/_correa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/_correa.dir/depend

