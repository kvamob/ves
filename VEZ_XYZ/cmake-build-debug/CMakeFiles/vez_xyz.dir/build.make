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
CMAKE_SOURCE_DIR = D:\Git-REPOS\ves\VEZ_XYZ

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Git-REPOS\ves\VEZ_XYZ\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/VEZ_XYZ.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VEZ_XYZ.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VEZ_XYZ.dir/flags.make

CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.obj: CMakeFiles/VEZ_XYZ.dir/flags.make
CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.obj: ../VEZ_XYZ.C
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Git-REPOS\ves\VEZ_XYZ\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.obj"
	D:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\VEZ_XYZ.dir\VEZ_XYZ.C.obj -c D:\Git-REPOS\ves\VEZ_XYZ\VEZ_XYZ.C

CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.i"
	D:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Git-REPOS\ves\VEZ_XYZ\VEZ_XYZ.C > CMakeFiles\VEZ_XYZ.dir\VEZ_XYZ.C.i

CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.s"
	D:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Git-REPOS\ves\VEZ_XYZ\VEZ_XYZ.C -o CMakeFiles\VEZ_XYZ.dir\VEZ_XYZ.C.s

# Object files for target VEZ_XYZ
VEZ_XYZ_OBJECTS = \
"CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.obj"

# External object files for target VEZ_XYZ
VEZ_XYZ_EXTERNAL_OBJECTS =

VEZ_XYZ.exe: CMakeFiles/VEZ_XYZ.dir/VEZ_XYZ.C.obj
VEZ_XYZ.exe: CMakeFiles/VEZ_XYZ.dir/build.make
VEZ_XYZ.exe: CMakeFiles/VEZ_XYZ.dir/linklibs.rsp
VEZ_XYZ.exe: CMakeFiles/VEZ_XYZ.dir/objects1.rsp
VEZ_XYZ.exe: CMakeFiles/VEZ_XYZ.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Git-REPOS\ves\VEZ_XYZ\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VEZ_XYZ.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\VEZ_XYZ.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VEZ_XYZ.dir/build: VEZ_XYZ.exe

.PHONY : CMakeFiles/VEZ_XYZ.dir/build

CMakeFiles/VEZ_XYZ.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\VEZ_XYZ.dir\cmake_clean.cmake
.PHONY : CMakeFiles/VEZ_XYZ.dir/clean

CMakeFiles/VEZ_XYZ.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Git-REPOS\ves\VEZ_XYZ D:\Git-REPOS\ves\VEZ_XYZ D:\Git-REPOS\ves\VEZ_XYZ\cmake-build-debug D:\Git-REPOS\ves\VEZ_XYZ\cmake-build-debug D:\Git-REPOS\ves\VEZ_XYZ\cmake-build-debug\CMakeFiles\vez_xyz.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VEZ_XYZ.dir/depend
