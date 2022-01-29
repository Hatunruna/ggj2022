#ifndef HG_GAME_STATE_H
#define HG_GAME_STATE_H

#include <cstdint>

#include <gf/Path.h>

namespace hg {

  struct GameState {
    static constexpr uint16_t Version = 1;

    std::size_t level = 0;

    void loadFromFile(const gf::Path& filename);
    void saveToFile(const gf::Path& filename);
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, GameState& state) {
    return ar;
  }

}


#endif // HG_GAME_STATE_H
