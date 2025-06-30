#!/bin/bash

# Define variables for the compiler and flags
CC=gcc
COMPILER_FLAGS="-O2 -Wall -Wno-missing-braces -std=gnu99"
LINKER_FLAGS="-L./lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11" # -lbox2d

# Windows cross-compilation using DLL
WIN_CC=x86_64-w64-mingw32-gcc
RAYLIB_INCLUDE=include
WIN_RAYLIB_LIB=raylib_win
WIN_DLL="raylib_win/raylib.dll"  # path to the actual DLL

# You must have raylib.dll.a in the lib folder
WIN_LINKER_FLAGS="-L$WIN_RAYLIB_LIB -lraylib -lopengl32 -lgdi32 -lwinmm"


# Define the target executable
TARGET="accept-reject"

# Define the output folder for binaries
BIN_DIR="bin"

# Get all .c files in the src directory
SRCS=$(find src -name "*.c")

# Generate object file names from source files
OBJS=""
for src in $SRCS; do
    OBJS="$OBJS ${src/.c/.o}"
done

# Compile source files into object files
compile() {
    for src in $SRCS; do
        echo "Compiling $src..."
        $CC $COMPILER_FLAGS -c $src -o ${src/.c/.o}
    done
}

# Link object files into the target executable
link() {
    echo "Linking $TARGET..."
    $CC $OBJS $COMPILER_FLAGS $LINKER_FLAGS -o "bin/$TARGET"
}

# Clean up build artifacts
clean() {
    echo "Cleaning up..."
    rm -f $OBJS $TARGET
    rm -rf $BIN_DIR/*
}

rebuild() {
    clean
    build
}


build() {
    compile
    link
}

# Run the executable
run() {
    echo "Running $TARGET..."
    ./"bin/"$TARGET
}

rebuild_and_run() {
    rebuild
    run
}

windows() {
    echo "Cross-compiling for Windows (DLL)..."
    echo "Cleaning previous Windows build artifacts..."
    rm -f src/*.win.o
    rm -f "$BIN_DIR/$TARGET.exe"

    mkdir -p $BIN_DIR

    # Compile source files
    for src in $SRCS; do
        echo "Compiling $src..."
        $WIN_CC -c $src -o ${src/.c/.win.o} -I$RAYLIB_INCLUDE
    done

    # Gather object files
    WIN_OBJS=""
    for src in $SRCS; do
        WIN_OBJS="$WIN_OBJS ${src/.c/.win.o}"
    done

    # Link object files into Windows .exe
    $WIN_CC $WIN_OBJS $WIN_LINKER_FLAGS -o "$BIN_DIR/$TARGET.exe"

    # Copy the assets (resource folder) into the bin directory
    cp -r res "$BIN_DIR/"


    # Copy raylib.dll to the bin folder
    cp "$WIN_DLL" "$BIN_DIR/"

    echo "Windows build complete:"
    echo "  - EXE: $BIN_DIR/$TARGET.exe"
    echo "  - DLL: $BIN_DIR/raylib.dll"
}


# Create a linux release build
linux() {
    echo "Creating release build..."

    # Clean the previous build artifacts
    clean

    # Create the bin directory if it doesn't exist
    mkdir -p $BIN_DIR

    # Build the game
    build

    # Create a folder inside bin with the target name
    RELEASE_DIR="$BIN_DIR"
    mkdir -p $RELEASE_DIR

    # Copy the executable into the release directory
    # mv $TARGET $RELEASE_DIR

    # Copy the assets (or resource folder) into the release directory
    cp -r res $RELEASE_DIR/

    echo "Release build complete: $RELEASE_DIR/"
}

# Main logic to clean, rebuild, and run when no argument is provided
case "$1" in
    "clean")
        clean
        ;;
    "rebuild")
        rebuild
        ;;
    "run")
        run
        ;;
    "linux")
        clean
        linux
        ;;
    "windows")
        windows
        ;;
    *)
        linux
        ;;
esac
