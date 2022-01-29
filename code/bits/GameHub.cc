#include "GameHub.h"

#include "config.h"

namespace hg {

  GameHub::GameHub()
  : GameManager("Hanz and Gret", { GAME_DATADIR })
  , audio({ GAME_DATADIR })
  , data(resources)
  , start(*this)
  , level(*this)
  {
    pushScene(start);
  }

}
