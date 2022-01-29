#include "GameData.h"

#include <gf/Log.h>
#include <gf/Tmx.h>
#include <gf/TmxOps.h>

namespace hg {

  namespace {

    class LayersMaker : public gf::TmxVisitor {
    public:
      LayersMaker(gf::ResourceManager& resources, LevelData& data)
      : m_resources(resources)
      , m_data(data)
      {
      }

      virtual void visitTileLayer(const gf::TmxLayers& map, const gf::TmxTileLayer& layer) override {
        if (!layer.visible) {
          return;
        }

        gf::Log::debug("Parsing layer: '%s'\n", layer.name.c_str());
        m_data.layers.push_back(gf::makeTileLayer(map, layer, m_resources));
      }

    private:
      gf::ResourceManager& m_resources;
      LevelData& m_data;
    };

    LevelData makeLevelData(gf::ResourceManager& resources, const gf::Path& path) {
      gf::TmxLayers tmx;
      tmx.loadFromFile(resources.getAbsolutePath("level00.tmx"));

      LevelData data;

      LayersMaker maker(resources, data);
      tmx.visitLayers(maker);

      return data;
    }

  }

  GameData::GameData(gf::ResourceManager& resources)
  {
    levels.push_back(makeLevelData(resources, "level00.tmx"));
    // add more levels later
  }

}
