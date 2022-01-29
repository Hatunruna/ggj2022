#ifndef HG_LEVEL_SCENERY_H
#define HG_LEVEL_SCENERY_H

#include <vector>

#include <gf/ResourceManager.h>
#include <gf/TileLayer.h>
#include <gf/Tmx.h>

namespace hg {

  struct LevelScenery {
    std::vector<gf::TileLayer> layers;

    static LevelScenery makeFromTmx(gf::ResourceManager& resources, const gf::TmxLayers& tmx);
  };

}

#endif // HG_LEVEL_SCENERY_H
