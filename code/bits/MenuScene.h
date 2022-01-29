#ifndef HG_MENU_SCENE_H
#define HG_MENU_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>
#include "MenuTitleEntity.h"
#include "LevelSelectorEntity.h"
#include <vector>


namespace hg {

  struct GameHub;

  class MenuScene : public gf::Scene {
  public:
      MenuScene(GameHub& game);

  private:
    void doHandleActions(gf::Window& window) override;

  private:
    GameHub& m_game;
    gf::Action m_quitAction;
    gf::Action m_gameAction;
    gf::Action m_fullscreenAction;

    MenuTitleEntity m_menuTitleEntity;
    std::vector<LevelSelectorEntity> m_levelSelector;
  };

}

#endif // HG_MENU_SCENE_H
