#include "LayerEntity.h"

#include <cassert>

#include <gf/RenderTarget.h>

#include "GameData.h"
#include "GameState.h"

namespace hg {

  LayerEntity::LayerEntity(GameData& data, const GameState& state)
  : m_data(data)
  , m_state(state)
  {
  }

  void LayerEntity::update([[maybe_unused]] gf::Time time) {
  }

  void LayerEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    assert(m_state.level < m_data.levels.size());
    LevelData& currentLevel = m_data.levels[m_state.level];

    for (auto & layer : currentLevel.layers) {
      target.draw(layer, states);
    }

  }

}
