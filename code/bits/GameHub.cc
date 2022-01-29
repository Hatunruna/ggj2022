#include "GameHub.h"

#include "config.h"

namespace hg {

  GameHub::GameHub()
  : GameManager("Hanz and Gret", { GAME_DATADIR })
  , audio({ GAME_DATADIR })
  , start(*this)
  , level(*this)
  , quit(*this)
  {
    pushScene(start);
  }

}
