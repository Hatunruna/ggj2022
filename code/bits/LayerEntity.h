#ifndef HG_LAYER_ENTITY_H
#define HG_LAYER_ENTITY_H

#include <gf/Entity.h>

namespace hg {

  struct GameData;
  struct GameScenery;
  struct GameState;

  class LayerEntity : public gf::Entity {
  public:
    LayerEntity(const GameData& data, GameScenery& scenery, const GameState& state);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    const GameData& m_data;
    GameScenery& m_scenery;
    const GameState& m_state;
  };


}


#endif // HG_LAYER_ENTITY_H
