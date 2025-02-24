#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "level.hpp"
#include "loading.hpp"

int main(int argc, char* argv[]) {
  Level level{};
  int levelNumber{0}; // Default to first level if no argument provided

  std::ifstream levelFile;

  if (argc > 1)
    levelFile.open(argv[1]);
  else {
    std::cerr << "No level file provided!\n";
    return 1;
  }

  if (argc > 3)
  {
    std::stringstream convert{argv[3]};
    if(!(convert >> levelNumber))
      std::cerr << "Non-numeric argument provided for level number!\n";
    else
      levelNumber--;
  }
  
  if (!levelFile) {
    std::cerr << "Failed to open level file " << argv[1] << "\n";
    return 1;
  }

  RowStrings rowStrings = ParseLevelFile(levelFile)[levelNumber];

  for (std::string rowString : rowStrings) 
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

