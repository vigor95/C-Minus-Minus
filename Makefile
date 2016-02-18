# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:
.PHONY : .NOTPARALLEL

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
CMAKE_SOURCE_DIR = /home/vigor/workspace/C-Minus-Minus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vigor/workspace/C-Minus-Minus

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: install/strip
.PHONY : install/strip/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vigor/workspace/C-Minus-Minus/CMakeFiles /home/vigor/workspace/C-Minus-Minus/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vigor/workspace/C-Minus-Minus/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named cic

# Build rule for target.
cic: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cic
.PHONY : cic

# fast build rule for target.
cic/fast:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/build
.PHONY : cic/fast

# target to build an object file
buffer.o:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/buffer.o
.PHONY : buffer.o

# target to preprocess a source file
buffer.i:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/buffer.i
.PHONY : buffer.i

# target to generate assembly for a file
buffer.s:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/buffer.s
.PHONY : buffer.s

# target to build an object file
error.o:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/error.o
.PHONY : error.o

# target to preprocess a source file
error.i:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/error.i
.PHONY : error.i

# target to generate assembly for a file
error.s:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/error.s
.PHONY : error.s

# target to build an object file
file.o:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/file.o
.PHONY : file.o

# target to preprocess a source file
file.i:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/file.i
.PHONY : file.i

# target to generate assembly for a file
file.s:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/file.s
.PHONY : file.s

# target to build an object file
lex.o:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/lex.o
.PHONY : lex.o

# target to preprocess a source file
lex.i:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/lex.i
.PHONY : lex.i

# target to generate assembly for a file
lex.s:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/lex.s
.PHONY : lex.s

# target to build an object file
main.o:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/main.o
.PHONY : main.o

# target to preprocess a source file
main.i:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/main.i
.PHONY : main.i

# target to generate assembly for a file
main.s:
	$(MAKE) -f CMakeFiles/cic.dir/build.make CMakeFiles/cic.dir/main.s
.PHONY : main.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... cic"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... buffer.o"
	@echo "... buffer.i"
	@echo "... buffer.s"
	@echo "... error.o"
	@echo "... error.i"
	@echo "... error.s"
	@echo "... file.o"
	@echo "... file.i"
	@echo "... file.s"
	@echo "... lex.o"
	@echo "... lex.i"
	@echo "... lex.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

