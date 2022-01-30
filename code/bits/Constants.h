#ifndef HG_CONSTANTS_H
#define HG_CONSTANTS_H

#include <gf/Vector.h>

namespace hg {

  constexpr gf::Vector2f TileSize = gf::vec(32.0f, 32.0f);
  constexpr gf::Vector2i LevelSize = gf::vec(32, 32);

  constexpr gf::Vector2f Gravity = gf::vec(0.0f, 1000.0f);
  constexpr gf::Vector2f JumpImpulse = gf::vec(0.0f, -500.f);
  constexpr float RunVelocity = 300.0f;

  constexpr float ButtonDistance = 48.0f;

}

#endif // HG_CONSTANTS_H
