#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <stdexcept>
#include <set>
#include <sstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <string>
#include <random>
#include <time.h>
#include <utility>
#include <vector>
#include <variant>

#include "Player.hpp"
#include "prettyprint.hpp"

std::regex Player::infile_regex("^\\w+\\.out$");

Player::Player(std::string team_name)
    : m_team_name(team_name)
{
}

void Player::play()
{
    handshake();
    placement();
    attack();
}

/**
 * Does the handshake stage.
 * Sets the board size and the user's token. Also edits the team name until one
 * is accepted.
 */
void Player::handshake()
{
    // We assume that the size will always be 10x10.
    m_board_size = {10, 10};

    size_t try_number = 0;
    std::string team_name = m_team_name + std::to_string(try_number);

    while (true)
    {
        open_outfile();
        m_outfile << "HANDSHAKE=" << team_name << std::endl;
        m_outfile.close();

        auto parts = read_parts();

        if (parts.find("STATUS")->second == "REJECTED")
        {
            try_number++;
        }
        else
        {
            break;
        }
    }
}

void Player::open_outfile()
{
    static std::string outfile_name = "Player.in";

    m_outfile.open(outfile_name);
    if (!m_outfile.is_open())
    {
        throw std::runtime_error("Couldn't open '" + outfile_name +
                                 " for writing.");
    }
}

/**
 * Looks for a filename that matches the regex and returns an std::ifstream if
 * one is found, else the option is empty.
 */
void Player::open_infile()
{
    std::string path = std::filesystem::current_path();

    for (auto const& entry : std::filesystem::directory_iterator(path))
    {
        std::string a = entry.path();

        //  XXX: Can't you pass entry.path() directly?
        if (regex_match(a.begin(), a.end(), infile_regex))
        {
           m_infile.open(entry.path());
           return;
        }
    }
}

<<<<<<< HEAD:src/Player.cpp
std::map<std::string,std::string> Player::read_parts()
{
    std::map<std::string,std::string> ret;

    m_infile.close();
    while (!m_infile.is_open())
    {
        open_infile();
=======
// Placement
// Picks a point and tries either vertical or horizontal placment (rndm)
// If that doesn't work, try the next point in diagonal
void place_boat(char type_ship, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero)
{   
    std::vector<std::pair<std::pair<size_t,size_t>,char>> points;
    int len;
    std::pair<std::pair<size_t, size_t>,char> par;
    switch (type_ship)
    {   
        case 'A':
            len = 4;
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;
        
        case 'B':
            len = 3;            
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;
        
        case 'S':
            len = 2;
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;
        
        case 'T':
            len = 1;
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;

        default:
            break;
>>>>>>> f33ed880c38673cff76f75c8e2bd4e4510333004:src/funct.cpp
    }

    std::string line0;
    std::getline(m_infile, line0);

    while (std::getline(m_infile, line0,'='))
    {
        std::string line1;
        std::getline(m_infile, line1);
        ret[line0] = line1;
    }

    m_infile.close();

    return ret;
}

<<<<<<< HEAD:src/Player.cpp
/**
 * The attack stage.
 * Returns wheter the player won or lost.
 */
bool Player::attack()
{
    // Fill all the remaining positions to attack, we save them in a set so that
    // we can check rapidly wheter a specific position was already attacked.

    std::set<std::pair<size_t, size_t>> pos_left_to_shoot;
    for (size_t i = 0; i < m_board_size.first; i++)
    {
        for (size_t j = 0; j < m_board_size.second; j++)
        {
            pos_left_to_shoot.emplace(i, j);
        }
    }

    while (!pos_left_to_shoot.empty())
    {
        std::variant<bool, std::pair<size_t, size_t>>
            pos_hunted = hunt(pos_left_to_shoot);

        std::optional<bool> target_result = target(pos_hunted, pos_left_to_shoot);
    }
}

/**
 * Checks wheter a given position is inside the maps boundaries
 */
bool Player::is_inside_map(std::pair<size_t, size_t> pos)
=======
void placement(std::string TOKEN)
>>>>>>> f33ed880c38673cff76f75c8e2bd4e4510333004:src/funct.cpp
{
    return pos.first < m_board_size.first && pos.second < m_board_size.second;
}

void Player::attack_position(std::pair<size_t, size_t> pos)
{
    open_outfile();

    m_outfile << "TOKEN=" << m_token << std::endl;
    m_outfile << "ATTACK=" << pos_to_format(pos) << std::endl;

    m_outfile.close();
}

std::string Player::pos_to_format(std::pair<size_t, size_t> pos)
{
    std::ostringstream oss;
    oss << coordinate_to_letters(pos.second) << pos.first;
    return oss.str();
}

std::string Player::coordinate_to_letters(size_t c)
{
    std::string ret(1, 'A' + c % 26);
    c /= 26;

    while (c != 0)
    {
        ret = std::string(1, 'A' - 1 + c % 27) + ret;
        c /= 27;
    }

    return ret;
}

std::variant<bool, std::pair<size_t, size_t>>
    Player::hunt(std::set<std::pair<size_t, size_t>>& left_to_shoot)
{
    static std::random_device rd;

    while (!left_to_shoot.empty())
    {
        // Select a position not yet shot
        auto it_pos_to_shoot = std::next(left_to_shoot.begin(),
                                         rd() % left_to_shoot.size());
        auto pos_to_shoot = *it_pos_to_shoot;

        attack_position(pos_to_shoot);

        auto parts = read_parts();

        if (parts.find("STATUS")->second == "REJECTED")
        {
            continue;
        }

        left_to_shoot.erase(it_pos_to_shoot);

        auto message = parts.find("MESSAGE")->second;

        if (message == "WINNER")
        {
            return true;
        }
        else if (message == "GAMEOVER")
        {
            return false;
        }
        else if (message == "DAMAGED" || message == "DESTROYED")
        {
            return pos_to_shoot;
        }
    }
}

std::optional<bool>
    Player::target(std::set<std::pair<size_t, size_t>>& left_to_shoot,
                   std::pair<size_t, size_t> pos_shot)
{
    std::stack<std::pair<std::pair<size_t, size_t>,
                            std::pair<size_t, size_t>>>
        adjacent_pos_dir;

    for (auto& pd : adjacent_positions(pos_shot))
    {
        adjacent_pos_dir.push(pd);
    }

    while (!adjacent_pos_dir.empty())
    {
        std::pair<size_t, size_t> pos;
        std::pair<size_t, size_t> move_direction;

        std::tie(pos, move_direction) = adjacent_pos_dir.top();

        attack_position(pos);

        auto parts = read_parts();

        if (parts.find("STATUS")->second == "REJECTED")
        {
            continue;
        }

        adjacent_pos_dir.pop();

        auto message = parts.find("MESSAGE")->second;
        if (message == "WINNER")
        {
            return true;
        }
        if (message == "GAMEOVER")
        {
            return false;
        }
        else if (message == "FAILED")
        {
            continue;
        }
        else
        {
            auto new_pos = std::make_pair(pos.first + move_direction.first,
                                          pos.second + move_direction.second);
            if (is_inside_map(new_pos))
            {
                adjacent_pos_dir.emplace(new_pos, move_direction);
            }
        }
    }

    return std::optional<bool>();
}

std::vector<std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>
    Player::adjacent_positions(std::pair<size_t, size_t> pos)
{
    static std::vector<std::pair<int, int>> possible_moves = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    size_t x = pos.first;
    size_t y = pos.second;

    std::vector<std::pair<std::pair<size_t, size_t>,
                          std::pair<size_t, size_t>>>
        ret;

    for (auto const& pm : possible_moves)
    {
        if (is_inside_map({x + pm.first, y + pm.second}))
        {
            ret.emplace_back(std::make_pair(x + pm.first, y + pm.second), pm);
        }
    }

    return ret;
}
//placement
template<typename entero_t>
entero_t randint(entero_t first, entero_t last)
{
    std::random_device dev;
    std::mt19937 eng(dev());
    std::uniform_int_distribution<entero_t> dis(first, last);
    return dis(eng);
}

char randchar()
{
    int r = randint(0,1);
    if (r == 0)
    {
        return 'V';
    } else 
    {
        return 'H';
    } 
}

void update(std::pair<std::pair<size_t,size_t>, bool>& point)
{
    point.first.first = randint(0,9);
    point.first.second = randint(0,9);
    point.second = true;
}

std::pair<std::pair<size_t,size_t>, bool> 
        rand_point(std::set<std::pair<std::pair<size_t,size_t>, bool>> data)
{
    auto point_b = generate_point();
    
    while (true)
    {
        if (verify(data, point_b))
        {
            break;
        } else 
        {
            update(point_b);
        }
    } 
    return point_b;
}

bool verify(std::set<std::pair<std::pair<size_t,size_t>, bool>> data,
    std::pair<std::pair<size_t,size_t>, bool> point)
{
    return data.count(point) == 0;
}

std::pair<std::pair<size_t,size_t>, bool> generate_point()
{
    int a = randint(0,9);
    int b = randint(0,9);
    auto point = std::make_pair(a,b);
    return std::make_pair(point, true);
}

std::pair<std::pair<size_t,size_t>,char> can_it_place(int len, 
    std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero)
{
    char direc;
    auto tabpoint = generate_point();
    while (true)
    {
        bool rangeX = tabpoint.first.second + len <= 10;
        bool rangeY = tabpoint.first.first + len <= 10;
        if (rangeX&&rangeY)
        {
            char direction = randchar();
            if (direction == 'H')
            {
                bool fits = true;
                for (int i = 0; i < len; ++i)
                {
                        auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second);
                        auto point_ver = std::make_pair(ub,true);
                        fits = fits && verify(tablero,point_ver);
                }  
                if (fits)
                {
                    std::cout << "H " << tabpoint << std::endl;
                    for (int i = 0; i < len; ++i)
                    {
                        auto ub = std::make_pair(tabpoint.first.first+i+1,tabpoint.first.second);
                        auto point_ver = std::make_pair(ub,true);
                        tablero.insert(point_ver);
                        if (tabpoint.first.second+1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second+1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);
                        }
                        if (tabpoint.first.second-1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second-1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);
                        }
                    }
                    break;
                }      

            } else if (direction == 'V') 
            {
                bool fits = true;
                for (int i = 0; i < len; ++i)
                {
                        auto ub = std::make_pair(tabpoint.first.first,tabpoint.first.second+i);
                        auto point_ver = std::make_pair(ub,true);
                        fits = fits && verify(tablero,point_ver);
                }  
                if (fits)
                {
                    std::cout << "V " << tabpoint << std::endl;
                    for (int i = 0; i < len; ++i)
                    {
                        auto ub = std::make_pair(tabpoint.first.first,tabpoint.first.second+i);
                        auto point_ver = std::make_pair(ub,true);
                        tablero.insert(point_ver);

                        if (tabpoint.first.first+1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first+1,tabpoint.first.second+i+1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);

                        }
                        if (tabpoint.first.first-1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first-1,tabpoint.first.second+i+1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);
                        }
                    }
                break;
                }
            } 
            else 
            {
                update(tabpoint);
            }
        update(tabpoint);
        }
    update(tabpoint);
    }
    
    auto par1 = tabpoint.first.first;
    auto par2 = tabpoint.first.second;
    auto final_pair = std::make_pair(par1,par2);
    return std::make_pair(final_pair,direc);
}

void place_boat(char type_ship, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero)
{   
    std::vector<std::pair<std::pair<size_t,size_t>,char>> points;
    int len;
    std::pair<std::pair<size_t, size_t>,char> par;
    switch (type_ship)
    {   
        case 'A':
            len = 4;
            par = can_it_place(len, tablero);
            points.push_back(par);
        break;
        
        case 'B':
            len = 3;            
            par = can_it_place(len, tablero);
            points.push_back(par);
        break;
        
        case 'S':
            len = 2;
            par = can_it_place(len, tablero);
            points.push_back(par);
        break;
        
        case 'T':
            len = 1;
            par = can_it_place(len, tablero);
            points.push_back(par);
        break;
        default:
            std::cout<<"no"<<std::endl;
    }
    for (auto it : points){
        std::cout << it << std::endl;
    }
}

void placement()
{
    std::map<char, size_t> remaining_fleet = {
        {'A', 1},
        {'B', 2},
        {'S', 3},
        {'T', 4}
    };

    std::set<std::pair<std::pair<size_t,size_t>, bool>> tablero;
    
    std::map<char, size_t>::iterator itm;

    for (auto& itmap : remaining_fleet)
    {
        while (itmap.second != 0)
        {
            place_boat(itmap.first, tablero);
            itmap.second--;
        }
    }
}