# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jia/code/netdisk/serverc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jia/code/netdisk/serverc/build

# Include any dependencies generated for this target.
include CMakeFiles/serverc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/serverc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serverc.dir/flags.make

CMakeFiles/serverc.dir/command.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/command.c.o: ../command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/serverc.dir/command.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/command.c.o   -c /home/jia/code/netdisk/serverc/command.c

CMakeFiles/serverc.dir/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/command.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/command.c > CMakeFiles/serverc.dir/command.c.i

CMakeFiles/serverc.dir/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/command.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/command.c -o CMakeFiles/serverc.dir/command.c.s

CMakeFiles/serverc.dir/common.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/common.c.o: ../common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/serverc.dir/common.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/common.c.o   -c /home/jia/code/netdisk/serverc/common.c

CMakeFiles/serverc.dir/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/common.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/common.c > CMakeFiles/serverc.dir/common.c.i

CMakeFiles/serverc.dir/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/common.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/common.c -o CMakeFiles/serverc.dir/common.c.s

CMakeFiles/serverc.dir/config.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/config.c.o: ../config.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/serverc.dir/config.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/config.c.o   -c /home/jia/code/netdisk/serverc/config.c

CMakeFiles/serverc.dir/config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/config.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/config.c > CMakeFiles/serverc.dir/config.c.i

CMakeFiles/serverc.dir/config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/config.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/config.c -o CMakeFiles/serverc.dir/config.c.s

CMakeFiles/serverc.dir/factory.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/factory.c.o: ../factory.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/serverc.dir/factory.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/factory.c.o   -c /home/jia/code/netdisk/serverc/factory.c

CMakeFiles/serverc.dir/factory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/factory.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/factory.c > CMakeFiles/serverc.dir/factory.c.i

CMakeFiles/serverc.dir/factory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/factory.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/factory.c -o CMakeFiles/serverc.dir/factory.c.s

CMakeFiles/serverc.dir/main.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/serverc.dir/main.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/main.c.o   -c /home/jia/code/netdisk/serverc/main.c

CMakeFiles/serverc.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/main.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/main.c > CMakeFiles/serverc.dir/main.c.i

CMakeFiles/serverc.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/main.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/main.c -o CMakeFiles/serverc.dir/main.c.s

CMakeFiles/serverc.dir/md5.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/md5.c.o: ../md5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/serverc.dir/md5.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/md5.c.o   -c /home/jia/code/netdisk/serverc/md5.c

CMakeFiles/serverc.dir/md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/md5.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/md5.c > CMakeFiles/serverc.dir/md5.c.i

CMakeFiles/serverc.dir/md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/md5.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/md5.c -o CMakeFiles/serverc.dir/md5.c.s

CMakeFiles/serverc.dir/mysql_cmd.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/mysql_cmd.c.o: ../mysql_cmd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/serverc.dir/mysql_cmd.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/mysql_cmd.c.o   -c /home/jia/code/netdisk/serverc/mysql_cmd.c

CMakeFiles/serverc.dir/mysql_cmd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/mysql_cmd.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/mysql_cmd.c > CMakeFiles/serverc.dir/mysql_cmd.c.i

CMakeFiles/serverc.dir/mysql_cmd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/mysql_cmd.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/mysql_cmd.c -o CMakeFiles/serverc.dir/mysql_cmd.c.s

CMakeFiles/serverc.dir/openssl_md5.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/openssl_md5.c.o: ../openssl_md5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/serverc.dir/openssl_md5.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/openssl_md5.c.o   -c /home/jia/code/netdisk/serverc/openssl_md5.c

CMakeFiles/serverc.dir/openssl_md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/openssl_md5.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/openssl_md5.c > CMakeFiles/serverc.dir/openssl_md5.c.i

CMakeFiles/serverc.dir/openssl_md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/openssl_md5.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/openssl_md5.c -o CMakeFiles/serverc.dir/openssl_md5.c.s

CMakeFiles/serverc.dir/tcp_init.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/tcp_init.c.o: ../tcp_init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/serverc.dir/tcp_init.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/tcp_init.c.o   -c /home/jia/code/netdisk/serverc/tcp_init.c

CMakeFiles/serverc.dir/tcp_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/tcp_init.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/tcp_init.c > CMakeFiles/serverc.dir/tcp_init.c.i

CMakeFiles/serverc.dir/tcp_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/tcp_init.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/tcp_init.c -o CMakeFiles/serverc.dir/tcp_init.c.s

CMakeFiles/serverc.dir/work_que.c.o: CMakeFiles/serverc.dir/flags.make
CMakeFiles/serverc.dir/work_que.c.o: ../work_que.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/serverc.dir/work_que.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverc.dir/work_que.c.o   -c /home/jia/code/netdisk/serverc/work_que.c

CMakeFiles/serverc.dir/work_que.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverc.dir/work_que.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/serverc/work_que.c > CMakeFiles/serverc.dir/work_que.c.i

CMakeFiles/serverc.dir/work_que.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverc.dir/work_que.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/serverc/work_que.c -o CMakeFiles/serverc.dir/work_que.c.s

# Object files for target serverc
serverc_OBJECTS = \
"CMakeFiles/serverc.dir/command.c.o" \
"CMakeFiles/serverc.dir/common.c.o" \
"CMakeFiles/serverc.dir/config.c.o" \
"CMakeFiles/serverc.dir/factory.c.o" \
"CMakeFiles/serverc.dir/main.c.o" \
"CMakeFiles/serverc.dir/md5.c.o" \
"CMakeFiles/serverc.dir/mysql_cmd.c.o" \
"CMakeFiles/serverc.dir/openssl_md5.c.o" \
"CMakeFiles/serverc.dir/tcp_init.c.o" \
"CMakeFiles/serverc.dir/work_que.c.o"

# External object files for target serverc
serverc_EXTERNAL_OBJECTS =

serverc: CMakeFiles/serverc.dir/command.c.o
serverc: CMakeFiles/serverc.dir/common.c.o
serverc: CMakeFiles/serverc.dir/config.c.o
serverc: CMakeFiles/serverc.dir/factory.c.o
serverc: CMakeFiles/serverc.dir/main.c.o
serverc: CMakeFiles/serverc.dir/md5.c.o
serverc: CMakeFiles/serverc.dir/mysql_cmd.c.o
serverc: CMakeFiles/serverc.dir/openssl_md5.c.o
serverc: CMakeFiles/serverc.dir/tcp_init.c.o
serverc: CMakeFiles/serverc.dir/work_que.c.o
serverc: CMakeFiles/serverc.dir/build.make
serverc: CMakeFiles/serverc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jia/code/netdisk/serverc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable serverc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serverc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serverc.dir/build: serverc

.PHONY : CMakeFiles/serverc.dir/build

CMakeFiles/serverc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serverc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serverc.dir/clean

CMakeFiles/serverc.dir/depend:
	cd /home/jia/code/netdisk/serverc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jia/code/netdisk/serverc /home/jia/code/netdisk/serverc /home/jia/code/netdisk/serverc/build /home/jia/code/netdisk/serverc/build /home/jia/code/netdisk/serverc/build/CMakeFiles/serverc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serverc.dir/depend

