#ifndef HG_AUDIO_MANAGER_H
#define HG_AUDIO_MANAGER_H

#include <mutex>

#include <gf/AssetManager.h>
#include <gf/ResourceManager.h>

#include <SFML/Audio.hpp>

namespace hg {

  class AudioManager : public gf::AssetManager {
  public:
    AudioManager();
    AudioManager(std::initializer_list<gf::Path> paths);

    sf::Music& getMusic(const gf::Path& path) {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_musics.getResource(*this, path);
    }

    sf::SoundBuffer& getSound(const gf::Path& path) {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_sounds.getResource(*this, path);
    }

  private:
    gf::ResourceCache<sf::Music> m_musics;
    gf::ResourceCache<sf::SoundBuffer> m_sounds;
    std::mutex m_mutex;
  };


}


#endif // HG_GAME_HUB_H
