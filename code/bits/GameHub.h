#ifndef HG_GAME_HUB_H
#define HG_GAME_HUB_H

#include <gf/GameManager.h>

#include "AudioManager.h"
#include "GameData.h"
#include "GameState.h"
#include "LevelScene.h"
#include "StartScene.h"
#include "MenuScene.h"

namespace hg {

  struct GameHub : gf::GameManager {
    GameHub();

    AudioManager audio;

    GameData data;
    GameState state;

    StartScene start;
    MenuScene menu;
    LevelScene level;


  };


}


#endif // HG_GAME_HUB_H
