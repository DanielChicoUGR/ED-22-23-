# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /app/extra/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /app/extra/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniel/Proyectos/ED/P3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/Proyectos/ED/P3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bolsa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bolsa.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bolsa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bolsa.dir/flags.make

CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o: CMakeFiles/bolsa.dir/flags.make
CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o: ../estudiante/src/bolsa.cpp
CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o: CMakeFiles/bolsa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/Proyectos/ED/P3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o -MF CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o.d -o CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o -c /home/daniel/Proyectos/ED/P3/estudiante/src/bolsa.cpp

CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/Proyectos/ED/P3/estudiante/src/bolsa.cpp > CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.i

CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/Proyectos/ED/P3/estudiante/src/bolsa.cpp -o CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.s

# Object files for target bolsa
bolsa_OBJECTS = \
"CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o"

# External object files for target bolsa
bolsa_EXTERNAL_OBJECTS =

bolsa: CMakeFiles/bolsa.dir/estudiante/src/bolsa.cpp.o
bolsa: CMakeFiles/bolsa.dir/build.make
bolsa: CMakeFiles/bolsa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniel/Proyectos/ED/P3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bolsa"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bolsa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bolsa.dir/build: bolsa
.PHONY : CMakeFiles/bolsa.dir/build

CMakeFiles/bolsa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bolsa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bolsa.dir/clean

CMakeFiles/bolsa.dir/depend:
	cd /home/daniel/Proyectos/ED/P3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/Proyectos/ED/P3 /home/daniel/Proyectos/ED/P3 /home/daniel/Proyectos/ED/P3/cmake-build-debug /home/daniel/Proyectos/ED/P3/cmake-build-debug /home/daniel/Proyectos/ED/P3/cmake-build-debug/CMakeFiles/bolsa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bolsa.dir/depend

