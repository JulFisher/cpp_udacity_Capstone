#include <fstream>
#include <vector>

class Level
{
public:

    Level(int _lvl);
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
            _lvl_file = source._lvl_file;
            _lvl_folder = source._lvl_folder;

            return *this;
    }

    Level &operator=(Level &&source)
    {
        _lvl_board = source._lvl_board;
        _lvl_file = source._lvl_file;
        _lvl_folder = source._lvl_folder;
        source._lvl_board = nullptr;

        return *this;
    }
    
    auto create_lvl_board(const std::string _path) -> void;

    auto get_lvl_board() -> std::vector<std::vector<int>>*;

private:
    std::string _lvl_file;
    std::string _lvl_folder{"../lvl/"};
    std::vector<std::vector<int>>* _lvl_board;

    auto ParseLine(std::string line) -> std::vector<int>;

};