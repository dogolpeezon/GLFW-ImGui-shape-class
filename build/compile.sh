#!/bin/bash
if [ -d "$CMakeFiles" ]||[ -f "$CMakeCache.txt" ];then
    echo -- "Clean up old CMakeFiles"
    rm -R CMakeFiles
    rm CMakeCache.txt
    rm cmake_install.cmake
    rm main
fi

echo -- "Build [cmake]"
cmake ..
echo -- "Build-finished [make]"

echo -n -e "\e[93mMake Application?\e[0m (y/n)"
read option
if echo "$option" | grep -iq "y" ;then
    make
    echo -n -e "\e[93mRun Appplication?\e[0m (y/n)"
    read option
    if echo "$option" | grep -iq "y" ;then
        echo -e "[Run] \e[93m Application -main\e[0m"
        ./main
    fi
fi
echo -- "Clean up old CMakeFiles"
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile
rm -R CMakeFiles
