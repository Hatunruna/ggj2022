#ifndef HG_MENU_SCENE_H
#define HG_MENU_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>
#include "MenuTitleEntity.h"
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>
#include <gf/Event.h>

namespace hg {

  struct GameHub;

  class MenuScene : public gf::Scene {
  public:
    MenuScene(GameHub& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;
    void doShow() override;

  private:
    GameHub& m_game;
    gf::Action m_quitAction;

    gf::Action m_upAction;
    gf::Action m_downAction;
    gf::Action m_triggerAction;

    MenuTitleEntity m_menuTitleEntity;

    gf::WidgetContainer m_widgets;
    gf::TextButtonWidget m_tutoButton;
    gf::TextButtonWidget m_level1;
  };

}

#endif // HG_MENU_SCENE_H
