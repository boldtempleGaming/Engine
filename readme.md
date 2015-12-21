[![BGE](https://dl.dropboxusercontent.com/u/35777135/bge_logo.png)](#)

`version 0.3a` (unstable pre-alpha) /
[Main Web](http://gaming.boldtemple.net/engine/bge/ "boldtemple Game Engine Main web") / 
[Documentation](http://boldtemplegaming.github.io/Engine/ "boldtemple Game Engine Documentation") /
[TODO](https://github.com/boldtempleGaming/Engine/wiki/TODO "TODO")



boldtemple Game Engine, build using C++11 and SDL2.
<br/>Cross Platform: `Windows`, `Linux`, `OS X`.
<br/>

[![Build Status](https://travis-ci.org/boldtempleGaming/Engine.svg?branch=master)](https://travis-ci.org/boldtempleGaming/Engine) [![Gitter](https://badges.gitter.im/boldtempleGaming/Engine.svg)](https://gitter.im/boldtempleGaming/Engine?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

<br/>
## Features
**boldtemple Game Engine** it's a simple and lightweight 2d game framework:
* Sprite animation
* Simple AABB collision detection
* Camera controlling
* Widget system for making GUI
* Resource manager
 
**Soon:**
* Particle system
* Vector collision detection
* Scene manager 

<br/>
## Showcase
[![Animation](https://dl.dropboxusercontent.com/u/35777135/animation_small.gif)](#)

## Instructions
### - Build

<!--
> **Cross platform steps**
Soon..

| bgengine |
| :---- |
|`11111111111111111111111111111`|
--------------------
|  |  |
| ---- | ---- |
| a | b |
-->


<br/>**Windows**<br/>
Setup dependencies:

1. In engine root project, make new folder name it **`deps`**.
2. Inside ***`deps`*** download and extract: **[`SDL2`](https://www.libsdl.org/release/SDL2-devel-2.0.3-mingw.tar.gz")** + **[`SDL2_ttf`](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.12-mingw.tar.gz "SDL2_ttf-devel-2.0.12-mingw.tar.gz")** +
**[`SDL2_image`](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz "SDL2_image-devel-2.0.0-mingw.tar.gz")** + **[`SDL2_mixer`](https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.0-mingw.tar.gz")**.
3. Download [MinGW](http://sourceforge.net/projects/mingw/files/latest/download?source=files) and Install it using our guide, checking what to select from [*here*](http://gaming.boldtemple.net/engine/bge/files/media/mingw_ticks.png).
4. Download [CMake](www.cmake.org/download/) tool which uses **`CMakeLists.txt`** to generate project files/makefile.

Build source:
+ Link deps with in project, generate makefile then build:
```
mingw32-make -j4
```

<br/>**Linux**<br/>
Install dependencies:
```
$ sudo apt-get install g++ make cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```
Build source:
```
$ cd /path/to/build/
$ cmake /path/to/folder/with/cmakelists
$ make -j4
```
*Where `-j4` is 4 parallel make jobs, it depends on your count of CPU cores.*


<br/>**OS X**<br/>
Soon..


<!-- **boldtemple Game Engine** -->
