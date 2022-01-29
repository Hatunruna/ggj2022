#include "GameHub.h"

#include "config.h"

namespace hg {

  GameHub::GameHub()
  : GameManager("Hanz and Gret", { GAME_DATADIR })
  , audio({ GAME_DATADIR })
  , raw(resources)
  , data(raw.levels)
  , scenery(resources, raw.levels)
  , start(*this)
  , level(*this)
  {
    pushScene(start);
  }

}
