#ifndef HG_GAME_DATA_H
#define HG_GAME_DATA_H

#include <vector>

#include <gf/ResourceManager.h>

#include "LevelData.h"

namespace hg {

  struct GameData {
    GameData(gf::ResourceManager& resources);

    std::vector<LevelData> levels;
  };

}

#endif // HG_GAME_DATA_H
