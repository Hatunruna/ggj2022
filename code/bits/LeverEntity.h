#ifndef HG_LEVER_ENTITY_H
#define HG_LEVER_ENTITY_H

#include <gf/Animation.h>
#include <gf/Direction.h>
#include <gf/Entity.h>
#include <gf/ResourceManager.h>

#include "AudioManager.h"
#include "Hero.h"

namespace hg {
  class PhysicsModel;

  class LeverEntity : public gf::Entity {
  public:
    LeverEntity(gf::ResourceManager& resources, AudioManager& audio, gf::Vector2f position);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    gf::Texture& m_stillTexture;
    gf::Animation m_activationAnimation;
    gf::Vector2f m_position;
  };
}

#endif // HG_LEVER_ENTITY_H
