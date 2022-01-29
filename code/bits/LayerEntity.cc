#include "LayerEntity.h"

#include <cassert>

#include <gf/RenderTarget.h>

#include "GameScenery.h"
#include "GameState.h"

namespace hg {

  LayerEntity::LayerEntity(GameScenery& scenery, const GameState& state)
  : m_scenery(scenery)
  , m_state(state)
  {
  }

  void LayerEntity::update([[maybe_unused]] gf::Time time) {
  }

  void LayerEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    assert(m_state.levelIndex < m_scenery.levels.size());
    LevelScenery& currentLevel = m_scenery.levels[m_state.levelIndex];

    for (auto & layer : currentLevel.layers) {
      target.draw(layer, states);
    }

  }

}
