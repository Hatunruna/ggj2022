#include "MenuScene.h"

#include <gf/Color.h>

#include "GameHub.h"

namespace hg {

  MenuScene::MenuScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_gameAction("Game")
  , m_fullscreenAction("Fullscreen")
  , m_quitAction("Quit")
  , m_menuTitleEntity(game.resources, game.audio)
  , m_levelSelector()
  {
    setClearColor(gf::Color::Black);

    m_gameAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
    m_gameAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
    m_gameAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::X);
    m_gameAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Y);
    m_gameAction.addKeycodeKeyControl(gf::Keycode::Space);
    addAction(m_gameAction);

//     m_fullscreenAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Guide);
    addAction(m_fullscreenAction);

    m_quitAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_quitAction);

    m_levelSelector.reserve(25u);

    addHudEntity(m_menuTitleEntity);
    addHudEntity(m_levelSelector.emplace_back(game.resources, m_game, gf::Vector2f(0.4,0.2), "tuto"));
  }

  void MenuScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }

    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_gameAction.isActive()) {
      m_game.replaceScene(m_game.level);
    }

    if (m_quitAction.isActive()) {
      m_game.replaceScene(m_game.start);
    }
  }

}
