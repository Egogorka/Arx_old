# Arx

## What it is

A student project for 3-nd semester of MIPT LPR.

## What we use (as of now)

1. **CLion**, as programming IDE
2.  [**MinGW Builds 7.3.0 (64-bit)**](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download), as a compiler for C++
3. C++ 17 standard
4. [**SFML-2.5.1**](https://www.sfml-dev.org/download/sfml/2.5.1/), as graphics library

## Setup

To setup a project first of all you need a folder structure as follows:
```
Arx-root
├─ Arx
└─ SFML-2.5.1
```

Where `SFML-2.5.1` stands for de-archived folder of SFML you downloaded.

Afterwards you need to `git-clone` in Arx folder our repository. In CLion you just press `Git / Clone...`
and enter the url to github repository and path to `Arx-root/Arx` in your system.

Then you need to set up a MinGW compiler in CLion - it's in `File / Settings` and then `Build, Execution and Deployment / Toolchains`. There you press + button and enter a path to your MinGW compiler