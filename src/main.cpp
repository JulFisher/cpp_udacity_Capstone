#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "level.h"
#include <string>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{64};
  constexpr std::size_t kGridHeight{64};
  //CapStone: new variable for path to level files
  const std::string kLvlPath{"../lvl"};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  //CapStone: Add input to game
  Game game(kGridWidth, kGridHeight, kLvlPath);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  //CapStone: Add output for achieved level
  std::cout << "Level: " << game.GetLevel() << "\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}