#ifndef HG_LEVEL_SCENE_H
#define HG_LEVEL_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include "LayerEntity.h"
#include "HeroEntity.h"
#include "PhysicsModel.h"

namespace hg {

  struct GameData;
  struct GameHub;

  class LevelScene : public gf::Scene {
  public:
    LevelScene(GameHub& game);

    void loadLevel(const GameData& data, std::size_t number);

  private:
    void doHandleActions(gf::Window& window) override;

  private:
    GameHub& m_game;

    gf::Action m_quitAction;

    // Hanz actions
    gf::Action m_hanzRunLeftAction;
    gf::Action m_hanzRunRightAction;
    gf::Action m_hanzJumpAction;

    // Gret actions
    gf::Action m_gretRunLeftAction;
    gf::Action m_gretRunRightAction;

    PhysicsModel m_physics;

    LayerEntity m_layer;
    HeroEntity m_hanz; // red
    HeroEntity m_gret; // blue
  };

}

#endif // HG_LEVEL_SCENE_H
