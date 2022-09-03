cmake_minimum_required(VERSION 3.13)  # CMake version check
project(repositoryStat)               # Create project "repositoryStat"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES
        source/main.cpp
        source/Class/Commit/Commit.cpp
        source/Class/Commit/Commit.hpp
        source/Class/CommitHandler/CommitsHandler.cpp
        source/Class/CommitHandler/CommitsHandler.hpp
        source/Class/Contributor/Contributor.cpp source/Class/Contributor/Contributor.hpp source/prettyPrinter.hpp source/utils.hpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(repositoryStat ${SOURCE_FILES})