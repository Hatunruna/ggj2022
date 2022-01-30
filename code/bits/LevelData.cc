#include "LevelData.h"

#include <cassert>

#include <gf/Log.h>
#include <gf/Direction.h>

#include "Constants.h"

namespace hg {

  namespace {

    enum LayerName {
      Platforms,
      Cables,
      Lifts,
    };

    LayerName toLayerName(const std::string& name) {
      if (name == "platforms") {
        return LayerName::Platforms;
      }

      if (name == "cables") {
        return LayerName::Cables;
      }

      if (name == "lifts") {
        return LayerName::Lifts;
      }

      gf::Log::debug("Unknown layer: %s\n", name.c_str());
      assert(false);
      return LayerName::Platforms;
    }

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

        auto name = toLayerName(layer.name);

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

          switch (name) {
            case LayerName::Platforms:
              assert(m_data.platform_tiles.isValid(gf::vec(i, j)));
              assert(m_data.platform_tiles(gf::vec(i, j)) == PlatformType::None);
              assert(0 <= gid && gid <= 31);
              m_data.platform_tiles(gf::vec(i, j)) = static_cast<PlatformType>(gid);
              break;
            case LayerName::Cables:
              assert(m_data.cable_tiles.isValid(gf::vec(i, j)));
              assert(m_data.cable_tiles(gf::vec(i, j)) == CableType::None);
              assert(32 <= gid && gid <= 43);
              m_data.cable_tiles(gf::vec(i, j)) = static_cast<CableType>(gid);
              break;
            case LayerName::Lifts:
              assert(m_data.lift_tiles.isValid(gf::vec(i, j)));
              assert(m_data.lift_tiles(gf::vec(i, j)) == LiftType::None);
              assert(44 <= gid && gid <= 46);
              m_data.lift_tiles(gf::vec(i, j)) = static_cast<LiftType>(gid);
              break;
          }
        }
      }

    private:
      LevelData& m_data;
    };

    PlatformData makeHorizontalPlatform(const gf::Array2D<PlatformType, int>& tiles, gf::Vector2i start, PlatformType end, PlatformType type) {
      PlatformData platform;
      platform.type = type;
      platform.segment.p0 = platform.segment.p1 = start;

      do {
        ++platform.segment.p1.x;
        assert(tiles.isValid(platform.segment.p1));
      } while (tiles(platform.segment.p1) != end);

      return platform;
    }

    PlatformData makeVerticalPlatform(const gf::Array2D<PlatformType, int>& tiles, gf::Vector2i start, PlatformType end, PlatformType type) {
      PlatformData platform;
      platform.type = type;
      platform.segment.p0 = platform.segment.p1 = start;

      do {
        ++platform.segment.p1.y;
        assert(tiles.isValid(platform.segment.p1));
      } while (tiles(platform.segment.p1) != end);

      return platform;
    }

    LiftData makeLift(const gf::Array2D<LiftType, int>& tiles, gf::Vector2i start) {
      LiftData lift;
      lift.segment.p0 = lift.segment.p1 = start;

      do {
        ++lift.segment.p1.y;
        assert(tiles.isValid(lift.segment.p1));
        assert(tiles(lift.segment.p1) == LiftType::Lift_V || tiles(lift.segment.p1) == LiftType::Lift_D);
      } while (tiles(lift.segment.p1) != LiftType::Lift_D);

      return lift;
    }

    gf::Direction computeNextDirection(CableType type, gf::Direction current) {
      switch (current) {
        case gf::Direction::Center:
          switch (type) {
            case CableType::Straight_HL:
              return gf::Direction::Right;
            case CableType::Straight_HR:
              return gf::Direction::Left;
            case CableType::Straight_VU:
              return gf::Direction::Down;
            case CableType::Straight_VD:
              return gf::Direction::Up;
            default:
              gf::Log::debug("Wrong cable type: %i\n", (int) type);
              assert(false);
              break;
          }
          break;
        case gf::Direction::Up:
          switch (type) {
            case CableType::Straight_VU:
              return gf::Direction::Center;
            case CableType::Straight_V:
            case CableType::Cross:
              return gf::Direction::Up;
            case CableType::Turn_LD:
              return gf::Direction::Left;
            case CableType::Turn_RD:
              return gf::Direction::Right;
            default:
              gf::Log::debug("Wrong cable type: %i\n", (int) type);
              assert(false);
              break;
          }
          break;
        case gf::Direction::Down:
          switch (type) {
            case CableType::Straight_VD:
              return gf::Direction::Center;
            case CableType::Straight_V:
            case CableType::Cross:
              return gf::Direction::Down;
            case CableType::Turn_LU:
              return gf::Direction::Left;
            case CableType::Turn_RU:
              return gf::Direction::Right;
            default:
              gf::Log::debug("Wrong cable type: %i\n", (int) type);
              assert(false);
              break;
          }
          break;
        case gf::Direction::Right:
          switch (type) {
            case CableType::Straight_HR:
              return gf::Direction::Center;
            case CableType::Straight_H:
            case CableType::Cross:
              return gf::Direction::Right;
            case CableType::Turn_LD:
              return gf::Direction::Down;
            case CableType::Turn_LU:
              return gf::Direction::Up;
            default:
              gf::Log::debug("Wrong cable type: %i\n", (int) type);
              assert(false);
              break;
          }
          break;
        case gf::Direction::Left:
          switch (type) {
            case CableType::Straight_HL:
              return gf::Direction::Center;
            case CableType::Straight_H:
            case CableType::Cross:
              return gf::Direction::Left;
            case CableType::Turn_RD:
              return gf::Direction::Down;
            case CableType::Turn_RU:
              return gf::Direction::Up;
            default:
              assert(false);
              break;
          }
          break;
        default:
          assert(false);
          break;
      }

      return gf::Direction::Center;
    }

    template<typename T>
    std::size_t findSegment(const std::vector<T>& data, gf::Vector2i position) {
      for (std::size_t i = 0; i < data.size(); ++i) {
        gf::SegmentI segment = data[i].segment;

        if (segment.p0.x == segment.p1.x) {
          assert(segment.p0.y < segment.p1.y);

          if (position.x != segment.p0.x) {
            continue;
          }

          if (segment.p0.y <= position.y && position.y <= segment.p1.y) {
            return i;
          }
        } else {
          assert(segment.p0.y == segment.p1.y);
          assert(segment.p0.x < segment.p1.x);

          if (position.y != segment.p0.y) {
            continue;
          }

          if (segment.p0.x <= position.x && position.x <= segment.p1.x) {
            return i;
          }
        }
      }

      assert(false);
      return data.size();
    }

    gf::Vector2i followCable(const gf::Array2D<CableType, int>& tiles, ButtonData& button) {
      gf::Vector2i position = button.position;
      gf::Direction direction = gf::Direction::Center;

      gf::Log::debug("Start of cable: (%i,%i)\n", position.x, position.y);

      do {
        direction = computeNextDirection(tiles(position), direction);
        position += gf::displacement(direction);
        gf::Log::debug("\t(%i,%i)\n", position.x, position.y);
      } while (direction != gf::Direction::Center);

      gf::Log::debug("End of cable: (%i,%i)\n", position.x, position.y);
      return position;
    }

  }

  LevelData::LevelData()
  : platform_tiles(LevelSize, PlatformType::None)
  , cable_tiles(LevelSize, CableType::None)
  , lift_tiles(LevelSize, LiftType::None)
  {
  }

  LevelData LevelData::makeFromTmx(const gf::TmxLayers& tmx) {
    LevelData data;
    LayersDataMaker maker(data);
    tmx.visitLayers(maker);

    for (auto position : data.platform_tiles.getPositionRange()) {
      switch (data.platform_tiles(position)) {
        case PlatformType::Neutral_HL:
          data.platforms.push_back(makeHorizontalPlatform(data.platform_tiles, position, PlatformType::Neutral_HR, PlatformType::Neutral_H));
          break;
        case PlatformType::Red_HL:
          data.platforms.push_back(makeHorizontalPlatform(data.platform_tiles, position, PlatformType::Red_HR, PlatformType::Red_H));
          break;
        case PlatformType::Blue_HL:
          data.platforms.push_back(makeHorizontalPlatform(data.platform_tiles, position, PlatformType::Blue_HR, PlatformType::Blue_H));
          break;
        case PlatformType::Neutral_VU:
          data.platforms.push_back(makeVerticalPlatform(data.platform_tiles, position, PlatformType::Neutral_VD, PlatformType::Neutral_V));
          break;
        case PlatformType::Red_VU:
          data.platforms.push_back(makeVerticalPlatform(data.platform_tiles, position, PlatformType::Red_VD, PlatformType::Red_V));
          break;
        case PlatformType::Blue_VU:
          data.platforms.push_back(makeVerticalPlatform(data.platform_tiles, position, PlatformType::Blue_VD, PlatformType::Blue_V));
          break;
        case PlatformType::Red_Start:
          data.hanz = position;
          gf::Log::debug("Hanz: %i,%i\n", position.x, position.y);
          break;
        case PlatformType::Blue_Start:
          data.gret = position;
          gf::Log::debug("Gret: %i,%i\n", position.x, position.y);
          break;
        case PlatformType::Exit:
          data.exit = position;
          gf::Log::debug("Exit: %i,%i\n", position.x, position.y);
          break;
        case PlatformType::Button_P: {
          ButtonData button;
          button.type = ButtonType::Platform;
          button.position = position;
          data.buttons.push_back(button);
          break;
        }
        case PlatformType::Button_L: {
          ButtonData button;
          button.type = ButtonType::Lift;
          button.position = position;
          data.buttons.push_back(button);
          break;
        }
      }
    }

    gf::Log::debug("Number of platforms: %zu\n", data.platforms.size());

    assert(data.hanz != gf::vec(-1, -1));
    assert(data.gret != gf::vec(-1, -1));

    // limits harcoded for now...

    data.limits.push_back({ gf::vec(0,0), gf::vec(0, 31) });
    data.limits.push_back({ gf::vec(0,0), gf::vec(31, 0) });
    data.limits.push_back({ gf::vec(0, 31), gf::vec(31,31) });
    data.limits.push_back({ gf::vec(31, 0), gf::vec(31,31) });

    // lifts

    for (auto position : data.lift_tiles.getPositionRange()) {
      if (data.lift_tiles(position) == LiftType::Lift_U) {
        data.lifts.push_back(makeLift(data.lift_tiles, position));
      }
    }

    gf::Log::debug("Number of lifts: %zu\n", data.lifts.size());

    for (auto & button : data.buttons) {
      gf::Vector2i position = followCable(data.cable_tiles, button);

      switch (button.type) {
        case ButtonType::Platform:
          button.index = findSegment(data.platforms, position);
          break;
        case ButtonType::Lift:
          button.index = findSegment(data.lifts, position);
          break;
        case ButtonType::Unknown:
          assert(false);
          break;
      }
    }

    gf::Log::debug("Number of buttons: %zu\n", data.buttons.size());

    return data;
  }

}
