#ifndef HG_LAYER_ENTITY_H
#define HG_LAYER_ENTITY_H

#include <gf/Entity.h>

namespace hg {

  class GameScenery;
  class GameState;

  class LayerEntity : public gf::Entity {
  public:
    LayerEntity(GameScenery& scenery, const GameState& state);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    GameScenery& m_scenery;
    const GameState& m_state;
  };


}


#endif // HG_LAYER_ENTITY_H
