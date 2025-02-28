#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <array>
#include <string>
#include <map>

#include "constants.hpp"
#include "raylib.h"

enum class Tile { none, wall, box, player, goal, box_goal, player_goal };

using LevelArray =
    std::array<std::array<Tile, constants::max_width>, constants::max_height>;

const std::map<Tile, Color> tilemap{
    {Tile::none, LIGHTGRAY},    {Tile::wall, DARKGRAY}, {Tile::box, BROWN},
    {Tile::player, RED},        {Tile::goal, YELLOW},   {Tile::box_goal, GREEN},
    {Tile::player_goal, ORANGE}};

class Level {
private:
  int height_, width_;
  int player_xInit, player_yInit;
  int player_x, player_y;
  Tile player_replaceTileInit;
  Tile player_replaceTile;
  LevelArray gridInit;
  LevelArray grid_;

  bool MoveBox(int pos_x, int pos_y, int dir_x, int dir_y, Tile currentTile);

public:
  LevelArray grid() const { return grid_; };
  int height() const { return height_; };
  int width() const { return width_; };

  Level();
  void AddRow(std::string row_string);  
  void InitGrid();
  void MovePlayer(int dir_x, int dir_y);
};

#endif
