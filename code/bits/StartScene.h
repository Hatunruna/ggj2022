#ifndef HG_START_SCENE_H
#define HG_START_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include <SFML/Audio.hpp>

#include "TitleEntity.h"

namespace hg {

  struct GameHub;

  class StartScene : public gf::Scene {
  public:
    StartScene(GameHub& game);

  private:
    void doHandleActions(gf::Window& window) override;

  private:
    GameHub& m_game;

    gf::Action m_startAction;
    gf::Action m_fullscreenAction;

    TitleEntity m_titleEntity;

    sf::Music& m_theme;
  };

}

#endif // HG_START_SCENE_H
