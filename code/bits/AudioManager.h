#ifndef XY_AUDIO_MANAGER_H
#define XY_AUDIO_MANAGER_H

#include <mutex>

#include <gf/AssetManager.h>
#include <gf/ResourceManager.h>

#include <SFML/Audio.hpp>

namespace xy {

  class AudioManager : public gf::AssetManager {
  public:
    AudioManager();
    AudioManager(std::initializer_list<gf::Path> paths);

    sf::Music& getMusic(const gf::Path& path) {
      std::lock_guard<std::mutex> lock(m_mutex);
      auto& music = m_musics.getResource(*this, path);
      return music;
    }

    sf::Sound getSound(const gf::Path& path) {
      std::lock_guard<std::mutex> lock(m_mutex);
      auto& buffer = m_sounds.getResource(*this, path);
      return sf::Sound(buffer);
    }

  private:
    gf::ResourceCache<sf::Music> m_musics;
    gf::ResourceCache<sf::SoundBuffer> m_sounds;
    std::mutex m_mutex;
  };


}


#endif // XY_GAME_HUB_H
