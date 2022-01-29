#ifndef HG_GAME_RAW_H
#define HG_GAME_RAW_H

#include <vector>

#include <gf/AssetManager.h>
#include <gf/Tmx.h>

namespace hg {

  struct GameRaw {
    GameRaw(gf::AssetManager& assets);
    std::vector<gf::TmxLayers> levels;
  };

}


#endif // HG_GAME_RAW_H
