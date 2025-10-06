#!/bin/bash
gcc -Iinclude/ -o glfw_test glfw_test.c glad.c -Llib/ -l:libglfw3.a -lGL -lm
