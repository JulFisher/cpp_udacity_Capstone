#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "level.h"

class Game {
 public:
 //CapStone: add input path to level folder to constructor
  Game(std::size_t grid_width, std::size_t grid_height, std::string lvl_path);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  //CapStone: new getter function
  int GetLevel() const;

 private:
  Snake snake;
  Level level;
  SDL_Point food;
  int food_count;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  //CapStone: new private member variables
  int lvl_number{0};
  size_t lvl_counter{0};

  void PlaceFood();
  void Update();
  void ChangeLevel();
};

#endif