//CapStone: Implementation of the new level class member functions

#include <level.h>
#include <fstream>
#include <sstream>
#include <memory>
#include <experimental/filesystem>

Level::Level(std::string _lvl_path, size_t grid_width, size_t grid_height) : grid_width(grid_width), grid_height(grid_height)
{
    for(const auto & entry : std::experimental::filesystem::directory_iterator(_lvl_path))
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
    _lvl_board->clear();
    calculate_size_factors(lvl_number);
    auto path = _lvl_paths[lvl_number];
    std::ifstream lvl_file (path);
    int count{0};
    if (lvl_file)
    {
        std::string line;
        while (std::getline(lvl_file, line))
        {
            std::vector<int> row = ParseLine(line);
            if (size_factor_height == 1) _lvl_board->push_back(row);
            else if (size_factor_height > 1)
                {
                    _lvl_board->push_back(row);
                    for(int i = 1; i < size_factor_height; i++) _lvl_board->push_back(row);
                }
            else
                {
                    if (count % static_cast<int>(1 / size_factor_height) == 0) _lvl_board->push_back(row);
                    ++count;
                }
            
        }
    }
}

auto Level::create_walls_from_board(const int lvl_number) -> void
{   
    create_lvl_board(lvl_number);
    int x{0}, y{0};
    _wall_cells.clear();
    auto test = *_lvl_board;
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
        y = 0;
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

    int count{0};
    std::vector<int> row;
    while(sline >> n >> c && c == ',')
    {   
        if (size_factor_width == 1) row.push_back(n);
        else if (size_factor_width > 1)
        {
            row.push_back(n);
            for(int i = 1; i < size_factor_width; i++) row.push_back(n);
        }
        else
        {    
            if (n == 1) row.push_back(n);
            else if (count % static_cast<int>(1 / size_factor_width) == 0) row.push_back(n);
            ++count;
        }
    }
    return row;
}

auto Level::get_lvl_amount() -> size_t
{
    return _lvl_paths.size();
}

auto Level::calculate_size_factors(const int lvl_number) -> void
{
    auto path = _lvl_paths[lvl_number];
    std::ifstream lvl_file (path);
    int number_lines{0}, number_columns{0};
    std::string line;
    if (lvl_file)
    {
        while(std::getline(lvl_file, line))
            { 
                if(number_lines==0)
                {
                    std::istringstream sline(line);
                    int n;
                    char c;
                    std::vector<int> row;
                    while(sline >> n >> c && c == ',')
                    {   
                            row.push_back(n);  
                    }
                    number_columns = row.size();
                }
                ++number_lines;
            }
    }
    size_factor_height = static_cast<int>(grid_height / number_lines);
    size_factor_width = static_cast<int>(grid_width / number_columns);
}
