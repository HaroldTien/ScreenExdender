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
CMAKE_SOURCE_DIR = /home/harold/code/ScreenExtender

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/harold/code/ScreenExtender/build

# Include any dependencies generated for this target.
include CMakeFiles/ScreenExtender.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ScreenExtender.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ScreenExtender.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ScreenExtender.dir/flags.make

CMakeFiles/ScreenExtender.dir/src/main.cpp.o: CMakeFiles/ScreenExtender.dir/flags.make
CMakeFiles/ScreenExtender.dir/src/main.cpp.o: /home/harold/code/ScreenExtender/src/main.cpp
CMakeFiles/ScreenExtender.dir/src/main.cpp.o: CMakeFiles/ScreenExtender.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/harold/code/ScreenExtender/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ScreenExtender.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ScreenExtender.dir/src/main.cpp.o -MF CMakeFiles/ScreenExtender.dir/src/main.cpp.o.d -o CMakeFiles/ScreenExtender.dir/src/main.cpp.o -c /home/harold/code/ScreenExtender/src/main.cpp

CMakeFiles/ScreenExtender.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ScreenExtender.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harold/code/ScreenExtender/src/main.cpp > CMakeFiles/ScreenExtender.dir/src/main.cpp.i

CMakeFiles/ScreenExtender.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ScreenExtender.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harold/code/ScreenExtender/src/main.cpp -o CMakeFiles/ScreenExtender.dir/src/main.cpp.s

CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o: CMakeFiles/ScreenExtender.dir/flags.make
CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o: /home/harold/code/ScreenExtender/lib/MainFrame.cpp
CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o: CMakeFiles/ScreenExtender.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/harold/code/ScreenExtender/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o -MF CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o.d -o CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o -c /home/harold/code/ScreenExtender/lib/MainFrame.cpp

CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harold/code/ScreenExtender/lib/MainFrame.cpp > CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.i

CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harold/code/ScreenExtender/lib/MainFrame.cpp -o CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.s

CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o: CMakeFiles/ScreenExtender.dir/flags.make
CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o: /home/harold/code/ScreenExtender/lib/ConnectionCodeGeneration.cpp
CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o: CMakeFiles/ScreenExtender.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/harold/code/ScreenExtender/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o -MF CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o.d -o CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o -c /home/harold/code/ScreenExtender/lib/ConnectionCodeGeneration.cpp

CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harold/code/ScreenExtender/lib/ConnectionCodeGeneration.cpp > CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.i

CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harold/code/ScreenExtender/lib/ConnectionCodeGeneration.cpp -o CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.s

# Object files for target ScreenExtender
ScreenExtender_OBJECTS = \
"CMakeFiles/ScreenExtender.dir/src/main.cpp.o" \
"CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o" \
"CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o"

# External object files for target ScreenExtender
ScreenExtender_EXTERNAL_OBJECTS =

/home/harold/code/ScreenExtender/output/ScreenExtender: CMakeFiles/ScreenExtender.dir/src/main.cpp.o
/home/harold/code/ScreenExtender/output/ScreenExtender: CMakeFiles/ScreenExtender.dir/lib/MainFrame.cpp.o
/home/harold/code/ScreenExtender/output/ScreenExtender: CMakeFiles/ScreenExtender.dir/lib/ConnectionCodeGeneration.cpp.o
/home/harold/code/ScreenExtender/output/ScreenExtender: CMakeFiles/ScreenExtender.dir/build.make
/home/harold/code/ScreenExtender/output/ScreenExtender: CMakeFiles/ScreenExtender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/harold/code/ScreenExtender/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable /home/harold/code/ScreenExtender/output/ScreenExtender"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ScreenExtender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ScreenExtender.dir/build: /home/harold/code/ScreenExtender/output/ScreenExtender
.PHONY : CMakeFiles/ScreenExtender.dir/build

CMakeFiles/ScreenExtender.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ScreenExtender.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ScreenExtender.dir/clean

CMakeFiles/ScreenExtender.dir/depend:
	cd /home/harold/code/ScreenExtender/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/harold/code/ScreenExtender /home/harold/code/ScreenExtender /home/harold/code/ScreenExtender/build /home/harold/code/ScreenExtender/build /home/harold/code/ScreenExtender/build/CMakeFiles/ScreenExtender.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ScreenExtender.dir/depend

