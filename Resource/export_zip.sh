#!/bin/bash

# WARNING! This script is made for UNIX system not for NT (a.k.a Windows)
# This script is designed to run on root folder of your problem that want to export.
# You can use this script with symlink (i'm make by using this method.)

if [[ "$OSTYPE" != linux-gnu* && "$OSTYPE" != darwin* ]]; then
    echo "Sorry! Please use Linux or Darwin or Your WSL."
    exit
fi

echo "This script need to use zip-cli. Are you install?"
read -p "Continue (y/n)?" choice
case "$choice" in 
  n|N ) echo "Please setup by using `sudo apt install zip unzip` if you're debian/ubuntu"; exit;;
esac

mkdir export
mkdir export/testdata
cp -r testcase/* export/testdata

cd export
zip -r ../problem.zip testdata
cd ..
rm -rf export

echo "Run finished! Please check at $(pwd)/problem.zip again."