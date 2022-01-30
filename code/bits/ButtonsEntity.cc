#include "ButtonsEntity.h"

#include <cassert>

#include <gf/VectorOps.h>

#include "Constants.h"
#include "GameData.h"
#include "GameState.h"
#include "PhysicsModel.h"

namespace hg {

  namespace {

    HeroColor changeColor(HeroColor color) {
      switch (color) {
        case HeroColor::Red:
          return HeroColor::Blue;
        case HeroColor::Blue:
          return HeroColor::Red;
        case HeroColor::Neutral:
          assert(false);
          break;
      }

      return HeroColor::Neutral;
    }

  }

  ButtonsEntity::ButtonsEntity(gf::ResourceManager& resources, const GameData& data, GameState& state, PhysicsModel& physics)
  : m_data(data)
  , m_state(state)
  , m_physics(physics)
  {
  }

  void ButtonsEntity::activate(Hero hero) {
    gf::Vector2f heroPosition = m_physics.getPosition(hero);

    // find a button

    assert(m_state.levelIndex  < m_data.levels.size());
    auto & data = m_data.levels[m_state.levelIndex];

    for (auto & button : data.buttons) {
      gf::Vector2f position = button.position * TileSize + TileSize / 2;

      if (gf::squareDistance(heroPosition, position) >= gf::square(ButtonDistance)) {
        continue;
      }

      // found a button

      switch (button.type) {
        case ButtonType::Platform: {
          PlatformState& state = m_state.level.platforms[button.index];
          state.color = changeColor(state.color);
          m_physics.switchColor(button.index);
          break;
        }
        case ButtonType::Lift:
          break;
        default:
          assert(false);
          break;
      }

    }

  }

  void ButtonsEntity::update(gf::Time time) {


  }

  void ButtonsEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {

  }

}
