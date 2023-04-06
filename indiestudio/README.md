# Indie Studio

The goal of this project is to re-create Bomberman

## Getting Started

This is how to install all dependencies you need to play the game.

### Prerequisites

1. make, gcc and git
    ```
    sudo apt install build-essential git
    ```

2. CMake
    ```
    sudo apt install cmake
    ```

### Installation and launch

1. Create thr build folder and download raylib through the CMakeLists file
    * On linux :
        ```
        mkdir build
        cd build
        cmake ..
        make
        ```
    * On Windows :
        ```
        mkdir build
        cd build
        cmake ..
        cmake --build .
        ```
2. The program is ready to launch !
    * On linux :
        ```
        ./bomberman
        ```
    * On Windows :
        Open the sln file generate by CMake on visual studio code and press ctrl + F5

Have fun playing our game !
