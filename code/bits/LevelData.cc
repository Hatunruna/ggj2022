#include "LevelData.h"

#include "Constants.h"

namespace hg {

  namespace {

    class LayersDataMaker : public gf::TmxVisitor {
    public:
      LayersDataMaker(LevelData& data)
      : m_data(data)
      {
      }

      virtual void visitTileLayer(const gf::TmxLayers& map, const gf::TmxTileLayer& layer) override {
        if (!layer.visible) {
          return;
        }

        if (layer.name != "platforms") {
          return;
        }

        int k = 0;

        for (auto& cell : layer.cells) {
          int i = k % map.mapSize.width;
          int j = k / map.mapSize.width;
          assert(j < map.mapSize.height);

          ++k;

          int gid = cell.gid;

          if (gid == 0) {
            continue;
          }

          const gf::TmxTileset *tileset = map.getTileSetFromGID(gid);
          assert(tileset);
          gid = gid - tileset->firstGid;

          assert(m_data.tiles.isValid(gf::vec(i, j)));
          assert(m_data.tiles(gf::vec(i, j)) == PlatformData::None);
          m_data.tiles(gf::vec(i, j)) = static_cast<PlatformData>(gid);
        }
      }

    private:
      LevelData& m_data;
    };
  }

  LevelData::LevelData()
  : tiles(LevelSize, PlatformData::None)
  {
  }

  LevelData LevelData::makeFromTmx(const gf::TmxLayers& tmx) {
    LevelData data;
    LayersDataMaker maker(data);
    tmx.visitLayers(maker);



    return data;
  }

}

