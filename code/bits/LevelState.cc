#include "LevelState.h"

namespace hg {
  void LevelState::loadLevel(const GameData& data, std::size_t number) {
    assert(number < data.levels.size());
    const LevelData& level = data.levels[number];

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

      platforms.push_back(state);
    }
  }
}