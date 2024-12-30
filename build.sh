#!/bin/bash


# old version
#gcc ./src/*.c -o game -O2 -Wall -Wno-missing-braces -I ./include/ -I ./src/header/ -L ./lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 
#./game


CC=gcc
COMPILER_FLAGS="-O2 -Wall -Wno-missing-braces"
LINKER_FLAGS="-L./lib/ -lraylib -lbox2d -lGL -lm -lpthread -ldl -lrt -lX11"

### SRCS="src/main.c src/player.c"
SRCS=$(find src -name "*.c")
OBJS=""

for src in $SRCS; do
    OBJS="$OBJS ${src/.c/.o}"
done

# Define the target executable
TARGET="game"

# Function to compile source files into object files
compile() {
    for src in $SRCS; do
        echo "Compiling $src..."
        $CC $COMPILER_FLAGS -c $src -o ${src/.c/.o}
    done
}


link() {
    echo "Linking $TARGET..."
    $CC $OBJS $COMPILER_FLAGS $LINKER_FLAGS -o $TARGET
}

clean() {
    echo "Cleaning up..."
    rm -f $OBJS $TARGET
}

rebuild() {
    clean
    build
}

build() {
    compile
    link
}

run() {
    echo "Running $TARGET..."
    ./game
}

# Rebuild, and run
rbr() {
    rebuild
    run
}

# Main logic to clean, rebuild and run when no argument is provided
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
    *)
        rbr
        ;;
esac
