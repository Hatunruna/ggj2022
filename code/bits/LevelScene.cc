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
  , m_music(game.audio.getMusic("stage.ogg"))
  , m_quitAction("Quit")
  , m_hanzRunLeftAction("hanzRunLeft")
  , m_hanzRunRightAction("hanzRunRight")
  , m_hanzJumpAction("hanzJump")
  , m_hanzActivateAction("hanzActivate")
  , m_gretRunLeftAction("gretRunLeft")
  , m_gretRunRightAction("gretRunRight")
  , m_gretJumpAction("gretJump")
  , m_gretActivateAction("gretActivate")
  , m_layer(game.resources, game.data, game.scenery, game.state)
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

    m_hanzActivateAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::X);
    addAction(m_hanzActivateAction);

    m_gretRunLeftAction.setContinuous();
    m_gretRunLeftAction.addScancodeKeyControl(gf::Scancode::A);
    addAction(m_gretRunLeftAction);

    m_gretRunRightAction.setContinuous();
    m_gretRunRightAction.addScancodeKeyControl(gf::Scancode::D);
    addAction(m_gretRunRightAction);

    m_gretJumpAction.addScancodeKeyControl(gf::Scancode::Space);
    addAction(m_gretJumpAction);

    m_gretActivateAction.addScancodeKeyControl(gf::Scancode::E);
    addAction(m_gretActivateAction);

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
    m_game.state.level.loadLevel(data, number);
  }

  void LevelScene::stopMusic() {
    m_music.stop();
  }

  void LevelScene::onActivityChange(bool active) {
    if (active && !isPaused()) {
      m_music.setLoop(true);
      m_music.play();m_music.setVolume(100.0f);
    } else if (!active && isPaused()) {
      m_music.setVolume(10.0f);
    } else if (active && isPaused()) {
      if (m_music.getStatus() == sf::Music::Stopped) {
        m_music.play();
      }
      m_music.setVolume(100.0f);
    } else {
      m_music.stop();
    }
  }

  void LevelScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }

    if (m_quitAction.isActive()) {
      pause();
      m_game.pushScene(m_game.quit);
    }

    if (m_hanzJumpAction.isActive()) {
      m_hanz.jump();
    } else if (m_hanzActivateAction.isActive()) {
      m_hanz.activate();
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
    } else if (m_gretActivateAction.isActive()) {
      m_gret.activate();
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
