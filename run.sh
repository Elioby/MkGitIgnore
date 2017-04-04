#!/bin/bash
echo "Building..."
if gcc main.cpp -o mkgitignore -Wno-write-strings -lssl -lcrypto -lstdc++; then
    echo "Build succeeded, running output..."
    echo

    ./mkgitignore
else
    echo "Build failed."
fi