#ifndef GUARD_PLAYER_HPP
#define GUARD_PLAYER_HPP

#include <string>
#include <fstream>
#include <regex>
#include <utility>

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
    void play();

private:
    void handshake();
    void handshake_write();
    bool attack();
    void open_outfile();
    void open_infile();
    void attack_position(std::pair<size_t, size_t>);

    bool is_inside_map(std::pair<size_t, size_t> pos);

    std::string pos_to_format(std::pair<size_t, size_t> pos);
    std::string coordinate_to_letters(size_t c);

    std::map<std::string,std::string> read_parts();
};

#endif
