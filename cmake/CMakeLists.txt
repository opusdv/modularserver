cmake_minimum_required(VERSION 3.22)

project(modularserver 
	VERSION 0.0.1
	DESCRIPTION "Modular server"
	LANGUAGES C
	)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined -g")

add_executable(main
	../src/main.c
	../src/config.c
	../src/connection.c
	../src/coreserver.c
	../src/plugin.c
	)

target_include_directories(main PRIVATE ../include/server/ )
target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Werror)
