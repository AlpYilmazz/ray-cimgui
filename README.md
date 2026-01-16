# raycimgui

[Raylib][raylib-github] integration of
[cimgui][cimgui-github] which is a C translation of
the excellent C++ library [imgui][imgui-github].

version: 1.92.1

## CREDITS

This library is a C/cimgui adaptation of the
C++ Raylib/ImGui entegration library
[raylib-extras/rlImGui][rlImGui-github].

I created this library after all my tries to
figure out which cimgui version the library
[alfredbaudisch/raylib-cimgui][raylib-cimgui-github]
was implemented against proved unfruitful.

## CLONE
```
git clone <ray-cimgui>
cd ray-cimgui
git checkout <version>
git submodule update --init --recursive
```

## DEPENDENCIES

- [raylib][raylib-github]: 5.0
- [cimgui][cimgui-github]: 1.92.1
    - [imgui][imgui-github]: 1.92.1

`raycimgui` versions reflect the
cimgui version
one-to-one which is corralated with the .

## BUILD

For now,
only windows/wingw is tested and supported,
feel free to adapt and/or test on other platforms
before I get to it.

```
# build raycimgui
build.bat
    [--clean]
    [--make-cmd <make-cmd>]
    [--makefile <makefile-raycimgui>]
    [--ar <ar>]
    [--cc <c-compiler>]
    [--cxx <cpp-compiler>]

# test raycimgui
# build cimgui-test
build-exe.bat cimgui-test.c
    [--out <output>]

# run test
run.bat <output.exe>
```

Instead of building `raycimgui` as an external library,
you can directly include/reference the source code
as you need.

### raycimgui library usage

cimgui is built as a dynamic library (.dll),
so it requires dynamic linking
(static building requires very little work,
will support it ).

The library is built under directory `./raycimgui`.
After build, directory `raycimgui` contains
everything but raylib. You should link against
the correct version of raylib ([dependencies](#dependencies))
while building with `raycimgui`.

Feel free to check `build-exe.bat` as an usage example.

```
# include flags
-Iraycimgui/include

# lib flags
-Lraycimgui/lib

# link flags
-lcimgui -lraycimgui
```


[raylib-github]: https://github.com/raysan5/raylib
[cimgui-github]: https://github.com/cimgui/cimgui
[imgui-github]: https://github.com/ocornut/imgui
[raylib-cimgui-github]: https://github.com/alfredbaudisch/raylib-cimgui
[rlImGui-github]: https://github.com/raylib-extras/rlImGui
