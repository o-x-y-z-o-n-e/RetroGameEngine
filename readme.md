# Retro Game Engine (RGE)
A single header-only game framework for making retro aesthetic games :)

This project is inspired by:
- [olc::PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)
- [Hazel](https://hazelengine.com)
- [Monogame](https://www.monogame.net)
- [Gunslinger](https://github.com/MrFrenik/gunslinger)
- [Pico-8](https://www.lexaloffle.com/pico-8.php)


## Core System Features
- Windows, Linux, & MacOS platform support.
- Software & OpenGL 1.0 2D/3D renderers.
- Entity component system [**planned**].
- Serialization system [**planned**].
- Audio playback [**planned**].
- Physics system [**planned**].
- UI & text rendering [**planned**].


## How to use
The entire project is a single header-only library. Just drop the 'rge.hpp' file your project directory. No external dependencies required.

Startup code example:
```C++
#define RGE_IMPL
#include <rge.hpp>

class game : public rge::engine {
public:
    game() : rge::engine() {
        
    }

    void on_init() override {
        
    }

	void on_update(float delta_time) override {
        
	}

    void on_render() override {
        
    }
};

int main(int argc, char** argv) {
    game* gm = new game();
	gm->create(true);
	gm->wait_for_exit();
	delete gm;
    return 0;
}
```

In your compiler, set one of these defines to compile support for that platform.
- SYS_WINDOWS
- SYS_LINUX
- SYS_MACOSX

In your compiler, Set one of these defines to compile support for that renderer.
- SYS_SOFTWARE_GL
- SYS_OPENGL_1_0

### Windows
Premake generates a Visual Studio 2022 solution.
Under root run 'scripts/gen_window.bat'. Then open 'retro_game_engine.sln'.
You can build the engine & all example projects within VS.


## Extra Included Projects
### Example Project
Cinematic scene to show off sprite rendering & input.


## Extra Credits
- Software renderer is a port of Adrian Clark's renderer for UC PROD321