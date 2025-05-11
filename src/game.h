#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <future>


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  // adding pause feature
  void togglePause();
  bool isPaused();
  // adding high score feature
  int getHighScore () const;

  //adding bonus food timer
  void BonusFoodTimer();
  void PlaceBonusFood();




 private:
  Snake snake;
  SDL_Point food;
  bool is_paused {false};
  std::mutex pause_mutex;
  std::promise<void> pause_promise;
  std::future<void> pause_future = pause_promise.get_future();

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
 // adding high score feature
  int high_score{0};
  void loadHighScore();
  void saveHighScore();

    // adding game over feature (red screen)
    bool game_over_shown{false};


  //adding bonus food timer
  std::thread bonusFoodThread;
  std::condition_variable condition_var;
  std::mutex bonus_mutex;
  bool is_bonus_food_active = false;
  bool bonus_food_already_appeared = false;
  SDL_Point bonus_food;
};

#endif