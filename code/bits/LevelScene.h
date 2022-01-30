#ifndef HG_LEVEL_SCENE_H
#define HG_LEVEL_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include <SFML/Audio.hpp>

#include "LayerEntity.h"
#include "HeroEntity.h"
#include "ButtonsEntity.h"
#include "PhysicsModel.h"

namespace hg {

  struct GameData;
  struct GameHub;

  class LevelScene : public gf::Scene {
  public:
    LevelScene(GameHub& game);

    void loadLevel(const GameData& data, std::size_t number);

    void stopMusic();

  private:
    void onActivityChange(bool active) override;
    void doHandleActions(gf::Window& window) override;

  private:
    GameHub& m_game;

    // Audio
    sf::Music& m_music;

    gf::Action m_quitAction;

    // Hanz actions
    gf::Action m_hanzRunLeftAction;
    gf::Action m_hanzRunRightAction;
    gf::Action m_hanzJumpAction;
    gf::Action m_hanzActivateAction;

    // Gret actions
    gf::Action m_gretRunLeftAction;
    gf::Action m_gretRunRightAction;
    gf::Action m_gretJumpAction;
    gf::Action m_gretActivateAction;

    PhysicsModel m_physics;

    LayerEntity m_layer;
    HeroEntity m_hanz; // red
    HeroEntity m_gret; // blue
    ButtonsEntity m_buttons;
  };

}

#endif // HG_LEVEL_SCENE_H
