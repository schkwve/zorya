# Netwerk isnt a typo BLYAT
# WTF is this?
This is sovyetski-soyouzy, OUR Browser. A PERFECTLY Made Browser By Russians (Slavs).

# Why on earth?
Because normal browsers suck! bloated! telemetry! our browser is PERFECT.</br>
We PROMISE to be 
* Customizable
* Fast
* Telemetry-free

# Build guide(Linux only cuz fuck windows users)

```bash
git submodule update --init
mkdir build
cd build
cmake ..
make
```

# Packaging guide

After building, simply run:

```bash
make package
```

This will create:
 - A .app bundle and a DMG file on macOS
 - A .zip archive on Linux
 - An NSIS installer on Windows

