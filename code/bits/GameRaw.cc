#include "GameRaw.h"

namespace hg {

  GameRaw::GameRaw(gf::AssetManager& assets)
  {
    for (auto & path : { "level04.tmx", "level01.tmx", "level00.tmx", "level02.tmx" }) {
      gf::TmxLayers tmx;
      tmx.loadFromFile(assets.getAbsolutePath(path));
      levels.push_back(std::move(tmx));
    }
  }

}

