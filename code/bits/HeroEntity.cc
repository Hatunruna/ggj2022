#include "HeroEntity.h"

#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>

namespace hg {

  namespace {
    const gf::Texture& getHeroTexture(gf::ResourceManager& resources, const std::string& textureName, HeroColor color) {
      std::string dir;
      switch(color) {
      case HeroColor::Red:
        dir = "hanz/";
        break;

      case HeroColor::Blue:
        dir = "gret/";
        break;
      }

      return resources.getTexture(dir + textureName);
    }
  }


  HeroEntity::HeroEntity(gf::ResourceManager& resources, AudioManager& audio, HeroColor color, gf::Vector2f position)
  : m_color(color)
  , m_postion(position)
  , m_pauseTexture(getHeroTexture(resources, "pause.png", color))
  {
    gf::Log::debug("pos: %dx%d\n", position.x, position.y);
  }

  void HeroEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    gf::Sprite sprite;
    sprite.setTexture(m_pauseTexture);
    sprite.setAnchor(gf::Anchor::Center);
    sprite.setPosition(m_postion);
    target.draw(sprite, states);
  }
}
