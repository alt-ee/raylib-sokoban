#ifndef LOADING_HPP
#define LOADING_HPP

#include <vector>
#include <string>
#include <fstream>

using RowStrings = std::vector<std::string>;

std::vector<RowStrings> ParseLevelFile(std::ifstream& levelFile);

#endif
