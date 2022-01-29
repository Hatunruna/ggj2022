#ifndef HG_HERO_ENTITY_H
#define HG_HERO_ENTITY_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>

#include "AudioManager.h"

namespace hg {
  enum class HeroColor {
    Blue,
    Red,
  };

  class HeroEntity : public gf::Entity {
  public:
    HeroEntity(gf::ResourceManager& resources, AudioManager& audio, HeroColor color, gf::Vector2f position);

    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    const HeroColor m_color;
    gf::Vector2f m_postion;
    const gf::Texture& m_pauseTexture;
  };
}

#endif // HG_HERO_ENTITY_H
