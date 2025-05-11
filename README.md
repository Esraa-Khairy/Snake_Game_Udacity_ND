# Snake Game - Final Project

## Project Overview

This is a classic Snake Game implemented in C++ using SDL2.  
The player controls a snake that collects food and grows longer while avoiding collisions with the walls or itself.  
If the snake collides, the game is over, and the player's score is displayed.

---
### ✅ Feature Coverage Summary

**Pause functionality**  
### ✅ Feature Coverage Summary

**Pause functionality**  
Covered in:
- `controller.cpp` – game pause is handled using `switch-case` statements that check when the 'P' key is pressed (Line 39).
- `game.cpp` – game pause is managed using `if` statements that check the paused state and the 'P' key input in the game loop. The game updates and renders only when not paused. (`Lines 31`)
- `game.h` – member variables like `is_paused`, `pause_mutex`, and functions like `togglePause()` and `isPaused()` are used to encapsulate pause behavior. (`Lines 19-31`)

**High score tracking**  
Covered in:
- `game.cpp` – functions `loadHighScore()` and `saveHighScore()` handle reading/writing `high_score.txt` for persistent score tracking. (`Lines 100-105`)(`Lines 129-154`)
- `game.h` – member variable `high_score` stores and updates the highest score internally. (`Line 42-48`)

**Game over screen**  
Addressed here:
- `game.cpp`, `renderer.cpp`, `snake.cpp` – game over logic is encapsulated in the `Game` class and related modules.
- `game.cpp` – `if` and `switch` statements manage the game over state and related events. (`Lines 43-49`)
- `renderer.cpp` – game over screen is rendered with a semi-transparent red overlay when the game ends. (`Line 75-87`)


---
### Dependencies for Running Locally

- **CMake** >= 3.7  
  [Click here for installation instructions](https://cmake.org/install/)

- **Make** >= 4.1 (Linux, Mac), 3.81 (Windows)  
  - **Linux**: `make` is installed by default on most Linux distros.
  - **Mac**: Install Xcode command line tools to get `make`.
  - **Windows**: [Click here for installation instructions](https://www.gnu.org/software/make/)

- **SDL2** >= 2.0  
  [All installation instructions can be found here](https://wiki.libsdl.org/Installation)

  *Note: For Linux, an apt or apt-get installation is preferred over building from source.*

- **gcc/g++** >= 5.4  
  - **Linux**: `gcc/g++` is installed by default on most Linux distros.
  - **Mac**: Same deal as `make` – install Xcode command line tools.
  - **Windows**: Recommend using MinGW.

---

### Basic Build Instructions

1. Clone this repo:

    git clone <repo_url>
    cd <repo_name>


2. Make a build directory in the top-level directory:

    mkdir build && cd build


3. Compile the project:

    cmake .. && make


4. Run the game:

    ./SnakeGame



