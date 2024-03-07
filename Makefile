# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/sasha/sovyetski-soyouzy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sasha/sovyetski-soyouzy

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sasha/sovyetski-soyouzy/CMakeFiles /home/sasha/sovyetski-soyouzy//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sasha/sovyetski-soyouzy/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named SusieBrowser

# Build rule for target.
SusieBrowser: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 SusieBrowser
.PHONY : SusieBrowser

# fast build rule for target.
SusieBrowser/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/build
.PHONY : SusieBrowser/fast

#=============================================================================
# Target rules for targets named uninstall

# Build rule for target.
uninstall: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 uninstall
.PHONY : uninstall

# fast build rule for target.
uninstall/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/CMakeFiles/uninstall.dir/build.make lib/glfw/CMakeFiles/uninstall.dir/build
.PHONY : uninstall/fast

#=============================================================================
# Target rules for targets named glfw

# Build rule for target.
glfw: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 glfw
.PHONY : glfw

# fast build rule for target.
glfw/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/src/CMakeFiles/glfw.dir/build.make lib/glfw/src/CMakeFiles/glfw.dir/build
.PHONY : glfw/fast

#=============================================================================
# Target rules for targets named update_mappings

# Build rule for target.
update_mappings: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 update_mappings
.PHONY : update_mappings

# fast build rule for target.
update_mappings/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/src/CMakeFiles/update_mappings.dir/build.make lib/glfw/src/CMakeFiles/update_mappings.dir/build
.PHONY : update_mappings/fast

lib/glad/src/glad.o: lib/glad/src/glad.c.o
.PHONY : lib/glad/src/glad.o

# target to build an object file
lib/glad/src/glad.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/lib/glad/src/glad.c.o
.PHONY : lib/glad/src/glad.c.o

lib/glad/src/glad.i: lib/glad/src/glad.c.i
.PHONY : lib/glad/src/glad.i

# target to preprocess a source file
lib/glad/src/glad.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/lib/glad/src/glad.c.i
.PHONY : lib/glad/src/glad.c.i

lib/glad/src/glad.s: lib/glad/src/glad.c.s
.PHONY : lib/glad/src/glad.s

# target to generate assembly for a file
lib/glad/src/glad.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/lib/glad/src/glad.c.s
.PHONY : lib/glad/src/glad.c.s

src/html/parse.o: src/html/parse.c.o
.PHONY : src/html/parse.o

# target to build an object file
src/html/parse.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/html/parse.c.o
.PHONY : src/html/parse.c.o

src/html/parse.i: src/html/parse.c.i
.PHONY : src/html/parse.i

# target to preprocess a source file
src/html/parse.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/html/parse.c.i
.PHONY : src/html/parse.c.i

src/html/parse.s: src/html/parse.c.s
.PHONY : src/html/parse.s

# target to generate assembly for a file
src/html/parse.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/html/parse.c.s
.PHONY : src/html/parse.c.s

src/html/tree_utils.o: src/html/tree_utils.c.o
.PHONY : src/html/tree_utils.o

# target to build an object file
src/html/tree_utils.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/html/tree_utils.c.o
.PHONY : src/html/tree_utils.c.o

src/html/tree_utils.i: src/html/tree_utils.c.i
.PHONY : src/html/tree_utils.i

# target to preprocess a source file
src/html/tree_utils.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/html/tree_utils.c.i
.PHONY : src/html/tree_utils.c.i

src/html/tree_utils.s: src/html/tree_utils.c.s
.PHONY : src/html/tree_utils.s

# target to generate assembly for a file
src/html/tree_utils.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/html/tree_utils.c.s
.PHONY : src/html/tree_utils.c.s

src/main.o: src/main.c.o
.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/main.c.s
.PHONY : src/main.c.s

src/network/connect.o: src/network/connect.c.o
.PHONY : src/network/connect.o

# target to build an object file
src/network/connect.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/network/connect.c.o
.PHONY : src/network/connect.c.o

src/network/connect.i: src/network/connect.c.i
.PHONY : src/network/connect.i

# target to preprocess a source file
src/network/connect.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/network/connect.c.i
.PHONY : src/network/connect.c.i

src/network/connect.s: src/network/connect.c.s
.PHONY : src/network/connect.s

# target to generate assembly for a file
src/network/connect.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/network/connect.c.s
.PHONY : src/network/connect.c.s

src/network/http.o: src/network/http.c.o
.PHONY : src/network/http.o

# target to build an object file
src/network/http.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/network/http.c.o
.PHONY : src/network/http.c.o

src/network/http.i: src/network/http.c.i
.PHONY : src/network/http.i

# target to preprocess a source file
src/network/http.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/network/http.c.i
.PHONY : src/network/http.c.i

src/network/http.s: src/network/http.c.s
.PHONY : src/network/http.s

# target to generate assembly for a file
src/network/http.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/network/http.c.s
.PHONY : src/network/http.c.s

src/suzTK/pages.o: src/suzTK/pages.c.o
.PHONY : src/suzTK/pages.o

# target to build an object file
src/suzTK/pages.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/pages.c.o
.PHONY : src/suzTK/pages.c.o

src/suzTK/pages.i: src/suzTK/pages.c.i
.PHONY : src/suzTK/pages.i

# target to preprocess a source file
src/suzTK/pages.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/pages.c.i
.PHONY : src/suzTK/pages.c.i

src/suzTK/pages.s: src/suzTK/pages.c.s
.PHONY : src/suzTK/pages.s

# target to generate assembly for a file
src/suzTK/pages.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/pages.c.s
.PHONY : src/suzTK/pages.c.s

src/suzTK/stb_image_impl.o: src/suzTK/stb_image_impl.c.o
.PHONY : src/suzTK/stb_image_impl.o

# target to build an object file
src/suzTK/stb_image_impl.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/stb_image_impl.c.o
.PHONY : src/suzTK/stb_image_impl.c.o

src/suzTK/stb_image_impl.i: src/suzTK/stb_image_impl.c.i
.PHONY : src/suzTK/stb_image_impl.i

# target to preprocess a source file
src/suzTK/stb_image_impl.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/stb_image_impl.c.i
.PHONY : src/suzTK/stb_image_impl.c.i

src/suzTK/stb_image_impl.s: src/suzTK/stb_image_impl.c.s
.PHONY : src/suzTK/stb_image_impl.s

# target to generate assembly for a file
src/suzTK/stb_image_impl.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/stb_image_impl.c.s
.PHONY : src/suzTK/stb_image_impl.c.s

src/suzTK/text.o: src/suzTK/text.c.o
.PHONY : src/suzTK/text.o

# target to build an object file
src/suzTK/text.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/text.c.o
.PHONY : src/suzTK/text.c.o

src/suzTK/text.i: src/suzTK/text.c.i
.PHONY : src/suzTK/text.i

# target to preprocess a source file
src/suzTK/text.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/text.c.i
.PHONY : src/suzTK/text.c.i

src/suzTK/text.s: src/suzTK/text.c.s
.PHONY : src/suzTK/text.s

# target to generate assembly for a file
src/suzTK/text.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/text.c.s
.PHONY : src/suzTK/text.c.s

src/suzTK/window.o: src/suzTK/window.c.o
.PHONY : src/suzTK/window.o

# target to build an object file
src/suzTK/window.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/window.c.o
.PHONY : src/suzTK/window.c.o

src/suzTK/window.i: src/suzTK/window.c.i
.PHONY : src/suzTK/window.i

# target to preprocess a source file
src/suzTK/window.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/window.c.i
.PHONY : src/suzTK/window.c.i

src/suzTK/window.s: src/suzTK/window.c.s
.PHONY : src/suzTK/window.s

# target to generate assembly for a file
src/suzTK/window.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/suzTK/window.c.s
.PHONY : src/suzTK/window.c.s

src/utils/buffer.o: src/utils/buffer.c.o
.PHONY : src/utils/buffer.o

# target to build an object file
src/utils/buffer.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/utils/buffer.c.o
.PHONY : src/utils/buffer.c.o

src/utils/buffer.i: src/utils/buffer.c.i
.PHONY : src/utils/buffer.i

# target to preprocess a source file
src/utils/buffer.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/utils/buffer.c.i
.PHONY : src/utils/buffer.c.i

src/utils/buffer.s: src/utils/buffer.c.s
.PHONY : src/utils/buffer.s

# target to generate assembly for a file
src/utils/buffer.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/utils/buffer.c.s
.PHONY : src/utils/buffer.c.s

src/utils/logging.o: src/utils/logging.c.o
.PHONY : src/utils/logging.o

# target to build an object file
src/utils/logging.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/utils/logging.c.o
.PHONY : src/utils/logging.c.o

src/utils/logging.i: src/utils/logging.c.i
.PHONY : src/utils/logging.i

# target to preprocess a source file
src/utils/logging.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/utils/logging.c.i
.PHONY : src/utils/logging.c.i

src/utils/logging.s: src/utils/logging.c.s
.PHONY : src/utils/logging.s

# target to generate assembly for a file
src/utils/logging.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SusieBrowser.dir/build.make CMakeFiles/SusieBrowser.dir/src/utils/logging.c.s
.PHONY : src/utils/logging.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... uninstall"
	@echo "... update_mappings"
	@echo "... SusieBrowser"
	@echo "... glfw"
	@echo "... lib/glad/src/glad.o"
	@echo "... lib/glad/src/glad.i"
	@echo "... lib/glad/src/glad.s"
	@echo "... src/html/parse.o"
	@echo "... src/html/parse.i"
	@echo "... src/html/parse.s"
	@echo "... src/html/tree_utils.o"
	@echo "... src/html/tree_utils.i"
	@echo "... src/html/tree_utils.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/network/connect.o"
	@echo "... src/network/connect.i"
	@echo "... src/network/connect.s"
	@echo "... src/network/http.o"
	@echo "... src/network/http.i"
	@echo "... src/network/http.s"
	@echo "... src/suzTK/pages.o"
	@echo "... src/suzTK/pages.i"
	@echo "... src/suzTK/pages.s"
	@echo "... src/suzTK/stb_image_impl.o"
	@echo "... src/suzTK/stb_image_impl.i"
	@echo "... src/suzTK/stb_image_impl.s"
	@echo "... src/suzTK/text.o"
	@echo "... src/suzTK/text.i"
	@echo "... src/suzTK/text.s"
	@echo "... src/suzTK/window.o"
	@echo "... src/suzTK/window.i"
	@echo "... src/suzTK/window.s"
	@echo "... src/utils/buffer.o"
	@echo "... src/utils/buffer.i"
	@echo "... src/utils/buffer.s"
	@echo "... src/utils/logging.o"
	@echo "... src/utils/logging.i"
	@echo "... src/utils/logging.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
