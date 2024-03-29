#include "game.h"
#include <iostream>
#include "SDL.h"
//CapStone: Added 'level' Object to initialization list.
Game::Game(std::size_t grid_width, std::size_t grid_height, std::string lvl_path)
    : snake(grid_width, grid_height),
      level(lvl_path, grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  //CapStone: update new member variables for game setup and set additional variable
  lvl_counter = level.get_lvl_amount();
  level.create_walls_from_board(lvl_number);
  bool level_change = false;


  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, level);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    //CapStone: Check if level should be change
    if (level_score != 0 && level_score % 10 == 0) 
    {
      level_change = true;
      lvl_number++;
      level_score = 0;
    }
    //CapStone: Add level change functionality
    if (level_change && lvl_number < lvl_counter)
    {
        level.create_walls_from_board(lvl_number);
        snake.speed -= 0.12;
        snake.ResetBody();
        level_change = false;
    }

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, lvl_number);
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
    //CapStone: check also if food is on no wall cell
    if (!snake.SnakeCell(x, y) && !level.WallCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update(level);

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    level_score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetLevel() const { return lvl_number; }