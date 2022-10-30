#!/bin/bash

# exit script at first error
set -u -e

# Compile it and output to executable called 'app'
g++ *.cpp -lSDL2 -o app

# runs the app
./app