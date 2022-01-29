#include "LevelScenery.h"

#include <gf/TmxOps.h>

namespace hg {

  namespace {

    class LayersSceneryMaker : public gf::TmxVisitor {
    public:
      LayersSceneryMaker(gf::ResourceManager& resources, LevelScenery& scenery)
      : m_resources(resources)
      , m_scenery(scenery)
      {
      }

      virtual void visitTileLayer(const gf::TmxLayers& map, const gf::TmxTileLayer& layer) override {
        if (!layer.visible) {
          return;
        }

        m_scenery.layers.push_back(gf::makeTileLayer(map, layer, m_resources));
      }

    private:
      gf::ResourceManager& m_resources;
      LevelScenery& m_scenery;
    };
  }

  LevelScenery LevelScenery::makeFromTmx(gf::ResourceManager& resources, const gf::TmxLayers& tmx) {
    LevelScenery scenery;

    LayersSceneryMaker maker(resources, scenery);
    tmx.visitLayers(maker);

    return scenery;
  }

}

