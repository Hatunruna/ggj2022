#include "MenuScene.h"

#include <gf/Log.h>
#include <gf/Coordinates.h>
#include "GameHub.h"

namespace hg {

    SelectLevelScene::SelectLevelScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_upAction("UpAction")
  , m_downAction("DownAction")
  , m_triggerAction("TriggerAction")
  , m_quitAction("Quit")
  , m_menuTitleEntity(game.resources, game.audio)
  , m_tutoButton("Tuto", game.resources.getFont("Underdog.otf"))
  , m_level1("Level 1", game.resources.getFont("Underdog.otf"))
  , m_theme(game.audio.getMusic("theme.ogg"))
  {
    setClearColor(gf::Color::Black);
    addHudEntity(m_menuTitleEntity);

    m_quitAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
    m_quitAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_quitAction);

    m_upAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
    m_upAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
    m_upAction.addScancodeKeyControl(gf::Scancode::Up);
    addAction(m_upAction);

    m_downAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
    m_downAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
    m_downAction.addScancodeKeyControl(gf::Scancode::Down);
    addAction(m_downAction);

    m_triggerAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
    m_triggerAction.addScancodeKeyControl(gf::Scancode::Return);
    m_triggerAction.addMouseButtonControl(gf::MouseButton::Left);
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

    setupButton(m_tutoButton, [&] () {
      gf::Log::debug("Tuto button pressed!\n");
      m_game.state.levelIndex = 0;
      m_game.level.loadLevel(m_game.data, m_game.state.levelIndex);
      m_theme.stop();
      m_game.replaceAllScenes(m_game.level);
    });

    setupButton(m_level1, [&] () {
      gf::Log::debug("Level 1 button pressed!\n");
      m_game.state.levelIndex = 1;
      m_game.level.loadLevel(m_game.data, m_game.state.levelIndex);
      m_theme.stop();
      m_game.replaceAllScenes(m_game.level);
    });
  }

  void SelectLevelScene::doHandleActions([[maybe_unused]] gf::Window& window) {
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

  void SelectLevelScene::doProcessEvent(gf::Event& event) {
    switch (event.type)
    {
      case gf::EventType::MouseMoved:
        m_widgets.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;
    }
  }

  void SelectLevelScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    constexpr float characterSize = 0.075f;
    constexpr float spaceBetweenButton = 0.025f;
    constexpr gf::Vector2f backgroundSize(0.5f, 0.3f);

    target.setView(getHudView());
    gf::Coordinates coords(target);

    const float paragraphWidth = coords.getRelativeSize(backgroundSize - 0.05f).x;
    const float paddingSize = coords.getRelativeSize({0.01f, 0.f}).x;
    const unsigned resumeCharacterSize = coords.getRelativeCharacterSize(characterSize);

    m_tutoButton.setCharacterSize(resumeCharacterSize);
    m_tutoButton.setPosition(coords.getRelativePoint({0.275f, 0.425f}));
    m_tutoButton.setParagraphWidth(paragraphWidth);
    m_tutoButton.setPadding(paddingSize);

    m_level1.setCharacterSize(resumeCharacterSize);
    m_level1.setPosition(coords.getRelativePoint({0.275f, 0.425f + characterSize + spaceBetweenButton}));
    m_level1.setParagraphWidth(paragraphWidth);
    m_level1.setPadding(paddingSize);

    m_widgets.render(target, states);
    m_menuTitleEntity.render(target,states);
  }

  void SelectLevelScene::doShow() {
    m_widgets.clear();

    m_tutoButton.setDefault();
    m_widgets.addWidget(m_tutoButton);

    m_level1.setDefault();
    m_widgets.addWidget(m_level1);

    m_widgets.selectNextWidget();
  }


}
