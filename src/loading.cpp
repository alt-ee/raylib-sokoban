#include "loading.hpp"
#include <algorithm>

std::vector<RowStrings> ParseLevelFile(std::ifstream & levelFile) {

  std::string rowString{};
  RowStrings rowStrings{};
  std::vector<RowStrings> levelRowStrings{};

  levelFile.ignore(1000, '\n'); // Skip the first line containing the level marker
                                
  while (std::getline(levelFile, rowString)) {
    rowString.erase(std::remove(rowString.begin(), rowString.end(), '\r'), rowString.end());
    if (rowString.empty()) {
      continue;
    }

    if (rowString[0] == ';') {
      levelRowStrings.push_back(rowStrings);
      rowStrings.clear();
    } else {
      rowStrings.push_back(rowString);
    }
  }

  levelRowStrings.push_back(rowStrings); // Have to add the final level here because there's no ; after it

  return levelRowStrings;  
}
