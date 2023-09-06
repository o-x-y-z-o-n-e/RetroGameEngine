#!/bin/bash

[ ! -d "scripts" ] && cd ..

./scripts/build_macosx.sh

cd examples/2d
./../../bin/debug-macosx-ARM64/2d/2d