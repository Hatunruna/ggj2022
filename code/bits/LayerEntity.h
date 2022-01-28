#ifndef HG_LAYER_ENTITY_H
#define HG_LAYER_ENTITY_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <gf/TileLayer.h>

namespace hg {

  class LayerEntity : public gf::Entity {
  public:
    LayerEntity(gf::ResourceManager& resources);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    gf::TileLayer m_tiles;
  };


}


#endif // HG_LAYER_ENTITY_H
