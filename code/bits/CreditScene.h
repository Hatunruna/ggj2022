#ifndef HG_CREDIT_SCENE_H
#define HG_CREDIT_SCENE_H

#include "CreditEntity.h"

#include <gf/Scene.h>
#include <gf/Action.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>
#include <gf/Event.h>
#include <gf/Text.h>

namespace hg {

  struct GameHub;

  class CreditScene : public gf::Scene {
  public:
      CreditScene(GameHub& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;
    void doShow() override;

  private:
    GameHub& m_game;

    gf::Action m_quitAction;
    gf::Action m_triggerAction;
    gf::TextButtonWidget m_quitButton;
    gf::WidgetContainer m_widgets;

    gf::Action m_upAction;
    gf::Action m_downAction;

    CreditEntity m_creditEntity;
  };

}

#endif // HG_CREDIT_SCENE_H
