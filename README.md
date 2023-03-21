# CPPND: Capstone Snake Game Extension

The code for this repo is based on [this](https://github.com/udacity/CppND-Capstone-Snake-Game) which was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

The Snake Game was extended by different levels that can played when reaching enough points per level.

For this the existing file and class structure was extended by a new class 'Level'.
The 'Game' class now uses beside the objects of the classes 'Controller', 'Renderer' and 'Snake' a object of the new class 'Level'.
Several adaptions in the member function of all existing classes were done to integrate the new functionality.

In a new folder 'lvl' the level files are stored which the object of the new class 'Level' imports.

The added feature should work like this:

1. The game starts with a blank level as it was used to.
2. Every time after achieving a 'score % 20 == 0'  the next level should start.
    * New wall design should appear.
    * Snake body should reset.
    * Snake speed should be reduce by 1.2.
3. If the head of the snake touchs a wall the snake dies.
4. No food should be placed on a wall.

<img src="snake_game.gif"/>

## Tackled rupric points

General: All code additions / adaptions can be found with the flag "CapStone" in the code comments.

1. The project demonstrates an understanding of C++ functions and control structures.
    * E.g. if statement (game.cpp, line 43), for and while loops (level.cpp, line 44, 55, 77)
2. The project reads data from a file and process the data, or the program writes data to a file.
    * In the class Level function create_lvl_board(...) (level.cpp, line 37)
3. The project uses Object Oriented Programming techniques.
    * Introduced new class 'Level' (level.h, level.cpp)
4. Classes use appropriate access specifiers for class members.
    * Defined and implemented setter, getter, constructor, destructor for new class 'Level' (level.h, level.cpp)
5. Classes encapsulate behavior. (level.h, level.cpp)
6. The project makes use of references in function declarations. (level.h, line 18, 42, 48)
7. The project uses destructors appropriately. (level.cpp, line 15)
8. The project follows the Rule of 5.
    * Only for the new introduced class 'Level' (level.h, level.cpp)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## CC Attribution-ShareAlike 4.0 International

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
