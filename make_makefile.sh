#!/bin/bash

"./premake5" gmake
printf '\n\ndoxygen:\n\tdoxygen\n' >> Makefile
