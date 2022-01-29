#include "GameData.h"

#include <gf/Log.h>
#include <gf/Tmx.h>
#include <gf/TmxOps.h>

namespace hg {


  GameData::GameData(gf::Span<const gf::TmxLayers> raw)
  {
    for (auto & tmx : raw) {
      levels.push_back(LevelData::makeFromTmx(tmx));
    }
  }

}
