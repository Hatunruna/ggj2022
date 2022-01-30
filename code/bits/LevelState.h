#ifndef HG_LEVEL_STATE_H
#define HG_LEVEL_STATE_H

#include <vector>

#include <gf/Vector.h>

#include "Hero.h"
#include "GameData.h"

namespace hg {

  struct PlatformState {
    HeroColor color;
  };

  struct LevelState {
    void loadLevel(const GameData& data, std::size_t number);

    std::vector<PlatformState> platforms;
  };

}

#endif // HG_LEVEL_STATE_H