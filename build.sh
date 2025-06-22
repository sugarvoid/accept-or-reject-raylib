#!/bin/bash

# Define variables for the compiler and flags
CC=gcc
COMPILER_FLAGS="-O2 -Wall -Wno-missing-braces"
LINKER_FLAGS="-L./lib/ -lraylib -lbox2d -lGL -lm -lpthread -ldl -lrt -lX11"

# Define the target executable
TARGET="accept-reject"

# Define the output folder for binaries
BIN_DIR="bin"

# Automatically get all .c files in the src directory
SRCS=$(find src -name "*.c")

# Generate object file names from source files
OBJS=""
for src in $SRCS; do
    OBJS="$OBJS ${src/.c/.o}"
done

# Function to compile source files into object files
compile() {
    for src in $SRCS; do
        echo "Compiling $src..."
        $CC $COMPILER_FLAGS -c $src -o ${src/.c/.o}
    done
}

# Function to link object files into the target executable
link() {
    echo "Linking $TARGET..."
    $CC $OBJS $COMPILER_FLAGS $LINKER_FLAGS -o "bin/$TARGET"
}

# Function to clean up build artifacts
clean() {
    echo "Cleaning up..."
    rm -f $OBJS $TARGET
    rm -rf $BIN_DIR/*
}

# Function to rebuild (clean and build)
rebuild() {
    clean
    build
}

# Function to build the project (native)
build() {
    compile
    link
}

# Function to run the executable
run() {
    echo "Running $TARGET..."
    ./"bin/"$TARGET
}

# Function to rebuild and run the executable
rebuild_and_run() {
    rebuild
    run
}

# Function to create a release build
release() {
    echo "Creating release build..."

    # Clean the previous build artifacts
    clean

    # Create the bin directory if it doesn't exist
    mkdir -p $BIN_DIR

    # Build the game
    build

    # Create a folder inside bin with the target name
    RELEASE_DIR="$BIN_DIR/$TARGET"
    mkdir -p $RELEASE_DIR

    # Copy the executable into the release directory
    mv $TARGET $RELEASE_DIR/

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
        release
        ;;
    *)
        rebuild_and_run
        ;;
esac
