#!/bin/bash

[ ! -d "scripts" ] && cd ..

"vendor/premake/bin/macosx-ARM64/premake5" gmake2
make