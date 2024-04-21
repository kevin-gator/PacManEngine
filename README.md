## Notes
This is my submission for the final project for the Building Game Engines course at Northeastern.

For this project, I recreated Pac Man in C++ using an ECS engine built from scratch in C++. I added support for
a level editor as well as the game itself, which can support playing or editing 10 different levels. Levels are
saved as text files representing them as tile grids.

When the program launches, the user is prompted with two text inputs, one to determine whether to open the
game or the editor, and another to choose which level to load (1-10).

Beyond the basic requirements of the final project for Building Game Engines, I decided it would be fun to
program simple AI navigation for the ghosts. I wanted to replicate the original behavior of the ghosts in
Pac Man, so I read this article about it: https://gameinternals.com/understanding-pac-man-ghost-behavior. I
replicated the basic AI states of chase, scatter, and frighten, although I simplified the scatter-chase loop
to use the same state durations every time (5 for scatter, 20 for frighten). I also didn't create unique
personalities for the individual ghosts. The only things differentiating the four ghosts is their sprite,
the time it takes them to "wake up", and the destination they run to when they are scattered. The AI behavior
is not totally perfect, and sometimes the ghosts will get stuck, but overall I'm happy with the state it's in.

## Game/Engine Publicity

**Project Website**: https://pacmanengine.my.canva.site/

## Compilation Instructions

Compile with clang++ -std=c++20 ./src/*.cpp -I./include -o bin/prog `pkg-config --libs sdl3`
Run with ./bin/prog

## Project Hierarchy

### ./Engine Directory Organization

- docs 
    - Source Code Documentation (Doxygen)
- assets
    - art: contains sprite images
    - levels: contains the 10 level text files
- src
    - source code (.cpp files)
- include
    - header files(.hpp files)
- lib
    - the libSDL3.dylib file resides here
- bin
    - This is the directory where the built executable is put after each build