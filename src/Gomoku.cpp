/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Gomoku
*/

#include "Gomoku.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <sstream>
#include <fstream> //include the filestreamobject as the header files
#include <cstdio>

std::string Gomoku::get_command(void)
{
    std::string command;
    command.clear();
    std::cin >> command;

    if (command == "START") {
        if(!start())
            std::cout << "ERROR invalid size" << std::endl;
    } else if (command == "INFO") {
        info();
    } else if (command == "TURN") {
        turn();
    } else if (command == "BEGIN") {
        begin();
    } else if (command == "BOARD") {
        board();
    } else if (command == "END") {
        end();
    } else if (command == "ABOUT") {
        about();
    }
    return command;
}

static std::pair<int, int> get_max(const std::vector<std::vector<int>> &weight)
{
    std::pair<int, int> pos;
    int max = -2;

    for (size_t y = 0; y < weight.size(); y++) {
        for (size_t x = 0; x < weight[y].size(); x++) {
            if (weight[y][x] > max) {
                pos = {x, y};
                max = weight[y][x];
            }
        }
    }
    return pos;
}

void Gomoku::play(void)
{
    get_map();
    static int x = 0;
    static int y = 0;

    weights = std::vector<std::vector<int>>(board_size, std::vector<int>(board_size, -9));
    if (game_started == true) {
        playing_attack_move();
        playing_defensive_move();

        auto pos = get_max(weights);
        x_just_played = pos.first;
        y_just_played = pos.second;
        _board[y_just_played][x_just_played] = Tile_t::brain;
        write_map();
        std::cout << x_just_played << "," << y_just_played << std::endl;
        return;
    }
    game_started = true;
    while (_board[y][x] != Tile_t::empty) {
        x+= 1;
        if(x >= board_size) {
            y += 1;
            x = 0;
        }
    }
    _board[y][x] = Tile_t::brain;
    std::cout << x << "," << y << std::endl;    
    write_map();
} 

void Gomoku::start(int size)
{
    board_size = size;

    _board.clear();
    for (size_t i = 0; i < board_size; i++) {
        _board.push_back(std::vector<Tile_t> (board_size, Tile_t::empty));
    }
}

bool Gomoku::start(void)
{
    srand(time(NULL));
    std::string data;
    getline(std::cin, data);
    if (data == "")
        return false;
    board_size = std::stoi(data);
    if (board_size < 5)
        return false;
    start(board_size);
    write_map();
    std::cout << "OK" << std::endl;
    return true;
}

void Gomoku::turn(void)
{
    get_map();
    std::string data;

    getline(std::cin, data);
    if (data == "" || data.find(",") == std::string::npos) {
        std::cout << "ERROR invalid move" << std::endl;
        return;
    }
    int x_manager_move = std::stoi(data.substr(0, data.find(",")));
    int y_manager_move = std::stoi(data.substr(data.find(',')+ 1, std::string::npos));
    if (y_manager_move > board_size || x_manager_move > board_size || y_manager_move < 0 || x_manager_move < 0)
        std::cout << "ERROR invalid move" << std::endl;
    else {
        _board[y_manager_move][x_manager_move] = Tile_t::manager;
        write_map();
        play();
    }
}

void Gomoku::begin(void)
{
    _turn = Tile_t::brain;
    play();
}

void Gomoku::board(void) {
    std::string str = "BOARD";
    int x = 0;
    int y = 0;
    int type = 0;

    start(board_size);
    str.clear();
    std::cin >> str;
    while(str != "DONE") {
        x = std::stoi(str.substr(0, str.find(",")));
        str.erase(0, str.find(",") + 1);
        y = std::stoi(str.substr(0, str.find(",")));
        str.erase(0, str.find(",") + 1);
        type = std::stoi(str.substr(0, std::string::npos));
        if (type == 1)
            _board[y][x] = Tile_t::brain;
        if (type == 2)
            _board[y][x] = Tile_t::manager;
        str.clear();
        std::cin >> str;
    }
    play();
}

void Gomoku::info(void)
{
    std::string key_info;
    std::string data;
    std::cin >> key_info;
    std::cin >> data;
    if (key_info == "folder")
        folder = data;
    else 
        settings.at(key_info) = std::stoi(data);
}

void Gomoku::end(void) {}

void Gomoku::about(void) {
    std::cout << "name=\"Gomoku-ai\", version=\"1.0\", author=\"Juliette Dupin, Damien Antoniou, Nataniel Louis\", country=\"France\"" << std::endl;
}

void Gomoku::write_map()
{
    static std::fstream file("map.txt", std::ios::out | std::ios::trunc);

    file << board_size << std::endl;
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            switch (_board[y][x]) {
                case Tile_t::manager :
                    file << 'O';
                    break;
                case Tile_t::brain :
                    file << 'x';
                    break;
                case Tile_t::empty :
                    file << ' ';
                    break;
                default:
                    break;
            }
        }
        file << '\n';
    }
    file.close();
}

bool Gomoku::get_map()
{
    static std::fstream file("map.txt", std::ios::out | std::ios::trunc);
    std::string data;
    std::string line;
    
    if (!file.is_open())
        return false;
    if (!std::getline(file, line))
        return false;
    board_size = std::stoi(line);
    start(board_size);

    for (int y = 0; y < board_size; y++) {
        std::getline(file, line);
        for (int x = 0; x < board_size && line[x]; x++) {
            switch (line[x]) {
                case Tile_t::manager :
                    _board[y][x] = Tile_t::manager;
                    break;
                case Tile_t::brain :
                    _board[y][x] = Tile_t::brain;
                    break;
                case Tile_t::empty :
                    _board[y][x] = Tile_t::empty;
                    break;
                default:
                    break;
            }
        }  
    }
    file.close();
    return true;
}