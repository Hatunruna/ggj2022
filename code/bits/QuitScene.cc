#include "QuitScene.h"

#include <gf/Coordinates.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>

#include "GameHub.h"

namespace hg {

  QuitScene::QuitScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_upAction("UpAction")
  , m_downAction("DownAction")
  , m_triggerAction("TriggerAction")
  , m_resumeButton("Resume game", game.resources.getFont("Underdog.otf"))
  , m_quitButton("Quit", game.resources.getFont("Underdog.otf"))
  {
    setClearColor(gf::Color::Black);

    m_upAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
    m_upAction.addScancodeKeyControl(gf::Scancode::Up);
    addAction(m_upAction);

    m_downAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
    m_downAction.addScancodeKeyControl(gf::Scancode::Down);
    addAction(m_downAction);

    m_triggerAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
    m_triggerAction.addScancodeKeyControl(gf::Scancode::Return);
    m_triggerAction.addMouseButtonControl(gf::MouseButton::Left);
    addAction(m_triggerAction);

    auto setupButton = [&] (gf::TextButtonWidget& button, auto callback) {
      button.setDefaultTextColor(gf::Color::Black);
      button.setDefaultBackgroundColor(gf::Color::Gray(0.7f));
      button.setSelectedTextColor(gf::Color::Orange);
      button.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
      button.setDisabledTextColor(gf::Color::Red);
      button.setDisabledBackgroundColor(gf::Color::Gray(0.7f));
      button.setAnchor(gf::Anchor::TopLeft);
      button.setAlignment(gf::Alignment::Center);
      button.setCallback(callback);
      m_widgets.addWidget(button);
    };

    setupButton(m_resumeButton, [&] () {gf::Log::debug("Resume button pressed!\n"); m_game.popScene(); });
    setupButton(m_quitButton, [&] () {gf::Log::debug("Quit button pressed!\n"); m_game.replaceAllScenes(m_game.start); });
  }

  void QuitScene::doProcessEvent(gf::Event& event) {
    switch (event.type)
    {
      case gf::EventType::MouseMoved:
        //m_widgets.pointTo(rend.mapPixelToCoords(event.mouseCursor.coords));
        break;

      case gf::EventType::MouseButtonPressed:
        //m_widgets.pointTo(renderer.mapPixelToCoords(event.mouseButton.coords));
        break;
    }
  }

  void QuitScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }

    if (m_upAction.isActive()) {
      m_widgets.selectPreviousWidget();
    }

    if (m_downAction.isActive()) {
      m_widgets.selectNextWidget();
    }

    if (m_triggerAction.isActive()) {
      m_widgets.triggerAction();
    }
  }

  void QuitScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    constexpr float characterSize = 0.1f;
    constexpr float spaceBetweenButton = 0.05f;
    constexpr gf::Vector2f backgroundSize(0.5f, 0.3f);

    target.setView(getHudView());

    gf::Coordinates coords(target);

    const gf::Vector2f backgroundRelativeSize = coords.getRelativeSize(backgroundSize);
    const float paragraphWidth = coords.getRelativeSize(backgroundSize - 0.05f).x;
    const unsigned resumeCharacterSize = coords.getRelativeCharacterSize(characterSize);

    gf::RectangleShape background;
    background.setPosition(coords.getRelativePoint({0.5f, 0.5f}));
    background.setSize(backgroundRelativeSize);
    background.setAnchor(gf::Anchor::Center);
    background.setColor(gf::Color::Gray(0.2f));

    background.draw(target, states);

    m_resumeButton.setCharacterSize(resumeCharacterSize);
    m_resumeButton.setPosition(coords.getRelativePoint({0.275f, 0.425f}));
    m_resumeButton.setParagraphWidth(paragraphWidth);

    m_quitButton.setCharacterSize(resumeCharacterSize);
    m_quitButton.setPosition(coords.getRelativePoint({0.275f, 0.425f + characterSize + spaceBetweenButton}));
    m_quitButton.setParagraphWidth(paragraphWidth);

    m_widgets.render(target, states);
  }

}