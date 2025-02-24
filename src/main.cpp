#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "constants.hpp"

enum class Tile { none, wall, box, player, goal, box_goal, player_goal };

const std::map<char, Tile> charmap{
    {' ', Tile::none},       {'#', Tile::wall}, {'$', Tile::box},
    {'@', Tile::player},     {'.', Tile::goal}, {'*', Tile::box_goal},
    {'+', Tile::player_goal}};

const std::map<Tile, Color> tilemap{
    {Tile::none, LIGHTGRAY},    {Tile::wall, DARKGRAY}, {Tile::box, BROWN},
    {Tile::player, RED},        {Tile::goal, YELLOW},   {Tile::box_goal, GREEN},
    {Tile::player_goal, ORANGE}};

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

  bool MoveBox(int pos_x, int pos_y, int dir_x, int dir_y, Tile currentTile) {
    int target_x{pos_x + dir_x};
    int target_y{pos_y + dir_y};

    Tile replaceTile;
    if (currentTile == Tile::box_goal) {
      replaceTile = Tile::goal;
    } else {
      replaceTile = Tile::none;
    }

    if (grid[target_y][target_x] == Tile::none) {
      grid[target_y][target_x] = Tile::box;
    } else if (grid[target_y][target_x] == Tile::goal) {
      grid[target_y][target_x] = Tile::box_goal;
    } else {
      return false;
    }

    grid[pos_y][pos_x] = replaceTile;

    return true;
  }

public:
  Level()
      : height{0}, width{0}, player_xInit{0}, player_yInit{0},
        player_replaceTileInit(Tile::none), gridInit{Tile::none},
        player_x{0}, player_y{0},
        player_replaceTile(Tile::none), grid{Tile::none} {}

  void AddRow(std::string row_string) {
    if (row_string.size() > width) {
      width = row_string.size();
    }

    int x{0};
    for (char c : row_string) {
      gridInit[height][x] = charmap.at(c);
      if (c == '@' || c == '+') {
        player_xInit = x;
        player_yInit = height;
        if (c == '+') player_replaceTileInit = Tile::goal;
      }
      x++;
    }
    height++;
  }

  void InitGrid() {
    player_x = player_xInit;
    player_y = player_yInit;
    player_replaceTile = player_replaceTileInit;
    grid = gridInit;
  }

  void Draw() {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        DrawRectangle(x * constants::tile_width, y * constants::tile_height,
                      constants::tile_width, constants::tile_height,
                      tilemap.at(grid[y][x]));
      }
    }
  }

  void MovePlayer(int dir_x, int dir_y) {
    int target_x { player_x + dir_x };
    int target_y { player_y + dir_y };
    Tile target_tile { grid[target_y][target_x] };
    
    if (target_tile == Tile::box || target_tile == Tile::box_goal) {
      if (!MoveBox(target_x, target_y, dir_x, dir_y, target_tile)) return;
    } else if (target_tile == Tile::wall) {
      return;
    }

    // The tile we are replacing the target destination with
    // It will either be just the player if the destination is empty
    // or a player-on-goal tile if the destiation is the goal
    Tile target_replaceTile { Tile::player };
    if (target_tile == Tile::goal || target_tile == Tile::box_goal) {
      target_replaceTile = Tile::player_goal;
    }
      

    grid[player_y][player_x] = player_replaceTile;

    // If a box was pushed above, the value of target_tile is no longer valid,
    // so we need to re-access the target destination to set player_replaceTile
    player_replaceTile = grid[target_y][target_x];
    grid[target_y][target_x] = target_replaceTile;
    player_x = target_x;
    player_y = target_y;

    return;
  }
};

int main() {
  Level level{};

  std::ifstream levelFile{"level.txt"};

  if (!levelFile) {
    std::cerr << "Failed to open level file\n";
    return 1;
  }

  std::string rowString{};
  while (std::getline(levelFile, rowString))
    level.AddRow(rowString);

  level.InitGrid();

  InitWindow(1000, 800, "raygui test");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    if (IsKeyPressed(KEY_RIGHT)) {
      level.MovePlayer(1, 0);
    } else if (IsKeyPressed(KEY_LEFT)) {
      level.MovePlayer(-1, 0);
    } else if (IsKeyPressed(KEY_DOWN)) {
      level.MovePlayer(0, 1);
    } else if (IsKeyPressed(KEY_UP)) {
      level.MovePlayer(0, -1);
    }

    if (IsKeyPressed(KEY_R)) {
      level.InitGrid();
    }

    BeginDrawing();
    level.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
