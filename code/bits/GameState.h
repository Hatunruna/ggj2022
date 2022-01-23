#ifndef XY_GAME_STATE_H
#define XY_GAME_STATE_H

#include <cstdint>

#include <gf/Path.h>

namespace xy {

  struct GameState {
    static constexpr uint16_t Version = 1;

    void loadFromFile(const gf::Path& filename);
    void saveToFile(const gf::Path& filename);
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, GameState& state) {
    return ar;
  }

}


#endif // XY_GAME_STATE_H
