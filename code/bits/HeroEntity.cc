#include "HeroEntity.h"

#include <gf/AnimatedSprite.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>

#include "PhysicsModel.h"

namespace hg {

  namespace {
    constexpr float TextureScale = 64.0f / 256.0f;

    gf::Texture& getHeroTexture(gf::ResourceManager& resources, const std::string& textureName, Hero hero) {
      std::string dir;
      switch(hero) {
      case Hero::Hanz:
        dir = "hanz/";
        break;

      case Hero::Gret:
        dir = "gret/";
        break;
      }

      return resources.getTexture(dir + textureName);
    }
  }


  HeroEntity::HeroEntity(gf::ResourceManager& resources, PhysicsModel& physics, AudioManager& audio, Hero hero)
  : m_physics(physics)
  , m_hero(hero)
  , m_state(HeroState::Pause)
  , m_pauseTexture(getHeroTexture(resources, "pause.png", hero))
  , m_runTexture(getHeroTexture(resources, "run.png", hero))
  , m_facedDirection(gf::Direction::Left)
  , m_moveDirection(gf::Direction::Center)
  {
    // Smoothing textures
    m_pauseTexture.setSmooth();
    m_runTexture.setSmooth();

    // Load animation
    m_runAnimation.addTileset(m_runTexture, gf::vec(4, 3), gf::seconds(1.0f / 25.0f), 12);
  }

  void HeroEntity::setDirection(gf::Direction direction) {
    switch(m_state) {
    case HeroState::Pause:
      if (direction == gf::Direction::Left || direction == gf::Direction::Right) {
        m_moveDirection = direction;
        m_facedDirection = direction;

        m_state = HeroState::Run;
      }
      // TODO: handle jump
      // TODO: activate

      break;

    case HeroState::Run:
      if (direction == gf::Direction::Left || direction == gf::Direction::Right) {
        m_moveDirection = direction;
        m_facedDirection = direction;
      } else if (direction == gf::Direction::Center) {
        m_moveDirection = direction;

        m_state = HeroState::Pause;
        m_runAnimation.reset();
      }
      // TODO: handle jump
      // TODO: handle fall
      // TODO: activate

      break;

    default:
      // TODO: jump
      // TODO: fall
      // TODO: land
      // TODO: activate
      assert(false);
      break;
    }

    m_physics.setDirection(m_hero, direction);
  }

  void HeroEntity::jump() {
    m_physics.jump(m_hero);
  }

  void HeroEntity::update(gf::Time time) {
    if (m_moveDirection == gf::Direction::Left || m_moveDirection == gf::Direction::Right) {
      m_runAnimation.update(time);
    }
  }

  void HeroEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    auto drawAnimation = [this, &target, &states](gf::Animation& animation, bool inverted = false) {
      gf::AnimatedSprite sprite;
      sprite.setAnimation(animation);
      sprite.setAnchor(gf::Anchor::Center);
      sprite.setPosition(m_physics.getPosition(m_hero));
      if (inverted) {
        sprite.setScale(gf::vec(-TextureScale, TextureScale));
      } else {
        sprite.setScale(TextureScale);
      }
      target.draw(sprite, states);
    };

    auto drawSprite = [this, &target, &states](gf::Texture& texture, bool inverted = false) {
      gf::Sprite sprite;
      sprite.setTexture(texture);
      sprite.setAnchor(gf::Anchor::Center);
      sprite.setPosition(m_physics.getPosition(m_hero));
      if (m_facedDirection == gf::Direction::Right) {
        sprite.setScale(gf::vec(-TextureScale, TextureScale));
      } else {
        sprite.setScale(TextureScale);
      }
      target.draw(sprite, states);
    };

    switch (m_state) {
    case HeroState::Pause:
      drawSprite(m_pauseTexture, m_facedDirection == gf::Direction::Right);
      break;

    case HeroState::Run:
      drawAnimation(m_runAnimation, m_facedDirection == gf::Direction::Right);
      break;

    default:
      assert(false);
      break;
    }
  }
}
