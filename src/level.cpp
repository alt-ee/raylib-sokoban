#include "level.hpp"

#include <map>

const std::map<char, Tile> charmap{
    {' ', Tile::none},       {'#', Tile::wall}, {'$', Tile::box},
    {'@', Tile::player},     {'.', Tile::goal}, {'*', Tile::box_goal},
    {'+', Tile::player_goal}};

Level::Level()
    : height_{0}, width_{0}, player_xInit{0}, player_yInit{0},
      player_replaceTileInit(Tile::none), gridInit{Tile::none}, player_x{0},
      player_y{0}, player_replaceTile(Tile::none), grid_{Tile::none} {}

bool Level::MoveBox(int pos_x, int pos_y, int dir_x, int dir_y,
                    Tile currentTile) {
  int target_x{pos_x + dir_x};
  int target_y{pos_y + dir_y};

  Tile replaceTile;
  if (currentTile == Tile::box_goal) {
    replaceTile = Tile::goal;
  } else {
    replaceTile = Tile::none;
  }

  if (grid_[target_y][target_x] == Tile::none) {
    grid_[target_y][target_x] = Tile::box;
  } else if (grid_[target_y][target_x] == Tile::goal) {
    grid_[target_y][target_x] = Tile::box_goal;
  } else {
    return false;
  }

  grid_[pos_y][pos_x] = replaceTile;

  return true;
}

void Level::AddRow(std::string row_string) {
  if (row_string.size() > width_) {
    width_ = row_string.size();
  }

  int x{0};
  for (char c : row_string) {
    gridInit[height_][x] = charmap.at(c);
    if (c == '@' || c == '+') {
      player_xInit = x;
      player_yInit = height_;
      if (c == '+')
        player_replaceTileInit = Tile::goal;
    }
    x++;
  }
  height_++;
}

void Level::InitGrid() {
  player_x = player_xInit;
  player_y = player_yInit;
  player_replaceTile = player_replaceTileInit;
  grid_ = gridInit;
}

void Level::MovePlayer(int dir_x, int dir_y) {
  int target_x{player_x + dir_x};
  int target_y{player_y + dir_y};
  Tile target_tile{grid_[target_y][target_x]};

  if (target_tile == Tile::box || target_tile == Tile::box_goal) {
    if (!MoveBox(target_x, target_y, dir_x, dir_y, target_tile))
      return;
  } else if (target_tile == Tile::wall) {
    return;
  }

  // The tile we are replacing the target destination with
  // It will either be just the player if the destination is empty
  // or a player-on-goal tile if the destiation is the goal
  Tile target_replaceTile{Tile::player};
  if (target_tile == Tile::goal || target_tile == Tile::box_goal) {
    target_replaceTile = Tile::player_goal;
  }

  grid_[player_y][player_x] = player_replaceTile;

  // If a box was pushed above, the value of target_tile is no longer valid,
  // so we need to re-access the target destination to set player_replaceTile
  player_replaceTile = grid_[target_y][target_x];
  grid_[target_y][target_x] = target_replaceTile;
  player_x = target_x;
  player_y = target_y;

  return;
}
