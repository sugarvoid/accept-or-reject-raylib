#!/bin/bash

# Define variables for the compiler and flags
CC=gcc
COMPILER_FLAGS="-O2 -Wall -Wno-missing-braces -std=gnu99"
LINKER_FLAGS="-L./lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11" # -lbox2d

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

# Create a linux release build
release() {
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
    "release")
        clean
        release
        ;;
    *)
        rebuild_and_run
        ;;
esac
