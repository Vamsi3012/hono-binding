# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/poky-agl/4.0.2/sysroots/x86_64-aglsdk-linux/usr/bin/cmake

# The command to remove a file.
RM = /opt/poky-agl/4.0.2/sysroots/x86_64-aglsdk-linux/usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vgn5kor/Apps/hono-binding

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vgn5kor/Apps/hono-binding/build

# Utility rule file for packaging_wgt.

# Include the progress variables for this target.
include CMakeFiles/packaging_wgt.dir/progress.make

CMakeFiles/packaging_wgt: package/config.xml


package/config.xml:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vgn5kor/Apps/hono-binding/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating package/config.xml"
	/opt/poky-agl/4.0.2/sysroots/x86_64-aglsdk-linux/usr/bin/cmake -DINFILE=/home/vgn5kor/Apps/hono-binding/conf.d/app-templates/template.d/config.xml.in -DOUTFILE=/home/vgn5kor/Apps/hono-binding/build/package/config.xml -DPROJECT_BINARY_DIR=/home/vgn5kor/Apps/hono-binding/build -P /home/vgn5kor/Apps/hono-binding/conf.d/app-templates/cmake/configure_file.cmake
	cp /home/vgn5kor/Apps/hono-binding/conf.d/wgt/icon_hybrid_qml_128.png /home/vgn5kor/Apps/hono-binding/build/package/icon_hybrid_qml_128.png

packaging_wgt: CMakeFiles/packaging_wgt
packaging_wgt: package/config.xml
packaging_wgt: CMakeFiles/packaging_wgt.dir/build.make

.PHONY : packaging_wgt

# Rule to build all files generated by this target.
CMakeFiles/packaging_wgt.dir/build: packaging_wgt

.PHONY : CMakeFiles/packaging_wgt.dir/build

CMakeFiles/packaging_wgt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/packaging_wgt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/packaging_wgt.dir/clean

CMakeFiles/packaging_wgt.dir/depend:
	cd /home/vgn5kor/Apps/hono-binding/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vgn5kor/Apps/hono-binding /home/vgn5kor/Apps/hono-binding /home/vgn5kor/Apps/hono-binding/build /home/vgn5kor/Apps/hono-binding/build /home/vgn5kor/Apps/hono-binding/build/CMakeFiles/packaging_wgt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/packaging_wgt.dir/depend
