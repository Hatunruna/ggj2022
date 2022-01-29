#include "GameRaw.h"

namespace hg {

  GameRaw::GameRaw(gf::AssetManager& assets)
  {
    for (auto & path : { "level00.tmx" }) {
      gf::TmxLayers tmx;
      tmx.loadFromFile(assets.getAbsolutePath(path));
      levels.push_back(std::move(tmx));
    }
  }

}

