#ifndef HG_GAME_SCENERY_H
#define HG_GAME_SCENERY_H

#include <gf/Span.h>
#include <gf/Tmx.h>

#include "LevelScenery.h"

namespace hg {

  struct GameScenery {
    GameScenery(gf::ResourceManager& resources, gf::Span<const gf::TmxLayers> raw);

    std::vector<LevelScenery> levels;
  };

}

#endif // HG_GAME_SCENERY_H
