#include "GameScenery.h"

namespace hg {

  GameScenery::GameScenery(gf::ResourceManager& resources, gf::Span<const gf::TmxLayers> raw) {
    for (auto & tmx : raw) {
      levels.push_back(LevelScenery::makeFromTmx(resources, tmx));
    }
  }

}

