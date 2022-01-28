#ifndef HG_GAME_HUB_H
#define HG_GAME_HUB_H

#include <gf/GameManager.h>

#include "AudioManager.h"
#include "GameData.h"
#include "GameState.h"
#include "StartScene.h"

namespace hg {

  struct GameHub : gf::GameManager {
    GameHub();

    AudioManager audio;

    GameData data;
    GameState state;

    StartScene start;
  };


}


#endif // HG_GAME_HUB_H
