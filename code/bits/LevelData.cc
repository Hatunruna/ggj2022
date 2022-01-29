#include "LevelData.h"

#include <cassert>

#include <gf/Log.h>

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
          assert(m_data.tiles(gf::vec(i, j)) == PlatformType::None);
          m_data.tiles(gf::vec(i, j)) = static_cast<PlatformType>(gid);
        }
      }

    private:
      LevelData& m_data;
    };

    PlatformData makeHorizontalPlatform(const gf::Array2D<PlatformType, int>& tiles, gf::Vector2i start, PlatformType end, PlatformType type) {
      PlatformData platform;
      platform.type == type;
      platform.segment.p0 = platform.segment.p1 = start;

      while (tiles(platform.segment.p1) != end) {
        ++platform.segment.p1.x;
        assert(tiles.isValid(platform.segment.p1));
      }

      return platform;
    }

    PlatformData makeVerticalPlatform(const gf::Array2D<PlatformType, int>& tiles, gf::Vector2i start, PlatformType end, PlatformType type) {
      PlatformData platform;
      platform.type == type;
      platform.segment.p0 = platform.segment.p1 = start;

      while (tiles(platform.segment.p1) != end) {
        ++platform.segment.p1.y;
        assert(tiles.isValid(platform.segment.p1));
      }

      return platform;
    }

  }

  LevelData::LevelData()
  : tiles(LevelSize, PlatformType::None)
  {
  }

  LevelData LevelData::makeFromTmx(const gf::TmxLayers& tmx) {
    LevelData data;
    LayersDataMaker maker(data);
    tmx.visitLayers(maker);

    for (auto position : data.tiles.getPositionRange()) {
      switch (data.tiles(position)) {
        case PlatformType::Neutral_HL:
          data.platforms.push_back(makeHorizontalPlatform(data.tiles, position, PlatformType::Neutral_HR, PlatformType::Neutral_H));
          break;
        case PlatformType::Red_HL:
          data.platforms.push_back(makeHorizontalPlatform(data.tiles, position, PlatformType::Red_HR, PlatformType::Red_H));
          break;
        case PlatformType::Blue_HL:
          data.platforms.push_back(makeHorizontalPlatform(data.tiles, position, PlatformType::Blue_HR, PlatformType::Blue_H));
          break;
        case PlatformType::Neutral_VU:
          data.platforms.push_back(makeVerticalPlatform(data.tiles, position, PlatformType::Neutral_VD, PlatformType::Neutral_V));
          break;
        case PlatformType::Red_VU:
          data.platforms.push_back(makeVerticalPlatform(data.tiles, position, PlatformType::Red_VD, PlatformType::Red_V));
          break;
        case PlatformType::Blue_VU:
          data.platforms.push_back(makeVerticalPlatform(data.tiles, position, PlatformType::Blue_VD, PlatformType::Blue_V));
          break;
      }
    }

    gf::Log::debug("Number of platforms: %zu\n", data.platforms.size());

    // limits harcoded for now...

    data.limits.push_back({ gf::vec(0,0), gf::vec(0, 31) });
    data.limits.push_back({ gf::vec(0,0), gf::vec(31, 0) });
    data.limits.push_back({ gf::vec(31,31), gf::vec(0, 31) });
    data.limits.push_back({ gf::vec(31,31), gf::vec(31, 0) });

    return data;
  }

}

