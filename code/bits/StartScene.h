#ifndef XY_START_SCENE_H
#define XY_START_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

namespace xy {

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
  };

}

#endif // XY_START_SCENE_H
