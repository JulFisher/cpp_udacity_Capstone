#include <level.h>
#include <fstream>
#include <sstream>
#include <memory>

Level::Level(int _lvl)
{
    _lvl_file = "level_" + std::to_string(_lvl) + ".board";
    _lvl_board = new std::vector<std::vector<int>>{};

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
