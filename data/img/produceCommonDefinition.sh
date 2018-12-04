#!/usr/bin/env bash

echo "##########Textures ID###############"
echo "##########Textures ID###############"
echo "##########Textures ID###############"
ls -1 *.png | sort | sed -e 's/\..*$/,/'
echo end

echo "##########TextureFiles###############"
echo "##########TextureFiles###############"
echo "##########TextureFiles###############"
ls -1 *.png | sort | sed -e 's/$/",/' | sed -e 's/^/"/'
echo "##########MAP MAP###############"
echo "##########MAP MAP###############"
echo "##########MAP MAP###############"
# For Oskari Map Levelt Entity to Texture ID
for file in $(ls -1 *_alpha.png | sort | sed -e 's/\..*$//'); do
    echo "{ \"${file%_alpha}\", $file },";
done
