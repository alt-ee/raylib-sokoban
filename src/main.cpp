#include <fstream>
#include <iostream>
#include <string>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "level.hpp"

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
