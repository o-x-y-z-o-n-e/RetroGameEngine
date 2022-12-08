#!/bin/bash

[ ! -d "scripts" ] && cd ..

[ -d "bin" ] && rm -r "bin"
[ -d "tmp" ] && rm -r "tmp"

[ -f "Makefile" ] && rm "Makefile"
[ -f "engine/Makefile" ] && rm "engine/Makefile"
[ -f "examples/scenic/Makefile" ] && rm "examples/scenic/Makefile"
[ -f "examples/starship/Makefile" ] && rm "examples/starship/Makefile"