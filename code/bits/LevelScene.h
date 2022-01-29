#ifndef HG_LEVEL_SCENE_H
#define HG_LEVEL_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include "LayerEntity.h"
#include "HeroEntity.h"

namespace hg {

  struct GameHub;

  class LevelScene : public gf::Scene {
  public:
    LevelScene(GameHub& game);

  private:
    void doHandleActions(gf::Window& window) override;

  private:
    GameHub& m_game;

    gf::Action m_quitAction;

    // Hanz actions
    gf::Action m_hanzRunLeftAction;
    gf::Action m_hanzRunRightAction;

    // Gret actions
    gf::Action m_gretRunLeftAction;
    gf::Action m_gretRunRightAction;

    LayerEntity m_layer;
    HeroEntity m_hanz; // red
    HeroEntity m_gret; // blue
  };

}

#endif // HG_LEVEL_SCENE_H
