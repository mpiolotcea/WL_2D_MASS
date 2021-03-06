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

# Include any dependencies generated for this target.
include Tools/CMakeFiles/Tools.dir/depend.make

# Include the progress variables for this target.
include Tools/CMakeFiles/Tools.dir/progress.make

# Include the compile flags for this target's objects.
include Tools/CMakeFiles/Tools.dir/flags.make

Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o: Tools/CMakeFiles/Tools.dir/flags.make
Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o: ../Tools/src/lib/ShearInversions.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o"
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o -c /home/user/Work/Projects/WL_2D_MASS/1.0/Tools/src/lib/ShearInversions.cpp

Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.i"
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/user/Work/Projects/WL_2D_MASS/1.0/Tools/src/lib/ShearInversions.cpp > CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.i

Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.s"
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/user/Work/Projects/WL_2D_MASS/1.0/Tools/src/lib/ShearInversions.cpp -o CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.s

Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.requires:
.PHONY : Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.requires

Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.provides: Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.requires
	$(MAKE) -f Tools/CMakeFiles/Tools.dir/build.make Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.provides.build
.PHONY : Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.provides

Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.provides.build: Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o

# Object files for target Tools
Tools_OBJECTS = \
"CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o"

# External object files for target Tools
Tools_EXTERNAL_OBJECTS =

lib/libTools.so: Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o
lib/libTools.so: Tools/CMakeFiles/Tools.dir/build.make
lib/libTools.so: /opt/euclid/Elements/3.8/InstallArea/x86_64-co7-gcc48-o2g/lib/libElementsKernel.so
lib/libTools.so: /usr/lib64/libboost_filesystem-mt.so
lib/libTools.so: /usr/lib64/libboost_thread-mt.so
lib/libTools.so: /usr/lib64/libboost_program_options-mt.so
lib/libTools.so: /usr/lib64/libboost_system-mt.so
lib/libTools.so: /usr/lib64/libboost_regex-mt.so
lib/libTools.so: /usr/lib64/liblog4cpp.so
lib/libTools.so: Tools/CMakeFiles/Tools.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../lib/libTools.so"
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tools.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Detaching debug infos for libTools.so (Tools)."
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/lib && /usr/bin/objcopy --only-keep-debug libTools.so libTools.so.dbg
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/lib && /usr/bin/objcopy --strip-debug libTools.so
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/lib && /usr/bin/objcopy --add-gnu-debuglink=libTools.so.dbg libTools.so

# Rule to build all files generated by this target.
Tools/CMakeFiles/Tools.dir/build: lib/libTools.so
.PHONY : Tools/CMakeFiles/Tools.dir/build

Tools/CMakeFiles/Tools.dir/requires: Tools/CMakeFiles/Tools.dir/src/lib/ShearInversions.cpp.o.requires
.PHONY : Tools/CMakeFiles/Tools.dir/requires

Tools/CMakeFiles/Tools.dir/clean:
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools && $(CMAKE_COMMAND) -P CMakeFiles/Tools.dir/cmake_clean.cmake
.PHONY : Tools/CMakeFiles/Tools.dir/clean

Tools/CMakeFiles/Tools.dir/depend:
	cd /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Work/Projects/WL_2D_MASS/1.0 /home/user/Work/Projects/WL_2D_MASS/1.0/Tools /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools/CMakeFiles/Tools.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Tools/CMakeFiles/Tools.dir/depend

