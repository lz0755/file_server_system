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
CMAKE_SOURCE_DIR = /home/jia/code/netdisk/servers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jia/code/netdisk/servers/build

# Include any dependencies generated for this target.
include CMakeFiles/servers.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/servers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/servers.dir/flags.make

CMakeFiles/servers.dir/command.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/command.c.o: ../command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/servers.dir/command.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/command.c.o   -c /home/jia/code/netdisk/servers/command.c

CMakeFiles/servers.dir/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/command.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/command.c > CMakeFiles/servers.dir/command.c.i

CMakeFiles/servers.dir/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/command.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/command.c -o CMakeFiles/servers.dir/command.c.s

CMakeFiles/servers.dir/common.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/common.c.o: ../common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/servers.dir/common.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/common.c.o   -c /home/jia/code/netdisk/servers/common.c

CMakeFiles/servers.dir/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/common.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/common.c > CMakeFiles/servers.dir/common.c.i

CMakeFiles/servers.dir/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/common.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/common.c -o CMakeFiles/servers.dir/common.c.s

CMakeFiles/servers.dir/config.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/config.c.o: ../config.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/servers.dir/config.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/config.c.o   -c /home/jia/code/netdisk/servers/config.c

CMakeFiles/servers.dir/config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/config.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/config.c > CMakeFiles/servers.dir/config.c.i

CMakeFiles/servers.dir/config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/config.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/config.c -o CMakeFiles/servers.dir/config.c.s

CMakeFiles/servers.dir/factory.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/factory.c.o: ../factory.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/servers.dir/factory.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/factory.c.o   -c /home/jia/code/netdisk/servers/factory.c

CMakeFiles/servers.dir/factory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/factory.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/factory.c > CMakeFiles/servers.dir/factory.c.i

CMakeFiles/servers.dir/factory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/factory.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/factory.c -o CMakeFiles/servers.dir/factory.c.s

CMakeFiles/servers.dir/main.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/servers.dir/main.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/main.c.o   -c /home/jia/code/netdisk/servers/main.c

CMakeFiles/servers.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/main.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/main.c > CMakeFiles/servers.dir/main.c.i

CMakeFiles/servers.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/main.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/main.c -o CMakeFiles/servers.dir/main.c.s

CMakeFiles/servers.dir/md5.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/md5.c.o: ../md5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/servers.dir/md5.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/md5.c.o   -c /home/jia/code/netdisk/servers/md5.c

CMakeFiles/servers.dir/md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/md5.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/md5.c > CMakeFiles/servers.dir/md5.c.i

CMakeFiles/servers.dir/md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/md5.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/md5.c -o CMakeFiles/servers.dir/md5.c.s

CMakeFiles/servers.dir/mysql_cmd.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/mysql_cmd.c.o: ../mysql_cmd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/servers.dir/mysql_cmd.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/mysql_cmd.c.o   -c /home/jia/code/netdisk/servers/mysql_cmd.c

CMakeFiles/servers.dir/mysql_cmd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/mysql_cmd.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/mysql_cmd.c > CMakeFiles/servers.dir/mysql_cmd.c.i

CMakeFiles/servers.dir/mysql_cmd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/mysql_cmd.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/mysql_cmd.c -o CMakeFiles/servers.dir/mysql_cmd.c.s

CMakeFiles/servers.dir/openssl_md5.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/openssl_md5.c.o: ../openssl_md5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/servers.dir/openssl_md5.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/openssl_md5.c.o   -c /home/jia/code/netdisk/servers/openssl_md5.c

CMakeFiles/servers.dir/openssl_md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/openssl_md5.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/openssl_md5.c > CMakeFiles/servers.dir/openssl_md5.c.i

CMakeFiles/servers.dir/openssl_md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/openssl_md5.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/openssl_md5.c -o CMakeFiles/servers.dir/openssl_md5.c.s

CMakeFiles/servers.dir/tcp_init.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/tcp_init.c.o: ../tcp_init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/servers.dir/tcp_init.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/tcp_init.c.o   -c /home/jia/code/netdisk/servers/tcp_init.c

CMakeFiles/servers.dir/tcp_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/tcp_init.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/tcp_init.c > CMakeFiles/servers.dir/tcp_init.c.i

CMakeFiles/servers.dir/tcp_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/tcp_init.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/tcp_init.c -o CMakeFiles/servers.dir/tcp_init.c.s

CMakeFiles/servers.dir/work_que.c.o: CMakeFiles/servers.dir/flags.make
CMakeFiles/servers.dir/work_que.c.o: ../work_que.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/servers.dir/work_que.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/servers.dir/work_que.c.o   -c /home/jia/code/netdisk/servers/work_que.c

CMakeFiles/servers.dir/work_que.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/servers.dir/work_que.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jia/code/netdisk/servers/work_que.c > CMakeFiles/servers.dir/work_que.c.i

CMakeFiles/servers.dir/work_que.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/servers.dir/work_que.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jia/code/netdisk/servers/work_que.c -o CMakeFiles/servers.dir/work_que.c.s

# Object files for target servers
servers_OBJECTS = \
"CMakeFiles/servers.dir/command.c.o" \
"CMakeFiles/servers.dir/common.c.o" \
"CMakeFiles/servers.dir/config.c.o" \
"CMakeFiles/servers.dir/factory.c.o" \
"CMakeFiles/servers.dir/main.c.o" \
"CMakeFiles/servers.dir/md5.c.o" \
"CMakeFiles/servers.dir/mysql_cmd.c.o" \
"CMakeFiles/servers.dir/openssl_md5.c.o" \
"CMakeFiles/servers.dir/tcp_init.c.o" \
"CMakeFiles/servers.dir/work_que.c.o"

# External object files for target servers
servers_EXTERNAL_OBJECTS =

servers: CMakeFiles/servers.dir/command.c.o
servers: CMakeFiles/servers.dir/common.c.o
servers: CMakeFiles/servers.dir/config.c.o
servers: CMakeFiles/servers.dir/factory.c.o
servers: CMakeFiles/servers.dir/main.c.o
servers: CMakeFiles/servers.dir/md5.c.o
servers: CMakeFiles/servers.dir/mysql_cmd.c.o
servers: CMakeFiles/servers.dir/openssl_md5.c.o
servers: CMakeFiles/servers.dir/tcp_init.c.o
servers: CMakeFiles/servers.dir/work_que.c.o
servers: CMakeFiles/servers.dir/build.make
servers: CMakeFiles/servers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jia/code/netdisk/servers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable servers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/servers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/servers.dir/build: servers

.PHONY : CMakeFiles/servers.dir/build

CMakeFiles/servers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/servers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/servers.dir/clean

CMakeFiles/servers.dir/depend:
	cd /home/jia/code/netdisk/servers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jia/code/netdisk/servers /home/jia/code/netdisk/servers /home/jia/code/netdisk/servers/build /home/jia/code/netdisk/servers/build /home/jia/code/netdisk/servers/build/CMakeFiles/servers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/servers.dir/depend
