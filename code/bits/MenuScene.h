#ifndef HG_MENU_SCENE_H
#define HG_MENU_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>
#include "MenuTitleEntity.h"
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>
#include <gf/Event.h>
#include <gf/Text.h>

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
    gf::Texture& m_backgroundTexture;

    gf::Action m_quitAction;

    gf::Action m_upAction;
    gf::Action m_downAction;
    gf::Action m_triggerAction;

    gf::TextButtonWidget m_newGame;
    gf::TextButtonWidget m_continue;
    gf::TextButtonWidget m_credits;
    gf::TextButtonWidget m_quit;

    gf::WidgetContainer m_widgets;
  };

}

#endif // HG_MENU_SCENE_H
