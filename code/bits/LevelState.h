#ifndef HG_LEVEL_STATE_H
#define HG_LEVEL_STATE_H

#include <vector>

#include "Hero.h"

namespace hg {

  struct PlatformState {
    HeroColor color; 
  };

  struct LevelState {
    std::vector<PlatformState> platforms;
  };

}

#endif // HG_LEVEL_STATE_H