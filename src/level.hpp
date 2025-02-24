#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <array>
#include <string>

#include "constants.hpp"

enum class Tile { none, wall, box, player, goal, box_goal, player_goal };

using LevelArray =
    std::array<std::array<Tile, constants::max_width>, constants::max_height>;

class Level {
private:
  int height, width;
  int player_xInit, player_yInit;
  int player_x, player_y;
  Tile player_replaceTileInit;
  Tile player_replaceTile;
  LevelArray gridInit;
  LevelArray grid;

  bool MoveBox(int pos_x, int pos_y, int dir_x, int dir_y, Tile currentTile);

public:
  Level();
  void AddRow(std::string row_string);  
  void InitGrid();
  void Draw();
  void MovePlayer(int dir_x, int dir_y);
};

#endif
