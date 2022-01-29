#include "LevelScene.h"

#include <gf/Color.h>

#include "GameHub.h"

namespace hg {

  namespace {

    constexpr gf::Vector2f WorldSize = gf::vec(1024.0f, 1024.0f);

  }

  LevelScene::LevelScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_quitAction("Quit")
  , m_layer(game.scenery, game.state)
  , m_hanz(game.resources, game.audio, HeroColor::Red, WorldSize * 0.2f)
  , m_gret(game.resources, game.audio, HeroColor::Blue, WorldSize * 0.8f)
  {
    setWorldViewCenter(WorldSize / 2);
    setWorldViewSize(WorldSize);
    setClearColor(gf::Color::Black);

    m_quitAction.addScancodeKeyControl(gf::Scancode::Escape);
    m_quitAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Start);
    addAction(m_quitAction);

    addWorldEntity(m_layer);
    addWorldEntity(m_hanz);
    addWorldEntity(m_gret);
  }

  void LevelScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }

    if (m_quitAction.isActive()) {
      m_game.pushScene(m_game.quit);
    }
  }

}
