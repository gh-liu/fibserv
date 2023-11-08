cmake_minimum_required(VERSION 3.21)
project(fibserv)

set(TARGET_FILE "http-echo-server")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 17)

include(CheckIncludeFiles)
check_include_files("pthread.h;stdatomic.h;sys/socket.h;netinet/in.h;unistd.h" EDEPS)
if (EPTHREAD EQUAL 1)
  message(FATAL_ERROR "Necessary header files are not found!")
endif()

include_directories(. /usr/local/include)

aux_source_directory(./src DIR_SRCS)
add_subdirectory(libs/)

find_package(uriparser 0.9.6 CONFIG REQUIRED char)

add_executable(${TARGET_FILE} ${DIR_SRCS})
target_link_libraries(${TARGET_FILE} PUBLIC core m pthread uriparser::uriparser)
