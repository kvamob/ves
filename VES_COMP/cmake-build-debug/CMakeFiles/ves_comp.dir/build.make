# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\GIT-REPOS\ves\VES_COMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\GIT-REPOS\ves\VES_COMP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ves_comp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ves_comp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ves_comp.dir/flags.make

CMakeFiles/ves_comp.dir/Ves_comp.c.obj: CMakeFiles/ves_comp.dir/flags.make
CMakeFiles/ves_comp.dir/Ves_comp.c.obj: ../Ves_comp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GIT-REPOS\ves\VES_COMP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ves_comp.dir/Ves_comp.c.obj"
	D:\minGW-w64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ves_comp.dir\Ves_comp.c.obj   -c D:\GIT-REPOS\ves\VES_COMP\Ves_comp.c

CMakeFiles/ves_comp.dir/Ves_comp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ves_comp.dir/Ves_comp.c.i"
	D:\minGW-w64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\GIT-REPOS\ves\VES_COMP\Ves_comp.c > CMakeFiles\ves_comp.dir\Ves_comp.c.i

CMakeFiles/ves_comp.dir/Ves_comp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ves_comp.dir/Ves_comp.c.s"
	D:\minGW-w64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\GIT-REPOS\ves\VES_COMP\Ves_comp.c -o CMakeFiles\ves_comp.dir\Ves_comp.c.s

# Object files for target ves_comp
ves_comp_OBJECTS = \
"CMakeFiles/ves_comp.dir/Ves_comp.c.obj"

# External object files for target ves_comp
ves_comp_EXTERNAL_OBJECTS =

ves_comp.exe: CMakeFiles/ves_comp.dir/Ves_comp.c.obj
ves_comp.exe: CMakeFiles/ves_comp.dir/build.make
ves_comp.exe: CMakeFiles/ves_comp.dir/linklibs.rsp
ves_comp.exe: CMakeFiles/ves_comp.dir/objects1.rsp
ves_comp.exe: CMakeFiles/ves_comp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\GIT-REPOS\ves\VES_COMP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ves_comp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ves_comp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ves_comp.dir/build: ves_comp.exe

.PHONY : CMakeFiles/ves_comp.dir/build

CMakeFiles/ves_comp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ves_comp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ves_comp.dir/clean

CMakeFiles/ves_comp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\GIT-REPOS\ves\VES_COMP D:\GIT-REPOS\ves\VES_COMP D:\GIT-REPOS\ves\VES_COMP\cmake-build-debug D:\GIT-REPOS\ves\VES_COMP\cmake-build-debug D:\GIT-REPOS\ves\VES_COMP\cmake-build-debug\CMakeFiles\ves_comp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ves_comp.dir/depend

