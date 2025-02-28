#include "graphics.hpp"

void DrawLevel(LevelArray level, int width, int height) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      DrawRectangle(x * constants::tile_width, y * constants::tile_height,
                    constants::tile_width, constants::tile_height,
                    tilemap.at(level[y][x]));
    }
  }
}
