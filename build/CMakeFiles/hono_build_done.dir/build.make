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

# Utility rule file for hono_build_done.

# Include the progress variables for this target.
include CMakeFiles/hono_build_done.dir/progress.make

CMakeFiles/hono_build_done:
	/opt/poky-agl/4.0.2/sysroots/x86_64-aglsdk-linux/usr/bin/cmake -E cmake_echo_color --cyan ++\ Typical\ binding\ launch:\ afb-daemon\ --rootdir=$$(pwd)/package\ --binding=$$(pwd)/package/lib/afb-hono.so\ --port=1234\ --workdir=/home/vgn5kor/Apps/hono-binding/build/package\ --ldpaths=lib\ --roothttp=htdocs\ \ --token=""\ --tracereq=common\ --verbose

hono_build_done: CMakeFiles/hono_build_done
hono_build_done: CMakeFiles/hono_build_done.dir/build.make

.PHONY : hono_build_done

# Rule to build all files generated by this target.
CMakeFiles/hono_build_done.dir/build: hono_build_done

.PHONY : CMakeFiles/hono_build_done.dir/build

CMakeFiles/hono_build_done.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hono_build_done.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hono_build_done.dir/clean

CMakeFiles/hono_build_done.dir/depend:
	cd /home/vgn5kor/Apps/hono-binding/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vgn5kor/Apps/hono-binding /home/vgn5kor/Apps/hono-binding /home/vgn5kor/Apps/hono-binding/build /home/vgn5kor/Apps/hono-binding/build /home/vgn5kor/Apps/hono-binding/build/CMakeFiles/hono_build_done.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hono_build_done.dir/depend
