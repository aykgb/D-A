#!/bin/bash
for file in  $(ls | grep -vE ".cpp|.cc|.sh|.hpp|.md|.txt|.h|Makefile")
do
[ -f $file ] && {
    echo $file
    rm -f $file
}

[ -d $file ] && {
    if [[ "$file" = *\.dSYM ]]; then
        echo $file
        rm -rf $file
    fi
}
done