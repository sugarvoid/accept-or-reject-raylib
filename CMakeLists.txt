cmake_minimum_required(VERSION 3.10)
project(Game LANGUAGES CXX)

set(TARGET ${PROJECT_NAME})

# Compile options
add_compile_options(-O2 -Wall -Wno-missing-braces)

# Output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Paths for source and headers
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")
set(LIBRARY_PATH "${PROJECT_SOURCE_DIR}/lib/libraylib.a")

# Gather source files
file(GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp")

# Create the executable
add_executable(${TARGET} ${CPPS})

# Include directories for headers
target_include_directories(${TARGET} PUBLIC ${INCLUDE_PATH})

# Link to raylib (assuming libraylib.a is the static library)
target_link_libraries(${TARGET} ${LIBRARY_PATH})

# Installation
install(TARGETS ${TARGET} RUNTIME DESTINATION bin)
