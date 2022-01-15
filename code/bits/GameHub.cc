#include "GameHub.h"

#include "config.h"

namespace xy {

  GameHub::GameHub()
  : GameManager("Game", { GAME_DATADIR })
  , start(*this)
  {
    pushScene(start);
  }

}
