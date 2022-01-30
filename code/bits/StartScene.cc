#include "StartScene.h"

#include <gf/Color.h>

#include "GameHub.h"

namespace hg {

  StartScene::StartScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_startAction("Start")
  , m_fullscreenAction("Fullscreen")
  , m_titleEntity(game.resources, game.audio)
  {
    setClearColor(gf::Color::Black);

    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::X);
    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Y);
    m_startAction.addKeycodeKeyControl(gf::Keycode::Space);
    m_startAction.addMouseButtonControl(gf::MouseButton::Left);
    addAction(m_startAction);

    m_fullscreenAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Guide);
    m_fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
    addAction(m_fullscreenAction);

    addHudEntity(m_titleEntity);
  }

  void StartScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }

    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_startAction.isActive()) {
      m_game.replaceScene(m_game.menu);
    }
  }

}
