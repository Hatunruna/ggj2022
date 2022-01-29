#include "LeverEntity.h"

#include <gf/AnimatedSprite.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>

namespace hg {

  constexpr float TextureScale = 64.0f / 256.0f;

  LeverEntity::LeverEntity(gf::ResourceManager& resources, AudioManager& audio, gf::Vector2f position)
  : m_stillTexture(resources.getTexture("levier/levier.png"))
  , m_position(position)
  {
    m_stillTexture.setSmooth();
    m_activationAnimation.addTileset(m_stillTexture, gf::vec(6, 2), gf::seconds(1.0f / 25.0f), 12);
  }

  void LeverEntity::update(gf::Time time) {
      m_activationAnimation.update(time); // todo run animation once then stop
  }

  void LeverEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {

    auto drawAnimation = [this, &target, &states](gf::Animation animation) {
      gf::AnimatedSprite sprite;
      sprite.setAnimation(animation);
      sprite.setAnchor(gf::Anchor::Center);
      sprite.setPosition(m_position);
      sprite.setScale(TextureScale);
      target.draw(sprite, states);
    };
  }
}
