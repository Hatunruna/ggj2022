#ifndef HG_HERO_ENTITY_H
#define HG_HERO_ENTITY_H

#include <gf/Animation.h>
#include <gf/Direction.h>
#include <gf/Entity.h>
#include <gf/ResourceManager.h>

#include "AudioManager.h"
#include "Hero.h"

namespace hg {
  class PhysicsModel;

  class HeroEntity : public gf::Entity {
  public:
    HeroEntity(gf::ResourceManager& resources, PhysicsModel& physics, AudioManager& audio, Hero hero);

    void setDirection(gf::Direction direction);
    void jump();

    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    PhysicsModel& m_physics;

    // State
    Hero m_hero;

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
