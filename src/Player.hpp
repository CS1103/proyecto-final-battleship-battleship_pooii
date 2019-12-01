#ifndef GUARD_PLAYER_HPP
#define GUARD_PLAYER_HPP

#include <fstream>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <variant>

class Player
{
private:
    static std::regex infile_regex;

private:
    size_t m_token;
    std::string m_team_name;
    // `first` is the number of rows and `second` the number of columns
    std::pair<size_t, size_t> m_board_size;

    std::ofstream m_outfile;
    std::ifstream m_infile;

public:
    Player(std::string team_name);
    bool play();

private:
    void open_outfile();
    void open_infile();

    void handshake();

    bool attack();
    void attack_position(std::pair<size_t, size_t>);
    std::variant<bool, std::pair<size_t, size_t>>
        hunt(std::set<std::pair<size_t, size_t>>& left_to_shoot);
    std::optional<bool>
        target(std::set<std::pair<size_t, size_t>>& left_to_shoot,
            std::pair<size_t, size_t>);

    std::vector<std::pair<std::pair<size_t, size_t>,
                          std::pair<size_t, size_t>>>
        adjacent_positions(std::pair<size_t, size_t> pos);

    bool is_inside_map(std::pair<size_t, size_t> pos);

    std::string pos_to_format(std::pair<size_t, size_t> pos);
    std::string coordinate_to_letters(size_t c);

    std::map<std::string,std::string> read_parts();
};

#endif
