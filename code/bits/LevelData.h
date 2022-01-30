#ifndef HG_LEVEL_DATA_H
#define HG_LEVEL_DATA_H

#include <vector>

#include <gf/Array2D.h>
#include <gf/GeometryTypes.h>
#include <gf/Tmx.h>

namespace hg {
  enum class PlatformType {
    None        = -1,

    Neutral_HL  = 0,
    Neutral_H   = 1,
    Neutral_HR  = 2,
    Neutral_VU  = 3,
    Neutral_V   = 4,
    Neutral_VD  = 5,
    Neutral_C   = 6,

    Button_P    = 7,

    Red_HL      = 8,
    Red_H       = 9,
    Red_HR      = 10,
    Red_VU      = 11,
    Red_V       = 12,
    Red_VD      = 13,
    Red_C       = 14,
    Red_Start   = 15,

    Blue_HL     = 16,
    Blue_H      = 17,
    Blue_HR     = 18,
    Blue_VU     = 19,
    Blue_V      = 20,
    Blue_VD     = 21,
    Blue_C      = 22,
    Blue_Start  = 23,

    Limit_H     = 24,
    Limit_V     = 25,
    Limit_C     = 26,

    Exit        = 30,

    Button_L    = 31,
  };

  struct PlatformData {
    PlatformType type;
    gf::SegmentI segment;
  };

  enum class CableType {
    None        = -1,
    Straight_HL = 32,
    Straight_H  = 33,
    Straight_HR = 34,
    Straight_VU = 35,
    Straight_V  = 36,
    Straight_VD = 37,
    Cross       = 38,

    Turn_LD     = 40,
    Turn_LU     = 41,
    Turn_RD     = 42,
    Turn_RU     = 43,
  };

  enum class LiftType {
    None    = -1,
    Lift_V  = 44,
    Lift_D  = 45,
    Lift_U  = 46,
  };

  struct LiftData {
    gf::SegmentI segment;
  };

  enum class ButtonType {
    Unknown,
    Platform,
    Lift,
  };

  struct ButtonData {
    ButtonType type = ButtonType::Unknown;
    gf::Vector2i position = gf::vec(-1, -1);
    std::size_t index = std::size_t(-1); // of platform or lift
  };

  struct LevelData {
    LevelData();

    gf::Array2D<PlatformType, int> platform_tiles;
    gf::Array2D<CableType, int> cable_tiles;
    gf::Array2D<LiftType, int> lift_tiles;

    std::vector<PlatformData> platforms;
    std::vector<LiftData> lifts;
    std::vector<ButtonData> buttons;

    std::vector<gf::SegmentI> limits;

    gf::Vector2i exit = gf::vec(-1, -1);

    gf::Vector2i hanz = gf::vec(-1, -1);
    gf::Vector2i gret = gf::vec(-1, -1);

    static LevelData makeFromTmx(const gf::TmxLayers& tmx);
  };

}



#endif // HG_LEVEL_DATA_H
