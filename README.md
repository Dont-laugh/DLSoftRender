# DLSoftRender

## Overview

Completely implemented from scratch with C++ 14. The repository is aim to implement a soft renderer only using `DrawPixel()` API.

## Dependencies

1. SDL2: [Simple DirectMedia Layer - Homepage (libsdl.org)](https://www.libsdl.org/)

## Milestones

- [ ] Render a picture
- [ ] Render a model
- [ ] Custom vertex & fragment shader
- [ ] Support alpha test & alpha blending
- [ ] Support shadows
- [ ] Implement MSAA, FXAA & TAA
- [ ] Implement ray tracing

## Quick start

Because this project is created by XMake, you have to install xmake first.

### Install XMake

Go to [Releases · xmake-io/xmake (github.com)](https://github.com/xmake-io/xmake/releases) and download for your platform, or install with `homebrew` on your Mac:

```shell
brew install xmake
```

For more infomation, visit: [Installation (xmake.io)](https://xmake.io/#/guide/installation).

### Windows

Firstly, clone the respository, then run xmake:

```shell
git clone https://github.com/Dont-laugh/DLSoftRender.git
cd DLSoftRender
xmake
xmake run
```

### Mac OS

You have to install SDL2 with `homebrew`:

```shell
brew install sdl2
```

Then follow along with the prompts in the windows that comes up.

## How to build

### Windows

Run command：

```shell
xmake project -k vsxmake -a x64
```

You will find a folder named `vsxmake20xx`，it depends on your Visual Studio's version. For example, it's name will be "vsxmake2019" if you have VS2019. Then open file "vsxmake20xx/DLSoftRenderer.sln".

### Mac OS

Run command:

```shell
xmake project -k xcode
```

Then open file "DLSoftRenderer.xcodeproj".
