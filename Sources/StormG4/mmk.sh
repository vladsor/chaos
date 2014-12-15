#!/bin/bash

TARGET="storm"
TYPE="Kernel"
VERSION="G4.5.5"

SOURCES_DIR=$STORM_SOURCES
ARCHIVES_DIR=$CHAOS_ARCHIVES/$TYPE

case "$1" in
"-r") 
    BUILD=Release
    COMPILE_FLAGS="-O3 -funroll-loops -fomit-frame-pointer"
    PREPROCESSOR_FLAGS=""
    ;;
"-d") 
    BUILD=Debug
    COMPILE_FLAGS="-O0 -g"
    PREPROCESSOR_FLAGS=""
    ;;
"-g") 
    BUILD=DebugGDB
    COMPILE_FLAGS="-O0 -g -ggdb"
    PREPROCESSOR_FLAGS="-DGDB -DGDB_PORT=0 -DGDB_SPEED=9600"
    ;;
"-as")
	DATE_STRING=`date +%Y%m%d`
	make -s package-source \
            date_string="$DATE_STRING" \
            source_directory=$SOURCES_DIR \
            archive_directory="$ARCHIVES_DIR" \
	    --makefile=$SOURCES_DIR/Makefile
	exit
	;;
"-re")
    ln -sf $CHAOS_BINARIES/Release/Kernel $CHAOS_BINARIES/Kernel
    ;;
*) exit
esac

BINARIES_DIR=$CHAOS_BINARIES/$BUILD/$TYPE
OBJECTS_DIR=$CHAOS_OBJECTS/$BUILD/$TYPE

LOG_FILE=$OBJECTS_DIR/log

LINKER_FLAGS=""

if `test -f $BINARIES_DIR/.build`
then
    BUILD_COUNT=`cat $BINARIES_DIR/.build`
    echo Current build count: $BUILD_COUNT
else
    echo No build count
    BUILD_COUNT=0
fi


mkdir -p $BINARIES_DIR
mkdir -p $OBJECTS_DIR

if test $TERM = "cygwin" 
then
    echo Current is Cygwin
    LINKER_FLAGS="-Wl,-N -Wl,-Ttext -Wl,100000 -Wl,-e,_start"
    REFORMAT_COMMAND="objcopy -O elf32-i386 $BINARIES_DIR/storm.exe"
    MULTIBOOT_HEADER_ATTR='__attribute__ ((section (".init"), unused))'
else
    echo Current is $TERM
    MULTIBOOT_HEADER_ATTR="'__attribute__ ((section (\".init.pre\"), unused))'"
    LINKER_FLAGS="-Wl,-T,$CHAOS_ROOT/Tools/LinkerScripts/kernel.ld"
    REFORMAT_COMMAND="echo nothing for:"
fi

make -s deps \
    version="$VERSION" \
    preprocessor_flags="$PREPROCESSOR_FLAGS -DMULTIBOOT_HEADER_ATTR=$MULTIBOOT_HEADER_ATTR" \
    include_directories="$CHAOS_INCLUDES" \
    source_directory=$SOURCES_DIR \
    objects_directory=$OBJECTS_DIR \
    destination_directory=$BINARIES_DIR \
    --directory=$OBJECTS_DIR \
    --makefile=$SOURCES_DIR/Makefile


make -s \
    compile_flags="$COMPILE_FLAGS" \
    version="$VERSION" \
    build_count="$BUILD_COUNT" \
    preprocessor_flags="$PREPROCESSOR_FLAGS -DMULTIBOOT_HEADER_ATTR=$MULTIBOOT_HEADER_ATTR" \
    include_directories="$CHAOS_INCLUDES" \
    library_directories="$CHAOS_LIBRARIES" \
    modules_directory="$CHAOS_BINARIES/$BUILD/Modules/Static"\
    source_directory=$SOURCES_DIR \
    objects_directory=$OBJECTS_DIR \
    destination_directory=$BINARIES_DIR \
    libraries="list.a pool_of_integers.a pool_of_ranges.a avl_tree.a string.a hash_table.a" \
    modules="ata.a partition.a vfat.a" \
    linker_flags="$LINKER_FLAGS" \
    reformat_command="$REFORMAT_COMMAND" \
    --directory=$OBJECTS_DIR \
    --makefile=$SOURCES_DIR/Makefile

#libraries := list.a pool_of_integers.a pool_of_ranges.a avl_tree.a string.a
#unicode.a
#hash_table.a\
#"keyboard.a vga.a console.a"

#ata.a partition.a
# 
# vga.a console.a 
#pci.a pcnet32.a 
