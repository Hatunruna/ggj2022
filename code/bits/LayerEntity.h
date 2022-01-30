#ifndef HG_LAYER_ENTITY_H
#define HG_LAYER_ENTITY_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>

namespace hg {

  struct GameData;
  struct GameScenery;
  struct GameState;

  class LayerEntity : public gf::Entity {
  public:
    LayerEntity(gf::ResourceManager& resources, const GameData& data, GameScenery& scenery, const GameState& state);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    const GameData& m_data;
    GameScenery& m_scenery;
    const GameState& m_state;
    gf::Texture& m_backgroundTexture;
  };


}


#endif // HG_LAYER_ENTITY_H
