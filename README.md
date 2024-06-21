# Zorya

> [!NOTE]
> Due to the browser taking up unreasonable amounts of RAM during runtime (and the code overall being a mess), the entire browser is currently being rewritten in the `rewrite` branch.

A small, lightweight web browser built (mainly) by Slavs.

## Building

#### Installing Dependencies

<details>
<summary>Windows</summary>

TBA

</details>

<details>
<summary>macOS</summary>

Make sure you have [Homebrew](https://brew.sh/) installed.

```bash
brew bundle
```

</details>

<details>
<summary>Debian-based distributions</summary>

```bash
sudo apt install cmake clang libsdl2{-dev,} libsdl2{-image,} libsdl2{-ttf.}
```

</details>

<details>
<summary>Arch-based distributions</summary>

```bash
sudo pacman -S cmake clang sdl2{_image,_ttf}
```

</details>

#### Setting up build environment

To maintain a clean repository structure, it is recommended to create a separate build directory where CMake will be invoked:

```bash
mkdir build/
cd build/
cmake -DCMAKE_BUILD_TYPE=Release ..
```

> [!TIP]
> You can run CMake with the `-G`  argument to generate project files for a different build system (ie. for Visual Studio). Click [here](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) for a list of all available CMake generators.

## Installing

TBA

### Generating installer packages

When inside the `build` directory, simply run
```bash
make package
```

This will create an installer/archive of a fresh build of the browser. Output can bee seen in the `build/pkg` directory.

## Screenshots

TBA

## License

Zorya Browser is licensed under the [GNU General Public License version 3](LICENSE.txt).
