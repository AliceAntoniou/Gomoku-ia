/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Gomoku
*/

#include "Gomoku.hpp"
#include <fstream>

void Gomoku::defense_horizontal(int y_manager_move, int x_manager_move) {
    int x_max;
    int y_max;
    int x_min;
    int y_min;

    int size_line = 1;
    int x = x_manager_move + 1;

    for (x; x < board_size && _board[y_manager_move][x] == Tile_t::manager; x++);
    x_max = x;
    for (x = x_manager_move - 1; x >= 0 && _board[y_manager_move][x] == Tile_t::manager; x--);
    x_min = x;
    if (x_max - x_min >= 3) {
        y_just_played = y_manager_move;
        if (x_max < board_size && _board[y_manager_move][x_max] == Tile_t::empty) {
            if (x_max + 1 < board_size && _board[y_manager_move][x_max + 1] == Tile_t::manager) {
                next_moves.push_back({y_manager_move, x_max});
                m_line_size.push_back(x_max - x_min + 1);
            } else if (x_max - x_min >= 4) {
                next_moves.push_back({y_manager_move, x_max});
                m_line_size.push_back(x_max - x_min);
            }
        }
        if (x_min >= 0 && _board[y_manager_move][x_min] == Tile_t::empty) {
            if (x_min - 1 >= 0 && _board[y_manager_move][x_min - 1] == Tile_t::manager) {
                next_moves.push_back({y_manager_move, x_min});
                m_line_size.push_back(x_max - x_min + 1);
            } else if (x_max - x_min >= 5 && next_moves.size() && next_moves[next_moves.size() - 1].first == y_manager_move && next_moves[next_moves.size() - 1].second == x_max){
                next_moves.push_back({y_manager_move, x_min});
                m_line_size.push_back(x_max - x_min);
            } else if (x_max - x_min >= 5) {
                next_moves.push_back({y_manager_move, x_min});
                m_line_size.push_back(x_max - x_min - 1);
            }
        }
    }
}

void Gomoku::defense_vertical(int y_manager_move, int x_manager_move) {
    int y = y_manager_move + 1;
    int x_max;
    int y_max;
    int x_min;
    int y_min;

    for (y; y < board_size && _board[y][x_manager_move] == Tile_t::manager; y++);
    y_max = y;
    for (y = y_manager_move - 1; y >= 0 && _board[y][x_manager_move] == Tile_t::manager; y--);
    y_min = y;
    if (y_max - y_min >= 3) {
        x_just_played = x_manager_move;
        if (y_max < board_size && _board[y_max][x_manager_move] == Tile_t::empty) {
            if (y_max + 1 < board_size && _board[y_max + 1][x_manager_move] == Tile_t::manager) {
                next_moves.push_back({y_max, x_manager_move});
                m_line_size.push_back(y_max - y_min + 1);
            } else if (y_max - y_min >= 4) {
                next_moves.push_back({y_max, x_manager_move});
                m_line_size.push_back(y_max - y_min);
            }
        }
        if (y_min >= 0 && _board[y_min][x_manager_move] == Tile_t::empty) {
            if (y_min - 1 >= 0 && _board[y_min - 1][x_manager_move] == Tile_t::manager) {
                next_moves.push_back({y_min, x_manager_move});
                m_line_size.push_back(y_max - y_min + 1);
            } else if (y_max - y_min >= 4 && next_moves.size() && next_moves[next_moves.size() - 1].first == y_max && next_moves[next_moves.size() - 1].second == x_manager_move){
                next_moves.push_back({y_min, x_manager_move});
                m_line_size.push_back(y_max - y_min);
            } else if (y_max - y_min >= 5) {
                next_moves.push_back({y_min, x_manager_move});
                m_line_size.push_back(y_max - y_min - 1);
            }
        }
    }
}

void Gomoku::defense_diagonal_1(int y_manager_move, int x_manager_move) {
    int x;
    int y;
    int x_max;
    int y_max;
    int x_min;
    int y_min;

    for (x = x_manager_move, y = y_manager_move; x < board_size && y < board_size && _board[y][x] == Tile_t::manager; x++, y++);
    y_max = y;
    x_max = x;

    for (x = x_manager_move, y = y_manager_move; x > 0 && y > 0 && _board[y][x] == Tile_t::manager; x--, y--);
    y_min = y;
    x_min = x;

    if (y_max - y_min >= 3) {
        if (y_max < board_size && x_max < board_size && _board[y_max][x_max] == Tile_t::empty) {
            if (y_max + 1 < board_size && x_max + 1 < board_size && _board[y_max + 1][x_max + 1] == Tile_t::manager) {
                next_moves.push_back({y_max, x_max});
                m_line_size.push_back(y_max - y_min + 1);
            } else if (y_max - y_min >= 4) {
                next_moves.push_back({y_max, x_max});
                m_line_size.push_back(y_max - y_min);
            }
        }
        if (y_min >= 0 && x_min >= 0 && _board[y_min][x_min] == Tile_t::empty) {
            if (y_min - 1 >= 0 && x_min - 1 >= 0 && _board[y_min - 1][x_min - 1] == Tile_t::manager) {
                next_moves.push_back({y_min, x_min});
                m_line_size.push_back(y_max - y_min + 1);
            } else if (y_max - y_min >= 4 && next_moves.size() && next_moves[next_moves.size() - 1].first == y_max && next_moves[next_moves.size() - 1].second == x_max){
                next_moves.push_back({y_min, x_min});
                m_line_size.push_back(y_max - y_min);
            } else if (y_max - y_min >= 5) {
                next_moves.push_back({y_min, x_min});
                m_line_size.push_back(y_max - y_min - 1);
            }
        }
    }
}

void Gomoku::defense_diagonal_2(int y_manager_move, int x_manager_move) {
    int y = y_manager_move + 1;
    int x = x_manager_move - 1;
    int x_max;
    int y_max;
    int x_min;
    int y_min;

    for (x, y; x >= 0 && y < board_size && _board[y][x] == Tile_t::manager; x--, y++);
    y_max = y;
    x_min = x;

    y = y_manager_move - 1;
    x = x_manager_move + 1;
    for (x, y; x < board_size && y > 0 && _board[y][x] == Tile_t::manager; x++, y--);
    y_min = y;
    x_max = x;

    if (y_max - y_min >= 3) {
        if (y_max < board_size && x_min >= 0 && _board[y_max][x_min] == Tile_t::empty) {
            if (y_max + 1 < board_size && x_min - 1 >= 0 && _board[y_max + 1][x_min - 1] == Tile_t::manager) {
                next_moves.push_back({y_max, x_min});
                m_line_size.push_back(y_max - y_min + 1);
            } else if (y_max - y_min >= 4 && y_max < board_size && x_min >= 0 && _board[y_max][x_min] == Tile_t::empty) {
                next_moves.push_back({y_max, x_min});
                m_line_size.push_back(y_max - y_min);
            } else if (y_max - y_min >= 5) {
                next_moves.push_back({y_max, x_min});
                m_line_size.push_back(y_max - y_min);
            }
        }
        if (y_min >= 0 && x_max < board_size && _board[y_min][x_max] == Tile_t::empty) {
            if (y_min - 1 >= 0 && x_max + 1 < board_size && _board[y_min - 1][x_max + 1] == Tile_t::manager) { //line with empty case in middle
                next_moves.push_back({y_min, x_max});
                m_line_size.push_back(y_max - y_min + 1);
            } else if (y_max - y_min >= 4 && y_min >= 0 && x_max < board_size && _board[y_min][x_max] == Tile_t::empty){ //line not defended
                next_moves.push_back({y_min, x_max});
                m_line_size.push_back(y_max - y_min);
            } else if (y_max - y_min >= 5) { // line defended
                next_moves.push_back({y_min, x_max});
                m_line_size.push_back(y_max - y_min);
            }
        }
    }
}

void Gomoku::calculate_defensive_move(int y_manager_move, int x_manager_move)
{
    defense_horizontal(y_manager_move, x_manager_move);
    defense_vertical(y_manager_move, x_manager_move);
    defense_diagonal_1(y_manager_move, x_manager_move);
    defense_diagonal_2(y_manager_move, x_manager_move);
}

void Gomoku::calculate_range_around_enemy(int y, int x) 
{
    if (y + 1 < board_size && _board[y + 1][x] == Tile_t::empty)
        weights[y + 1][x] += 3;
    if (x + 1 < board_size && _board[y][x + 1] == Tile_t::empty)
        weights[y][x + 1] += 3;
    if (y - 1 >= 0 && _board[y - 1][x] == Tile_t::empty)
        weights[y - 1][x] += 3;
    if (x - 1 >= 0 && _board[y][x - 1] == Tile_t::empty)
        weights[y][x - 1] += 3;
    
    if (y + 2 < board_size && _board[y + 2][x] == Tile_t::empty)
        weights[y + 2][x] += 2;
    if (x + 2 < board_size && _board[y][x + 2] == Tile_t::empty)
        weights[y][x + 2] += 2;
    if (y - 2 >= 0 && _board[y - 2][x] == Tile_t::empty)
        weights[y - 2][x] += 2;
    if (x - 2 >= 0 && _board[y][x - 2] == Tile_t::empty)
        weights[y][x - 2] += 2;
}

void Gomoku::playing_defensive_move()
{
    m_line_size.clear();
    next_moves.clear();
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            if (_board[y][x] == Tile_t::manager) {
                calculate_range_around_enemy(y, x);
                calculate_defensive_move(y, x);
            }
        }
    }
    for (int i = 0; i < m_line_size.size(); i++) {
        weights[next_moves[i].first][next_moves[i].second] += 7;
        if (m_line_size[i] >= 5)
            weights[next_moves[i].first][next_moves[i].second] += 750;
    }
}
