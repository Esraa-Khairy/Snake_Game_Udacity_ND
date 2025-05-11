# Snake Game - Final Project

## Project Overview

This is a classic Snake Game implemented in C++ using SDL2.  
The player controls a snake that collects food and grows longer while avoiding collisions with the walls or itself.  
If the snake collides, the game is over, and the player's score is displayed.

---
### ✅ Feature Coverage Summary

## ✅ Rubric Coverage Summary

### 🔁 Loops, Functions, I/O (✔ Meets at least 2)

- **✅ Project demonstrates C++ functions and control structures**
  - `game.cpp`: Uses `switch`, `if`, and loops for game logic.  
    Example: Lines 43–49 handle Game Over logic.
  - `controller.cpp`: `switch-case` manages key inputs.  
    Example: Line 39 implements pause functionality.

- **✅ Code is organized into functions**
  - Modular design includes:
    - `Game::Run`
    - `Game::LoadHighScore`
    - `Renderer::RenderGameOverScreen`

- **✅ Reads/Writes to a file**
  - `game.cpp`:
    - `loadHighScore()` and `saveHighScore()` handle score persistence using `high_score.txt`.
    - Reading: Lines 100–105  
    - Writing: Lines 129–154

- **✅ Accepts user input and processes it**
  - `controller.cpp`: Handles input for movement, pause (`P`), and exit (`ESC`).  
    Example: Line 39 manages user key handling.

---

### 🧱 Object-Oriented Programming (✔ Meets at least 3)

- **✅ Classes with access specifiers**
  - `game.h`, `snake.h`, `renderer.h`: Use `public`, `private`, and `protected` to enforce encapsulation.

- **✅ Member data is hidden and accessed via methods**
  - Example: `Game::isPaused()` provides controlled access to `is_paused`.

- **✅ Class constructors use member initializer lists**
  - `snake.cpp`:
    ```cpp
    Snake::Snake(float x, float y) : head_x(x), head_y(y) { ... }
    ```

- **⚠️ Overloaded function example**
  - Currently **not implemented**. Optional to add for additional rubric credit.

- **✅ Classes abstract implementation details**
  - Responsibilities:
    - `Game`: Game logic
    - `Renderer`: Graphics
    - `Controller`: User input

---

### 💾 Memory Management (✔ Meets at least 3)

- **✅ Pass-by-reference used in functions**
  - Example:
    ```cpp
    void Game::Run(Snake &snake, Renderer &renderer, Controller &controller);
    ```

- **✅ Uses RAII (Resource Acquisition Is Initialization)**
  - `std::ifstream` and `std::ofstream` used in `loadHighScore()` and `saveHighScore()` automatically release resources.

- **✅ Move semantics used**
  - Example:
    ```cpp
    togglePause() uses std::move(promise_pause);
    ```

---
## 🔄 Concurrency (✔ Meets at least 2)

✅ **Uses threads / async tasks**  
The function `Game::BonusFoodTimer()` runs in a separate thread and manages the visibility of bonus food over time using `std::chrono` and conditional waiting.

✅ **Mutex or lock used**  
`std::mutex bonus_mutex` is used along with `std::unique_lock` to synchronize access to shared state like `is_bonus_food_active`. This ensures that the timer loop can safely check and update the state.

✅ **Condition variable used**  
A `std::condition_variable condition_var` is used to put the bonus timer thread to sleep efficiently and avoid busy-waiting. It waits in intervals (`wait_for`) and re-checks the condition until the timer expires.

---


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



