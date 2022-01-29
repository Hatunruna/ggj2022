#include "LevelScene.h"

#include <gf/Log.h>
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
  , m_hanzRunLeftAction("hanzRunLeft")
  , m_hanzRunRightAction("hanzRunRight")
  , m_hanzJumpAction("hanzJump")
  , m_gretRunLeftAction("gretRunLeft")
  , m_gretRunRightAction("gretRunRight")
  , m_gretJumpAction("gretJump")
  , m_layer(game.scenery, game.state)
  , m_hanz(game.resources, m_physics, game.audio, Hero::Hanz)
  , m_gret(game.resources, m_physics, game.audio, Hero::Gret)
  {
    setWorldViewCenter(WorldSize / 2);
    setWorldViewSize(WorldSize);
    setClearColor(gf::Color::Black);

    m_hanzRunLeftAction.setContinuous();
    m_hanzRunLeftAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
    m_hanzRunLeftAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadLeft);
    addAction(m_hanzRunLeftAction);

    m_hanzRunRightAction.setContinuous();
    m_hanzRunRightAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
    m_hanzRunRightAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadRight);
    addAction(m_hanzRunRightAction);

    m_hanzJumpAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
    addAction(m_hanzJumpAction);

    m_gretRunLeftAction.setContinuous();
    m_gretRunLeftAction.addScancodeKeyControl(gf::Scancode::A);
    addAction(m_gretRunLeftAction);

    m_gretRunRightAction.setContinuous();
    m_gretRunRightAction.addScancodeKeyControl(gf::Scancode::D);
    addAction(m_gretRunRightAction);

    m_gretJumpAction.addScancodeKeyControl(gf::Scancode::Space);
    addAction(m_gretJumpAction);

    m_quitAction.addScancodeKeyControl(gf::Scancode::Escape);
    m_quitAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Start);
    addAction(m_quitAction);

    addModel(m_physics);

    addWorldEntity(m_layer);
    addWorldEntity(m_hanz);
    addWorldEntity(m_gret);
  }

  void LevelScene::loadLevel(const GameData& data, std::size_t number) {
    m_physics.loadLevel(data, number);

    assert(number < data.levels.size());
    const LevelData & level = data.levels[number];

    for (auto & platform : level.platforms) {
      PlatformState state;

      switch (platform.type)
      {
        case PlatformType::Neutral_H:
        case PlatformType::Neutral_V:
          state.color = HeroColor::NEUTRAL;
          break;
        case PlatformType::Red_H:
        case PlatformType::Red_V:
          state.color = HeroColor::RED;
          break;
        case PlatformType::Blue_H:
        case PlatformType::Blue_V:
          state.color = HeroColor::BLUE;
          break;
      }

      m_game.state.level.platforms.push_back(state);
    }
  }

  void LevelScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }

    if (m_quitAction.isActive()) {
      m_game.pushScene(m_game.quit);
    }

    if (m_hanzJumpAction.isActive()) {
      gf::Log::debug("hanz jump pressed\n");
      m_hanz.jump();
    }

    if (m_hanzRunLeftAction.isActive()) {
      m_hanz.setDirection(gf::Direction::Left);
    } else if (m_hanzRunRightAction.isActive()) {
      m_hanz.setDirection(gf::Direction::Right);
    } else {
      m_hanz.setDirection(gf::Direction::Center);
    }

    if (m_gretJumpAction.isActive()) {
      m_gret.jump();
    }

    if (m_gretRunLeftAction.isActive()) {
      m_gret.setDirection(gf::Direction::Left);
    } else if (m_gretRunRightAction.isActive()) {
      m_gret.setDirection(gf::Direction::Right);
    } else {
      m_gret.setDirection(gf::Direction::Center);
    }
  }

}
