# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/abhishek/Analysis/jetAnalysis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abhishek/Analysis/jetAnalysis/build

# Include any dependencies generated for this target.
include CMakeFiles/jetAna.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/jetAna.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/jetAna.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jetAna.dir/flags.make

CMakeFiles/jetAna.dir/jetAna.cxx.o: CMakeFiles/jetAna.dir/flags.make
CMakeFiles/jetAna.dir/jetAna.cxx.o: /home/abhishek/Analysis/jetAnalysis/jetAna.cxx
CMakeFiles/jetAna.dir/jetAna.cxx.o: CMakeFiles/jetAna.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/abhishek/Analysis/jetAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jetAna.dir/jetAna.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jetAna.dir/jetAna.cxx.o -MF CMakeFiles/jetAna.dir/jetAna.cxx.o.d -o CMakeFiles/jetAna.dir/jetAna.cxx.o -c /home/abhishek/Analysis/jetAnalysis/jetAna.cxx

CMakeFiles/jetAna.dir/jetAna.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jetAna.dir/jetAna.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhishek/Analysis/jetAnalysis/jetAna.cxx > CMakeFiles/jetAna.dir/jetAna.cxx.i

CMakeFiles/jetAna.dir/jetAna.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jetAna.dir/jetAna.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhishek/Analysis/jetAnalysis/jetAna.cxx -o CMakeFiles/jetAna.dir/jetAna.cxx.s

# Object files for target jetAna
jetAna_OBJECTS = \
"CMakeFiles/jetAna.dir/jetAna.cxx.o"

# External object files for target jetAna
jetAna_EXTERNAL_OBJECTS =

jetAna: CMakeFiles/jetAna.dir/jetAna.cxx.o
jetAna: CMakeFiles/jetAna.dir/build.make
jetAna: libJetAnalysis.so
jetAna: /usr/lib/root/libCore.so
jetAna: /usr/lib/root/libImt.so
jetAna: /usr/lib/root/libRIO.so
jetAna: /usr/lib/root/libNet.so
jetAna: /usr/lib/root/libHist.so
jetAna: /usr/lib/root/libGraf.so
jetAna: /usr/lib/root/libGraf3d.so
jetAna: /usr/lib/root/libGpad.so
jetAna: /usr/lib/root/libROOTDataFrame.so
jetAna: /usr/lib/root/libTree.so
jetAna: /usr/lib/root/libTreePlayer.so
jetAna: /usr/lib/root/libRint.so
jetAna: /usr/lib/root/libPostscript.so
jetAna: /usr/lib/root/libMatrix.so
jetAna: /usr/lib/root/libPhysics.so
jetAna: /usr/lib/root/libMathCore.so
jetAna: /usr/lib/root/libThread.so
jetAna: /usr/lib/root/libMultiProc.so
jetAna: /usr/lib/root/libROOTVecOps.so
jetAna: CMakeFiles/jetAna.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/abhishek/Analysis/jetAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jetAna"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jetAna.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jetAna.dir/build: jetAna
.PHONY : CMakeFiles/jetAna.dir/build

CMakeFiles/jetAna.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jetAna.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jetAna.dir/clean

CMakeFiles/jetAna.dir/depend:
	cd /home/abhishek/Analysis/jetAnalysis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abhishek/Analysis/jetAnalysis /home/abhishek/Analysis/jetAnalysis /home/abhishek/Analysis/jetAnalysis/build /home/abhishek/Analysis/jetAnalysis/build /home/abhishek/Analysis/jetAnalysis/build/CMakeFiles/jetAna.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/jetAna.dir/depend

