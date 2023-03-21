//CapStone: Implementation of the new level class member functions

#include <level.h>
#include <fstream>
#include <sstream>
#include <memory>
#include <filesystem>

Level::Level(std::string _lvl_path)
{
    for(const auto & entry : std::filesystem::directory_iterator(_lvl_path))
        _lvl_paths.push_back(entry.path());
}

Level::~Level()
{
    if(_lvl_board != nullptr)
    {
        delete _lvl_board;
        _lvl_board = nullptr;
    }
}

Level::Level(const Level &source)
{
        _lvl_board = source._lvl_board;
        _lvl_paths = source._lvl_paths;
}

Level::Level(Level &&source)
{
        _lvl_board = source._lvl_board;
        _lvl_paths = source._lvl_paths;
        source._lvl_board = nullptr;
}

auto Level::create_lvl_board(const int lvl_number) -> void
{
    auto path = _lvl_paths[lvl_number];
    std::ifstream lvl_file (path);
    if (lvl_file)
    {
        std::string line;
        while (std::getline(lvl_file, line))
        {
            std::vector<int> row = ParseLine(line);
            _lvl_board->push_back(row);
        }
    }
}

auto Level::create_walls_from_board() -> void
{
    int x{0}, y{0};
    for (auto const &row : *_lvl_board)
    {
        for (auto const &column : row)
        {
            if (column == 1)
            {
                SDL_Point point{x, y};
                _wall_cells.push_back(point);
                y++;
            }
            else
            {
                y++;
            }
        }
        x++;
    }

}

auto Level::WallCell (int x, int y)-> bool
{
    for (auto const &cell : _wall_cells)
    {
        if (x == cell.x && y == cell.y)
        {
        return true;
        }
    }
    return false;
}

auto Level::get_walls() const -> std::vector<SDL_Point>
{
    return _wall_cells;
}


auto Level::ParseLine(std::string line) -> std::vector<int>
{
    std::istringstream sline(line);
    int n;
    char c;
    std::vector<int> row;
    while(sline >> n >> c && c == ',')
    {
        row.push_back(n);
    }
    return row;
}

auto Level::get_lvl_amount() -> size_t
{
    return _lvl_paths.size();
}
