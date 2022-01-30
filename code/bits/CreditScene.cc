#include "CreditScene.h"

#include <gf/Log.h>
#include <gf/Coordinates.h>
#include "GameHub.h"

namespace hg {

  CreditScene::CreditScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_quitAction("Quit")
  , m_triggerAction("TriggerAction")
  , m_quitButton("Quit", game.resources.getFont("Underdog.otf"))
  , m_creditEntity(game.resources, game.audio)
  , m_upAction("UpAction")
  , m_downAction("DownAction")
  {
    setClearColor(gf::Color::Black);

    m_quitAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
    m_quitAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_quitAction);

    m_upAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
    m_upAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
    m_upAction.addScancodeKeyControl(gf::Scancode::Up);
    addAction(m_upAction);

    m_downAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
    m_downAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
    m_downAction.addScancodeKeyControl(gf::Scancode::Down);
    addAction(m_downAction);

    m_triggerAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
    m_triggerAction.addMouseButtonControl(gf::MouseButton::Left);
    m_triggerAction.addScancodeKeyControl(gf::Scancode::Return);
    addAction(m_triggerAction);

    auto setupButton = [&] (gf::TextButtonWidget& button, auto callback) {
        button.setDefaultTextColor(gf::Color::Black);
        button.setDefaultBackgroundColor(gf::Color::Gray(0.7f));
        button.setSelectedTextColor(gf::Color::Black);
        button.setSelectedBackgroundColor(gf::Color::Green);
        button.setDisabledTextColor(gf::Color::Black);
        button.setDisabledBackgroundColor(gf::Color::Red);
        button.setAnchor(gf::Anchor::TopLeft);
        button.setAlignment(gf::Alignment::Center);
        button.setCallback(callback);
        m_widgets.addWidget(button);
    };

    setupButton(m_quitButton, [&] () {
        gf::Log::debug("Quit pressed!\n");
        m_game.replaceAllScenes(m_game.start);
    });
  }

  void CreditScene::doHandleActions([[maybe_unused]] gf::Window& window) {
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

    if (m_quitAction.isActive()) {
      m_game.replaceScene(m_game.start);
    }
  }

  void CreditScene::doProcessEvent(gf::Event& event) {
    switch (event.type)
    {
      case gf::EventType::MouseMoved:
        m_widgets.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;
    }
  }

  void CreditScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {

    target.setView(getHudView());
    gf::Coordinates coords(target);

    constexpr float characterSize = 0.075f;
    constexpr float spaceBetweenButton = 0.045f;
    constexpr gf::Vector2f backgroundSize(0.5f, 0.3f);

    const float paragraphWidth = coords.getRelativeSize(backgroundSize - 0.05f).x;
    const float paddingSize = coords.getRelativeSize({0.01f, 0.f}).x;
    const unsigned resumeCharacterSize = coords.getRelativeCharacterSize(characterSize);

    m_quitButton.setCharacterSize(resumeCharacterSize);
    m_quitButton.setPosition(coords.getRelativePoint({0.275f, 0.825f}));
    m_quitButton.setParagraphWidth(paragraphWidth);
    m_quitButton.setPadding(paddingSize);

    m_widgets.render(target, states);
    m_creditEntity.render(target,states);
  }

  void CreditScene::doShow() {
    m_widgets.clear();

    m_quitButton.setDefault();
    m_widgets.addWidget(m_quitButton);

    m_widgets.selectNextWidget();
  }

}
