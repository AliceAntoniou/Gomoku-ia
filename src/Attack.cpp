/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Gomoku
*/

#include <Gomoku.hpp>

//#include <fstream>
//#include <iomanip>

//static std::fstream out("C:\\Users\\groce\\Documents\\GitHub\\B-AIA-500-BDX-5-1-gomoku-juliette.dupin\\build\\out.txt", std::ios::out | std::ios::trunc);

static bool update(const Gomoku::Tile_t &tile, int &count, int &count_side, bool &check)
{
    if (tile == Gomoku::manager)
        return false;
    if (tile == Gomoku::empty)
        check = false;
    if (tile == Gomoku::brain) {
        if (check) {
            count_side++;
            count += 7;
        }
        count += 2;
    }
    count++;
    return true;
}

static int count_horizontaly(const Gomoku::board_t &board, std::pair<int, int> pos)
{
    int count = 0;
    int count_side = 0;
    bool check = true;
    int max = 1;

    for (int i = pos.first - 1; i >= 0 && i > pos.first - 5; i--) {
        if (!update(board[pos.second][i], count, count_side, check))
            break;
        max++;
    }
    check = true;
    for (int i = pos.first + 1; i < board[pos.second].size() && i < pos.first + 5; i++) {
        if (!update(board[pos.second][i], count, count_side, check))
            break;
        max++;
    }
    if (max < 5)
        return -4;
    if (count_side >= 4)
        return 800;
    return count;
}

static int count_verticaly(const Gomoku::board_t &board, std::pair<int, int> pos)
{
    int count = 0;
    int count_side = 0;
    bool check = true;
    int max = 1;

    for (int i = pos.second - 1; i >= 0 && i > pos.second - 5; i--) {
        if (!update(board[i][pos.first], count, count_side, check))
            break;
        max++;
    }
    check = true;
    for (int i = pos.second + 1; i < board.size() && i < pos.second + 5; i++) {
        if (!update(board[i][pos.first], count, count_side, check))
            break;
        max++;
    }
    if (max < 5)
        return -4;
    if (count_side >= 4)
        return 800;
    return count;
}

static int count_diagonaly_down(const Gomoku::board_t &board, std::pair<int, int> pos)
{
    int count = 0;
    int count_side = 0;
    bool check = true;
    int max = 1;
    int x = pos.first - 1;
    int y = pos.second - 1;

    while (x >= 0 && y >= 0 && x > pos.first - 5 && y > pos.second - 5) {
        if (!update(board[y][x], count, count_side, check))
            break;
        max++;
        x--;
        y--;
    }
    check = true;
    x = pos.first + 1;
    y = pos.second + 1;
    while (y < board.size() && x < board[y].size() && y < pos.second + 5 && x < pos.first + 5) {
        if (!update(board[y][x], count, count_side, check))
            break;
        max++;
        x++;
        y++;
    }
    if (max < 5)
        return -4;
    if (count_side >= 4)
        return 800;
    return count;
}

static int count_diagonaly_up(const Gomoku::board_t &board, std::pair<int, int> pos)
{
    int count = 0;
    int count_side = 0;
    bool check = true;
    int max = 1;
    int x = pos.first - 1;
    int y = pos.second + 1;

    while (x >= 0 && y < board.size() && x > pos.first - 5 && y > pos.second + 5) {
        if (!update(board[y][x], count, count_side, check))
            break;
        max++;
        x--;
        y++;
    }
    check = true;
    x = pos.first + 1;
    y = pos.second + 1;
    while (y >= 0 && x < board[y].size() && y < pos.second - 5 && x < pos.first + 5) {
        if (!update(board[y][x], count, count_side, check))
            break;
        max++;
        x++;
        y--;
    }
    if (max < 5)
        return -4;
    if (count_side >= 4)
        return 800;
    return count;
}

void Gomoku::playing_attack_move(void)
{
    int count = 0;

    for (size_t y = 0; y < weights.size(); y++) {
        for (size_t x = 0; x < weights[y].size(); x++) {
            if (_board[y][x] == Gomoku::empty)
                weights[y][x] = count_horizontaly(_board, {x, y}) + count_verticaly(_board, {x, y}) + count_diagonaly_down(_board, {x, y}) + count_diagonaly_up(_board, {x, y});
            //out << std::setfill(' ') << std::setw(3) << weights[y][x] << " ";
        }
        //out << std::endl;
    }
    //out << std::endl;
}