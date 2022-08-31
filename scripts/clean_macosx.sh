#!/bin/bash

[ ! -d "scripts" ] && cd ..

[ -d "bin" ] && rm -r "bin"
[ -d "tmp" ] && rm -r "tmp"

[ -f "Makefile" ] && rm "Makefile"
[ -f "engine/Makefile" ] && rm "engine/Makefile"
[ -f "example/Makefile" ] && rm "example/Makefile"