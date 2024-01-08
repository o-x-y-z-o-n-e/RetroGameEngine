#!/bin/bash

[ ! -d "scripts" ] && cd ..

"vendor/premake/bin/linux-x86_64/premake5" gmake2
make