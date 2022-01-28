#include "LayerEntity.h"

#include <iostream>

#include <gf/RenderTarget.h>
#include <gf/Tmx.h>
#include <gf/TmxOps.h>

namespace hg {

  namespace {

    class LayersMaker : public gf::TmxVisitor {
    public:
      LayersMaker(gf::TileLayer& layer, gf::ResourceManager& resources)
      : m_layer(layer)
      , m_resources(resources)
      {
      }

      virtual void visitTileLayer(const gf::TmxLayers& map, const gf::TmxTileLayer& layer) override {
        if (!layer.visible) {
          return;
        }

        std::cout << "Parsing layer '" << layer.name << "'\n";
        m_layer = gf::makeTileLayer(map, layer, m_resources);
      }

      virtual void visitObjectLayer(const gf::TmxLayers& map, const gf::TmxObjectLayer& layer) override {
        gf::unused(map);

        if (!layer.visible) {
          return;
        }
      }

    private:
      gf::TileLayer& m_layer;
      gf::ResourceManager& m_resources;
    };

  }

  LayerEntity::LayerEntity(gf::ResourceManager& resources)
  {
    LayersMaker maker(m_tiles, resources);

    gf::TmxLayers layers;
    layers.loadFromFile(resources.getAbsolutePath("level00.tmx"));
    layers.visitLayers(maker);
  }

  void LayerEntity::update([[maybe_unused]] gf::Time time) {
  }

  void LayerEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    m_tiles.setPosition({ 0.0f, 0.0f });
    target.draw(m_tiles, states);
  }

}
