#ifndef HG_LAYER_ENTITY_H
#define HG_LAYER_ENTITY_H

#include <gf/Entity.h>

namespace hg {

  class GameData;
  class GameState;

  class LayerEntity : public gf::Entity {
  public:
    LayerEntity(GameData& data, const GameState& state);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    GameData& m_data;
    const GameState& m_state;
  };


}


#endif // HG_LAYER_ENTITY_H
