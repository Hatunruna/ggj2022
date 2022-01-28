#include "AudioManager.h"

namespace hg {

  namespace {

    template<typename T>
    class ResourceLoader {
    public:
      std::unique_ptr<T> operator()(const gf::Path& filename) {
        auto ptr = std::make_unique<T>();

        if (!ptr->openFromFile(filename.string())) {
          throw std::runtime_error("'" + filename.string() + "' file not found");
        }

        return ptr;
      }
    };

    template<>
    class ResourceLoader<sf::SoundBuffer> {
    public:
      std::unique_ptr<sf::SoundBuffer> operator()(const gf::Path& filename) {
        auto ptr = std::make_unique<sf::SoundBuffer>();

        if (!ptr->loadFromFile(filename.string())) {
          throw std::runtime_error("'" + filename.string() + "' file not found");
        }

        return ptr;
      }
    };


  }

  AudioManager::AudioManager()
  : m_musics(ResourceLoader<sf::Music>())
  , m_sounds(ResourceLoader<sf::SoundBuffer>())
  {

  }

  AudioManager::AudioManager(std::initializer_list<gf::Path> paths)
  : AudioManager()
  {
    for (const auto& path : paths) {
      addSearchDir(path);
    }
  }

}
