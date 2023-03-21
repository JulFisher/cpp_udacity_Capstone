//CapStone: Definition new level class introduce to snake game

#include <fstream>
#include <vector>
#include "SDL.h"

#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:

    Level(std::string _lvl_paths, size_t grid_width, size_t grid_height);
    ~Level();
    Level(const Level &source);
    Level(Level &&source);
    Level &operator=(const Level &source)
    {
            if (this == &source)
                return *this;
            if (_lvl_board != nullptr)
            {
                delete _lvl_board;
                _lvl_board = new std::vector<std::vector<int>>;
                *_lvl_board = *source._lvl_board;
            }
            _lvl_paths = source._lvl_paths;

            return *this;
    }

    Level &operator=(Level &&source)
    {
        _lvl_board = source._lvl_board;
        _lvl_paths = source._lvl_paths;
        source._lvl_board = nullptr;

        return *this;
    }

 

    auto get_lvl_board() -> std::vector<std::vector<int>>*;

    auto create_walls_from_board(const int lvl_number) -> void;

    auto WallCell(int x, int y) -> bool;

    auto get_walls() const -> std::vector<SDL_Point>;

    auto get_lvl_amount() -> size_t;



private:
    std::vector<std::string> _lvl_paths{};
    std::vector<std::vector<int>>* _lvl_board = new std::vector<std::vector<int>>{};;
    std::vector<SDL_Point> _wall_cells;
    size_t grid_width, grid_height;
    int size_factor_height{1}, size_factor_width{1};

    auto create_lvl_board(const int lvl_number) -> void;
    auto calculate_size_factors(const int lvl_number) -> void;
    auto ParseLine(std::string line) -> std::vector<int>;
};

#endif