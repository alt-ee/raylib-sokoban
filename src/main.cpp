#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "constants.h"

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
public:
  int height, width;
  LevelArray grid;

  Level() : height{0}, width{0}, grid{Tile::none} {}

  void AddRow(std::string row_string) {
    if (row_string.size() > width) {
      width = row_string.size();
    }

    int i{0};
    for (char c : row_string) {
      grid[height][i] = charmap.at(c);
      i++;
    }
    height++;
  }

  void DrawLevel() {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        DrawRectangle(x * constants::tile_width, y * constants::tile_height,
                      constants::tile_width, constants::tile_height,
                      tilemap.at(grid[y][x]));
      }
    }
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

  InitWindow(1000, 800, "raygui test");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    level.DrawLevel();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
