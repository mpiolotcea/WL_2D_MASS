# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Work/Projects/WL_2D_MASS/1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g

# Utility rule file for rpmbuilddir.

# Include the progress variables for this target.
include CMakeFiles/rpmbuilddir.dir/progress.make

CMakeFiles/rpmbuilddir:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Packages/RPM as rpmbuild directory"
	/usr/bin/cmake -E make_directory /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Packages/RPM/BUILD
	/usr/bin/cmake -E make_directory /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Packages/RPM/BUILDROOT
	/usr/bin/cmake -E make_directory /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Packages/RPM/RPMS
	/usr/bin/cmake -E make_directory /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Packages/RPM/SRPMS
	/usr/bin/cmake -E make_directory /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Packages/RPM/BUILDROOT/WL_2D_MASS-1.0-1%{?dist}.x86_64

rpmbuilddir: CMakeFiles/rpmbuilddir
rpmbuilddir: CMakeFiles/rpmbuilddir.dir/build.make
.PHONY : rpmbuilddir

# Rule to build all files generated by this target.
CMakeFiles/rpmbuilddir.dir/build: rpmbuilddir
.PHONY : CMakeFiles/rpmbuilddir.dir/build

CMakeFiles/rpmbuilddir.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rpmbuilddir.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rpmbuilddir.dir/clean

CMakeFiles/rpmbuilddir.dir/depend:
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Work/Projects/WL_2D_MASS/1.0 /home/user/Work/Projects/WL_2D_MASS/1.0 /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/CMakeFiles/rpmbuilddir.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rpmbuilddir.dir/depend

