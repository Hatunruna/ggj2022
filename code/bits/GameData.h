#ifndef HG_GAME_DATA_H
#define HG_GAME_DATA_H

#include <gf/Span.h>
#include <gf/Tmx.h>

#include "LevelData.h"

namespace hg {

  struct GameData {
    GameData(gf::Span<const gf::TmxLayers> raw);

    std::vector<LevelData> levels;
  };

}

#endif // HG_GAME_DATA_H
