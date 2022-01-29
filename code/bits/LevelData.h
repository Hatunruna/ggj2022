#ifndef HG_LEVEL_DATA_H
#define HG_LEVEL_DATA_H

#include <vector>

#include <gf/Array2D.h>
#include <gf/GeometryTypes.h>
#include <gf/Tmx.h>

namespace hg {
  enum class PlatformData {
    None        = -1,

    Neutral_HL  = 0,
    Neutral_H   = 1,
    Neutral_HR  = 2,
    Neutral_VU  = 3,
    Neutral_V   = 4,
    Neutral_VD  = 5,
    Neutral_C   = 6,

    Button      = 7,

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
  };

  struct LevelData {
    LevelData();

    gf::Array2D<PlatformData, int> tiles;
    std::vector<gf::SegmentI> platforms;

    static LevelData makeFromTmx(const gf::TmxLayers& tmx);
  };

}



#endif // HG_LEVEL_DATA_H
