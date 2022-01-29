#include "HeroEntity.h"

#include <gf/AnimatedSprite.h>
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
  , m_position(position)
  , m_pauseTexture(getHeroTexture(resources, "pause.png", color))
  , m_runTexture(getHeroTexture(resources, "run.png", color))
  , m_facedDirection(gf::Direction::Left)
  , m_moveDirection(gf::Direction::Center)
  {
    // Load animation
    m_runAnimation.addTileset(m_runTexture, gf::vec(4, 3), gf::seconds(1.0f / 25.0f), 12);
  }

  void HeroEntity::setDirection(gf::Direction direction) {
    m_moveDirection = direction;

    if (direction == gf::Direction::Left || direction == gf::Direction::Right) {
      m_facedDirection = direction;
    } else if (direction == gf::Direction::Center) {
      m_runAnimation.reset();
    }
  }

  void HeroEntity::update(gf::Time time) {
    if (m_moveDirection == gf::Direction::Left || m_moveDirection == gf::Direction::Right) {
      m_runAnimation.update(time);
    }
  }

  void HeroEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    auto drawAnimation = [this, &target, &states](gf::Animation animation, bool invert = false) {
      gf::AnimatedSprite sprite;
      sprite.setAnimation(animation);
      sprite.setAnchor(gf::Anchor::Center);
      sprite.setPosition(m_position);
      if (invert) {
        sprite.setScale(gf::vec(-1.0f, 1.0f));
      }
      target.draw(sprite, states);
    };

    switch (m_moveDirection) {
    case gf::Direction::Center: {
      gf::Sprite sprite;
      sprite.setTexture(m_pauseTexture);
      sprite.setAnchor(gf::Anchor::Center);
      sprite.setPosition(m_position);
      if (m_facedDirection == gf::Direction::Right) {
        sprite.setScale(gf::vec(-1.0f, 1.0f));
      }
      target.draw(sprite, states);
      break;
    }

    case gf::Direction::Left:
      drawAnimation(m_runAnimation);
      break;

    case gf::Direction::Right:
      drawAnimation(m_runAnimation, true);
      break;

    default:
      assert(false);
    }

  }
}
