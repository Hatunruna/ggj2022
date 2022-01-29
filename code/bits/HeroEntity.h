#ifndef HG_HERO_ENTITY_H
#define HG_HERO_ENTITY_H

#include <gf/Animation.h>
#include <gf/Direction.h>
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

    void setDirection(gf::Direction direction);

    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    // State
    const HeroColor m_color;
    gf::Vector2f m_position;

    // Graphics
    gf::Texture& m_pauseTexture;
    gf::Texture& m_runTexture;
    gf::Animation m_runAnimation;

    // Actions
    gf::Direction m_facedDirection; // To handle pause position
    gf::Direction m_moveDirection;
  };
}

#endif // HG_HERO_ENTITY_H
