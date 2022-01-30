#include "LayerEntity.h"

#include <cassert>

#include <gf/Color.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>

#include "Constants.h"
#include "GameData.h"
#include "GameScenery.h"
#include "GameState.h"

namespace hg {

  LayerEntity::LayerEntity(gf::ResourceManager& resources, const GameData& data, GameScenery& scenery, const GameState& state)
  : m_data(data)
  , m_scenery(scenery)
  , m_state(state)
  , m_backgroundTexture(resources.getTexture("stage-background.jpg"))
  {
  }

  void LayerEntity::update([[maybe_unused]] gf::Time time) {
  }

  void LayerEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    gf::Sprite background;
    background.setTexture(m_backgroundTexture);
    target.draw(background, states);

    assert(m_state.levelIndex < m_data.levels.size());
    const LevelData& data = m_data.levels[m_state.levelIndex];

    assert(data.platforms.size() == m_state.level.platforms.size());

    for (std::size_t i = 0; i < data.platforms.size(); ++i) {
      static constexpr gf::Vector2f Shrink = 0.7f * TileSize;

      auto & platform = data.platforms[i];
      gf::RectF rect = gf::RectF::fromMinMax(platform.segment.p0 * TileSize + Shrink, (platform.segment.p1 + 1) * TileSize - Shrink);
      gf::RectangleShape shape(rect);

      switch (m_state.level.platforms[i].color) {
        case HeroColor::Red:
          shape.setColor(gf::Color::fromRgba32(0xFF, 0xB7, 0x61));
          break;
        case HeroColor::Blue:
          shape.setColor(gf::Color::fromRgba32(0xB0, 0xCA, 0xFE));
          break;
        case HeroColor::Neutral:
          shape.setColor(gf::Color::Gray(0.25f));
          break;
      }

      target.draw(shape, states);
    }

    assert(m_state.levelIndex < m_scenery.levels.size());
    LevelScenery& scenery = m_scenery.levels[m_state.levelIndex];

    for (auto & layer : scenery.layers) {
      target.draw(layer, states);
    }

  }

}
