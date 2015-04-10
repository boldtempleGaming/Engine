# boldtemple Game Engine
`version 0.2` (unstable pre-alpha) /
[Main Web](http://gaming.boldtemple.net/engine/bge/ "boldtemple Game Engine Main web") / 
[Documentation](http://boldtemplegaming.github.io/Engine/ "boldtemple Game Engine Documentation")

boldtemple Game Engine, build using C++11 and SDL2.
<br/>Cross Platform: `Windows`, `Linux`, `Macintosh`.

<br/>
___
<br/>


## Instructions
### #Build

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
2. Inside ***deps*** download and extract: **sdl2 ([`x32`](https://www.libsdl.org/release/SDL2-2.0.3-win32-x86.zip "SDL2-2.0.3-win32-x86.zip") or [`x64`](https://www.libsdl.org/release/SDL2-2.0.3-win32-x64.zip "SDL2-2.0.3-win32-x64.zip"))** / **[`sdl2 ttf`](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.12-mingw.tar.gz "SDL2_ttf-devel-2.0.12-mingw.tar.gz")** /
**[`sdl2 image`](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz "SDL2_image-devel-2.0.0-mingw.tar.gz")**.


<br/>**Linux**<br/>
Install dependencies:
```
$ sudo apt-get install g++ make cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev 
```
Build source:
```
$ cd /path/to/build/
$ cmake /path/to/folder/with/cmakelists
$ make -j4
```
*Where `-j4` is 4 parallel make jobs, it depends on your count of CPU cores.*


<br/>**Macintosh**<br/>
Soon..


<!-- **boldtemple Game Engine** -->
