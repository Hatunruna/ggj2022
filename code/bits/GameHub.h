#ifndef HG_GAME_HUB_H
#define HG_GAME_HUB_H

#include <gf/GameManager.h>

#include "AudioManager.h"
#include "GameData.h"
#include "GameRaw.h"
#include "GameScenery.h"
#include "GameState.h"
#include "LevelScene.h"
#include "StartScene.h"
#include "MenuScene.h"
#include "QuitScene.h"
#include "CreditScene.h"
#include "SelectLevelScene.h"

namespace hg {

  struct GameHub : gf::GameManager {
    GameHub();

    AudioManager audio;

    GameRaw raw;
    GameData data;
    GameScenery scenery;
    GameState state;

    StartScene start;
    MenuScene menu;
    SelectLevelScene select;
    CreditScene credits;
    LevelScene level;
    QuitScene quit;


  };


}


#endif // HG_GAME_HUB_H
