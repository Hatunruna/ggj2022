#include "MenuScene.h"

#include <gf/Coordinates.h>
#include <gf/Log.h>
#include <gf/Sprite.h>

#include "GameHub.h"

namespace hg {

  MenuScene::MenuScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_backgroundTexture(game.resources.getTexture("title.png"))
  , m_upAction("UpAction")
  , m_downAction("DownAction")
  , m_triggerAction("TriggerAction")
  , m_quitAction("Quit")
  , m_newGame("New Game", game.resources.getFont("Underdog.otf"))
  , m_continue("Continue", game.resources.getFont("Underdog.otf"))
  , m_credits("Credits", game.resources.getFont("Underdog.otf"))
  , m_quit("Quit", game.resources.getFont("Underdog.otf"))
  {
    setClearColor(gf::Color::Black);

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

    setupButton(m_newGame, [&] () {
        gf::Log::debug("New Game pressed!\n");
        m_game.replaceAllScenes(m_game.select);
    });

    setupButton(m_continue, [&] () {
        gf::Log::debug("Continue pressed!\n");
        m_game.replaceAllScenes(m_game.select);
    });

    setupButton(m_credits, [&] () {
        gf::Log::debug("Credits pressed!\n");
        m_game.replaceAllScenes(m_game.credits);
    });

    setupButton(m_quit, [&] () {
        gf::Log::debug("Quit pressed!\n");
        m_game.replaceAllScenes(m_game.start);
    });
  }

  void MenuScene::doHandleActions([[maybe_unused]] gf::Window& window) {
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

  void MenuScene::doProcessEvent(gf::Event& event) {
    switch (event.type)
    {
      case gf::EventType::MouseMoved:
        m_widgets.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;
    }
  }

  void MenuScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    gf::Coordinates coords(target);

    float backgroundHeight = coords.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
    float backgroundScale = backgroundHeight / m_backgroundTexture.getSize().height;

    gf::Sprite background(m_backgroundTexture);
    background.setColor(gf::Color::Opaque(0.20f));
    background.setPosition(coords.getCenter());
    background.setAnchor(gf::Anchor::Center);
    background.setScale(backgroundScale);
    target.draw(background, states);

    target.setView(getHudView());

    unsigned titleCharacterSize = coords.getRelativeCharacterSize(0.1f);

    gf::Text title("Hanz and Gret", m_game.resources.getFont("Underdog.otf"), titleCharacterSize);
    title.setColor(gf::Color::White);
    title.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
    title.setAnchor(gf::Anchor::TopCenter);
    target.draw(title, states);

    constexpr float characterSize = 0.075f;
    constexpr float spaceBetweenButton = 0.045f;
    constexpr gf::Vector2f backgroundSize(0.5f, 0.3f);

    const float paragraphWidth = coords.getRelativeSize(backgroundSize - 0.05f).x;
    const float paddingSize = coords.getRelativeSize({0.01f, 0.f}).x;
    const unsigned resumeCharacterSize = coords.getRelativeCharacterSize(characterSize);

    m_newGame.setCharacterSize(resumeCharacterSize);
    m_newGame.setPosition(coords.getRelativePoint({0.275f, 0.425f}));
    m_newGame.setParagraphWidth(paragraphWidth);
    m_newGame.setPadding(paddingSize);

    m_continue.setCharacterSize(resumeCharacterSize);
    m_continue.setPosition(coords.getRelativePoint({0.275f, 0.425f + characterSize + spaceBetweenButton}));
    m_continue.setParagraphWidth(paragraphWidth);
    m_continue.setPadding(paddingSize);

    m_credits.setCharacterSize(resumeCharacterSize);
    m_credits.setPosition(coords.getRelativePoint({0.275f, 0.425f + (characterSize + spaceBetweenButton) * 2}));
    m_credits.setParagraphWidth(paragraphWidth);
    m_credits.setPadding(paddingSize);

    m_quit.setCharacterSize(resumeCharacterSize);
    m_quit.setPosition(coords.getRelativePoint({0.275f, 0.425f + (characterSize + spaceBetweenButton) * 3}));
    m_quit.setParagraphWidth(paragraphWidth);
    m_quit.setPadding(paddingSize);

    m_widgets.render(target, states);
  }

  void MenuScene::doShow() {
    m_widgets.clear();

    m_newGame.setDefault();
    m_widgets.addWidget(m_newGame);

    m_continue.setDefault();
    m_widgets.addWidget(m_continue);

    m_credits.setDefault();
    m_widgets.addWidget(m_credits);

    m_quit.setDefault();
    m_widgets.addWidget(m_quit);

    m_widgets.selectNextWidget();
  }


}
