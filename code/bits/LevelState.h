#ifndef HG_LEVEL_STATE_H
#define HG_LEVEL_STATE_H

#include <vector>

#include "PlatformState.h"

namespace hg {

  struct LevelState {
    std::vector<PlatformState> platforms;
  };

}

#endif // HG_LEVEL_STATE_H