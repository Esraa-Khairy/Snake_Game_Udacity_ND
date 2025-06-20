#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>
#include <fstream>




Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  loadHighScore();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

  
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, *this);
    if(!(isPaused()))
    {
      Update();
      renderer.Render(snake, food, game_over_shown,bonus_food, is_bonus_food_active);

    }
    else
    {
      pause_future.wait();
      std::this_thread::sleep_for(std::chrono::microseconds(100));

    }
    
    if(!snake.alive && !game_over_shown)
    {
      std::cout <<"Game over! final score: " << score << std::endl;
      renderer.Render(snake,food,true,bonus_food, is_bonus_food_active);
      game_over_shown = true;
      SDL_Delay(2000);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count,high_score);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Snake eats normal food
  if (food.x == new_x && food.y == new_y) {
    score++;
    if (score > high_score) {
      high_score = score;
      saveHighScore();
    }
    PlaceFood();
    snake.GrowBody();
    snake.speed += 0.02;

    // Start bonus food thread
    if (!is_bonus_food_active && !bonus_food_already_appeared && score % 5 == 0) {
      PlaceBonusFood();
      is_bonus_food_active = true;
      bonus_food_already_appeared = true;
      bonusFoodThread = std::thread(&Game::BonusFoodTimer, this);
      bonusFoodThread.detach();
    }
  }

  // Snake eats bonus food
  if (bonus_food.x == new_x && bonus_food.y == new_y && is_bonus_food_active) {
    score += 3;  // bonus
    if (score > high_score) {
      high_score = score;
      saveHighScore();
    }
    is_bonus_food_active = false;
    bonus_food.x = -1;
    bonus_food.y = -1;
    bonus_food_already_appeared = false;
    condition_var.notify_all();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::togglePause()
{
  std::lock_guard<std::mutex> lock (pause_mutex);
  is_paused = !is_paused;
  std::cout << (is_paused? "Game paused \n" : "Game resumed \n");

  if(is_paused)
  {
    pause_promise.set_value();
  }
  else
  {
    std::promise<void> new_promise;
    pause_promise = std::move(new_promise);
    pause_future = pause_promise.get_future();
  }
}

bool Game::isPaused()
{
  std::lock_guard<std::mutex> lock(pause_mutex);
  return is_paused;
}

void Game::loadHighScore()
{
  std::ifstream file ("high_score.txt");
  if(file.is_open())
  {
    file >> high_score;

  }
  else
  {
    high_score = 0;
  }
}
void Game::saveHighScore()
{
  std::ofstream file ("high_Score.txt");
  if(file.is_open())
  {
    file << high_score;
  }
}

int Game::getHighScore() const
{
  return high_score;
}

void Game::BonusFoodTimer() {
  const int bonusSeconds = 10;
  auto startTime = std::chrono::high_resolution_clock::now();
  std::unique_lock<std::mutex> lock(bonus_mutex);

  while (is_bonus_food_active) {
    lock.unlock();
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(
                            currentTime - startTime).count();

    if (elapsedSeconds >= bonusSeconds) {
      // Bonus food disappears
      is_bonus_food_active = false;
      bonus_food.x = -1;
      bonus_food.y = -1;
      break;
    }

    lock.lock();
    condition_var.wait_for(lock, std::chrono::milliseconds(500));
  }
}

void Game::PlaceBonusFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    if (!snake.SnakeCell(x, y)) {
      bonus_food.x = x;
      bonus_food.y = y;
      return;
    }
  }
}