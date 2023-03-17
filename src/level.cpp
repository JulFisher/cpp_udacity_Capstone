#include <level.h>
#include <fstream>
#include <sstream>
#include <memory>

Level::Level(int _lvl)
{
    _lvl_file = _lvl_folder + "level_" + std::to_string(_lvl) + ".board";
    _lvl_board = new std::vector<std::vector<int>>{};
    create_lvl_board(_lvl_file);
    create_walls_from_board();
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
        _lvl_file = source._lvl_file;
        _lvl_folder = source._lvl_folder;
}

Level::Level(Level &&source)
{
        _lvl_board = source._lvl_board;
        _lvl_file = source._lvl_file;
        _lvl_folder = source._lvl_folder;
        source._lvl_board = nullptr;
}

auto Level::create_lvl_board(const std::string _path) -> void
{
    std::ifstream lvl_file (_path);
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
