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
CMAKE_SOURCE_DIR = /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build

# Include any dependencies generated for this target.
include CMakeFiles/search-server-first.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/search-server-first.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/search-server-first.dir/flags.make

CMakeFiles/search-server-first.dir/main.cpp.o: CMakeFiles/search-server-first.dir/flags.make
CMakeFiles/search-server-first.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/search-server-first.dir/main.cpp.o"
	/bin/g++-10  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search-server-first.dir/main.cpp.o -c /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/main.cpp

CMakeFiles/search-server-first.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search-server-first.dir/main.cpp.i"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/main.cpp > CMakeFiles/search-server-first.dir/main.cpp.i

CMakeFiles/search-server-first.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search-server-first.dir/main.cpp.s"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/main.cpp -o CMakeFiles/search-server-first.dir/main.cpp.s

CMakeFiles/search-server-first.dir/parse.cpp.o: CMakeFiles/search-server-first.dir/flags.make
CMakeFiles/search-server-first.dir/parse.cpp.o: ../parse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/search-server-first.dir/parse.cpp.o"
	/bin/g++-10  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search-server-first.dir/parse.cpp.o -c /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/parse.cpp

CMakeFiles/search-server-first.dir/parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search-server-first.dir/parse.cpp.i"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/parse.cpp > CMakeFiles/search-server-first.dir/parse.cpp.i

CMakeFiles/search-server-first.dir/parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search-server-first.dir/parse.cpp.s"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/parse.cpp -o CMakeFiles/search-server-first.dir/parse.cpp.s

CMakeFiles/search-server-first.dir/search_server.cpp.o: CMakeFiles/search-server-first.dir/flags.make
CMakeFiles/search-server-first.dir/search_server.cpp.o: ../search_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/search-server-first.dir/search_server.cpp.o"
	/bin/g++-10  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search-server-first.dir/search_server.cpp.o -c /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/search_server.cpp

CMakeFiles/search-server-first.dir/search_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search-server-first.dir/search_server.cpp.i"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/search_server.cpp > CMakeFiles/search-server-first.dir/search_server.cpp.i

CMakeFiles/search-server-first.dir/search_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search-server-first.dir/search_server.cpp.s"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/search_server.cpp -o CMakeFiles/search-server-first.dir/search_server.cpp.s

# Object files for target search-server-first
search__server__first_OBJECTS = \
"CMakeFiles/search-server-first.dir/main.cpp.o" \
"CMakeFiles/search-server-first.dir/parse.cpp.o" \
"CMakeFiles/search-server-first.dir/search_server.cpp.o"

# External object files for target search-server-first
search__server__first_EXTERNAL_OBJECTS =

search-server-first: CMakeFiles/search-server-first.dir/main.cpp.o
search-server-first: CMakeFiles/search-server-first.dir/parse.cpp.o
search-server-first: CMakeFiles/search-server-first.dir/search_server.cpp.o
search-server-first: CMakeFiles/search-server-first.dir/build.make
search-server-first: CMakeFiles/search-server-first.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable search-server-first"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/search-server-first.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/search-server-first.dir/build: search-server-first

.PHONY : CMakeFiles/search-server-first.dir/build

CMakeFiles/search-server-first.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/search-server-first.dir/cmake_clean.cmake
.PHONY : CMakeFiles/search-server-first.dir/clean

CMakeFiles/search-server-first.dir/depend:
	cd /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build /home/danilshvalov/dev/c-plus-plus/c-plus-plus-learning/search-server-first/build/CMakeFiles/search-server-first.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/search-server-first.dir/depend

