# Wolf3D

Wolf3D is a raycasting engine in the style of Wolfenstein 3D (1992). It is written in C and uses SDL3.

The engine adds these features:

- A command line in the game
- An MLG effect when you pick up a package of Doritos chips
- High-resolution textures
- Maps in plain text files

You can use the engine as a base for your own game. All textures, sprites, music files, and maps are in the `resources` folder. Replace them with your own files to make a new game.

## Controls

| Key | Action |
|---|---|
| `W`, `S` | Move forward, move back |
| `A`, `D` | Turn |
| `Left Shift` (hold) | Move faster |
| `Space` | Shoot |
| `Enter` | Open or close the command line |
| `F11` | Switch full-screen mode on or off |
| `Escape` | Exit (when the command line is closed) |

## Commands

To use a command, push `Enter`, type the command, and push `Enter` again.

| Command | Result |
|---|---|
| `praisethesun` | Heals you |
| `godmode` | Makes you immortal, or makes you mortal again |
| `goto N` | Sends you to level `N` |
| `displaymap` | Shows or hides the map of the level |
| `exit` | Exits the game |

## Map Format

A map is a text file in `resources/maps`:

```
[rows] [columns]
[column] [row]
[cell] ... [cell]
 ...        ...
[cell] ... [cell]
```

- The first line gives the size of the map. Each number is from 3 to 1024.
- The second line gives the start position of the player. Both numbers count from 1.
- The start cell must not be a wall. It must not be on the edge of the map.
- Each of the next lines is one row of the map. Spaces divide the cells.
- The game always makes the cells on the edge of the map into walls.

### Cell Format

A cell is a hexadecimal number with a maximum of 8 digits, for example `1ACB67FE`. A shorter number has zeros on the left. Thus, `3333` is the same as `00003333`.

| Digit | Meaning | Texture file |
|---|---|---|
| 1 | Solid sprite | — |
| 2 | Sprite | `sprite_N.png` |
| 3 | Floor | `side_N.jpg` |
| 4 | Ceiling | `side_N.jpg` |
| 5 | Left wall side | `wall_N.jpg` |
| 6 | Right wall side | `wall_N.jpg` |
| 7 | Bottom wall side | `wall_N.jpg` |
| 8 | Top wall side | `wall_N.jpg` |

Digit 1 is the digit on the left. The value of a digit selects the texture file with the same number. For example, digit `A` in position 5 selects `wall_A.jpg`.

- If one of the digits 5 to 8 is not 0, the cell is a wall.
- If the digits 1 and 2 are not 0, the player cannot move through the sprite.
- If a digit for a wall side, a floor, or a ceiling is 0, the game uses texture 1.

## Build

You need a C compiler, `make`, `pkg-config`, and the SDL3, SDL3_image, SDL3_ttf, and SDL3_mixer libraries.

1. Install the tools and the libraries for your system:
   - Fedora:
     ```sh
     sudo dnf install gcc make pkgconf-pkg-config SDL3-devel SDL3_image-devel SDL3_ttf-devel SDL3_mixer-devel
     ```
   - Debian testing, Ubuntu 26.10 or later. Debian 13 (stable) does not have `libsdl3-mixer-dev`.
     ```sh
     sudo apt install build-essential pkg-config libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev libsdl3-mixer-dev
     ```
   - macOS:
     ```sh
     xcode-select --install
     brew install pkgconf sdl3 sdl3_image sdl3_ttf sdl3_mixer
     ```
   - Windows: install [MSYS2](https://www.msys2.org) and open the UCRT64 shell.
     ```sh
     pacman -S make mingw-w64-ucrt-x86_64-{gcc,pkgconf,sdl3,sdl3-image,sdl3-ttf,sdl3-mixer}
     ```
2. In the project folder, build the game:
   ```sh
   make
   ```
3. Start the game:
   ```sh
   ./wolf3d
   ```

The game loads the `resources` folder from the folder of the executable. On Windows, the executable is `wolf3d.exe`.

To start `wolf3d.exe` outside of the MSYS2 shell, copy the DLL files that it uses into the project folder:

```sh
ldd wolf3d.exe | grep -o '/ucrt64/[^ ]*\.dll' | xargs cp -t .
```

---

Tested on Fedora Linux 44. The Windows build was tested under Wine.

Copyright © 2018 Stronautt (Pavlo Hrytsenko). This project uses the GNU General Public License v3. Refer to `LICENSE`.
