# Retro Game Engine (RGE)
A simple 2D pixel software renderer.

A game framework for making retro aesthetic games. :)

## Core System Features
- Sprite rendering.
- ECS data model.
- Scene serialization [planned].
- Audio playback [work in progress].
- Physics system [planned].
- UI & text rendering [planned].

## Extra Included Projects
### Example Project
Cinematic scene to show off sprite rendering & input.

### MyGameBoy
A GameBoy emulator.
Currently only boots the BIOS. Heavy work in progress.

## How to use
The project is setup with a premake 5 build system.
No external dependencies required. Just link with the engine static library & include 'engine/include/api.h' in your project.

### Windows
Premake generates a Visual Studio 2022 solution.
Under root run 'scripts/gen_window.bat'. Then open 'Starship.sln'.
You can build the engine & all example projects within VS.

### MacOS
Run 'scripts/all_macosx.sh', which builds the engine & example project.
