# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/build

# Include any dependencies generated for this target.
include CMakeFiles/peripheral_comm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/peripheral_comm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/peripheral_comm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/peripheral_comm.dir/flags.make

CMakeFiles/peripheral_comm.dir/example14.c.o: CMakeFiles/peripheral_comm.dir/flags.make
CMakeFiles/peripheral_comm.dir/example14.c.o: /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/example14.c
CMakeFiles/peripheral_comm.dir/example14.c.o: CMakeFiles/peripheral_comm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/peripheral_comm.dir/example14.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/peripheral_comm.dir/example14.c.o -MF CMakeFiles/peripheral_comm.dir/example14.c.o.d -o CMakeFiles/peripheral_comm.dir/example14.c.o -c /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/example14.c

CMakeFiles/peripheral_comm.dir/example14.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/peripheral_comm.dir/example14.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/example14.c > CMakeFiles/peripheral_comm.dir/example14.c.i

CMakeFiles/peripheral_comm.dir/example14.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/peripheral_comm.dir/example14.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/example14.c -o CMakeFiles/peripheral_comm.dir/example14.c.s

# Object files for target peripheral_comm
peripheral_comm_OBJECTS = \
"CMakeFiles/peripheral_comm.dir/example14.c.o"

# External object files for target peripheral_comm
peripheral_comm_EXTERNAL_OBJECTS =

peripheral_comm: CMakeFiles/peripheral_comm.dir/example14.c.o
peripheral_comm: CMakeFiles/peripheral_comm.dir/build.make
peripheral_comm: CMakeFiles/peripheral_comm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable peripheral_comm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/peripheral_comm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/peripheral_comm.dir/build: peripheral_comm
.PHONY : CMakeFiles/peripheral_comm.dir/build

CMakeFiles/peripheral_comm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/peripheral_comm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/peripheral_comm.dir/clean

CMakeFiles/peripheral_comm.dir/depend:
	cd /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9 /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9 /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/build /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/build /home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class9/build/CMakeFiles/peripheral_comm.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/peripheral_comm.dir/depend

