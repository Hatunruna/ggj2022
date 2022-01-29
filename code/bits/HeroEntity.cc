#include "HeroEntity.h"

#include <gf/AnimatedSprite.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>

#include "PhysicsModel.h"

namespace hg {

  namespace {
    constexpr float TextureScale = 64.0f / 256.0f;
    constexpr float JumpTextureOffset = 32.0f;
    constexpr int LandAnimationFrameCount = 4;
    constexpr gf::Time LandTotalTimeAnimaion = gf::seconds(LandAnimationFrameCount * (1.0f / 25.0f));

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
  , m_jumpTexture(getHeroTexture(resources, "jump.png", hero))
  , m_fallTexture(getHeroTexture(resources, "fall.png", hero))
  , m_landTexture(getHeroTexture(resources, "land.png", hero))
  , m_facedDirection(gf::Direction::Left)
  , m_moveDirection(gf::Direction::Center)
  {
    // Smoothing textures
    m_pauseTexture.setSmooth();
    m_runTexture.setSmooth();
    m_jumpTexture.setSmooth();
    m_fallTexture.setSmooth();

    // Load animation
    m_runAnimation.addTileset(m_runTexture, gf::vec(4, 3), gf::seconds(1.0f / 25.0f), 12);
    m_jumpAnimation.addTileset(m_jumpTexture, gf::vec(3, 3), gf::seconds(1.0f / 25.0f), 7);
    m_jumpAnimation.setLoop(false);
    m_fallAnimation.addTileset(m_fallTexture, gf::vec(3, 3), gf::seconds(1.0f / 25.0f), 6);
    m_fallAnimation.setLoop(false);
    m_landAnimation.addTileset(m_landTexture, gf::vec(3, 3), gf::seconds(1.0f / 25.0f), LandAnimationFrameCount);
    m_landAnimation.setLoop(false);
  }

  void HeroEntity::setDirection(gf::Direction direction) {
    switch(m_state) {
    case HeroState::Pause:
      if (direction == gf::Direction::Left || direction == gf::Direction::Right) {
        m_moveDirection = direction;
        m_facedDirection = direction;

        m_state = HeroState::Run;
      }
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
      // TODO: handle fall
      // TODO: activate

      break;

    case HeroState::Jump:
    case HeroState::Fall:
    {
        gf::Vector2f heroVelocity = m_physics.getVelocity(m_hero);
        if (heroVelocity.x > 0.0) {
          m_facedDirection = gf::Direction::Right;
        } else if (heroVelocity.x < 0.0f) {
          m_facedDirection = gf::Direction::Left;
        }
      }
      break;

    case HeroState::Land:
      // nothing
      break;

    default:
      // TODO: activate
      assert(false);
      break;
    }

    m_physics.setDirection(m_hero, direction);
  }

  void HeroEntity::jump() {
    gf::Log::debug("jump try\n");
    if (m_state == HeroState::Pause || m_state == HeroState::Run) {
      gf::Log::debug("jump state OK\n");
      if (m_physics.jump(m_hero)) {
        gf::Log::debug("jump triggered\n");
        m_jumpAnimation.reset();
        m_state = HeroState::Jump;
      }
    }
  }

  void HeroEntity::update(gf::Time time) {
    auto heroVelocity = m_physics.getVelocity(m_hero);

    switch (m_state) {
    case HeroState::Pause:
      // Nothing
      break;

    case HeroState::Run:
      m_runAnimation.update(time);
      break;

    case HeroState::Jump:
      if (heroVelocity.y > 0.0f) {
        m_fallAnimation.reset();
        m_state = HeroState::Fall;
      } else {
        m_jumpAnimation.update(time);
      }

      break;

    case HeroState::Fall:
      if (heroVelocity.y <= 0.0f) {
        m_state = HeroState::Land;
        m_elapsedTime = gf::seconds(0.0f);
      }
      break;

    case HeroState::Land:
      m_elapsedTime += time;
      m_landAnimation.update(time);

      if (m_elapsedTime > LandTotalTimeAnimaion) {
        m_state = HeroState::Pause;
      }
      break;

    default:
      assert(false);
      break;
    }
  }

  void HeroEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    auto drawAnimation = [this, &target, &states](gf::Vector2f pos, gf::Animation& animation, bool inverted = false) {
      gf::AnimatedSprite sprite;
      sprite.setAnimation(animation);
      sprite.setAnchor(gf::Anchor::Center);
      sprite.setPosition(pos);
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
      drawAnimation(m_physics.getPosition(m_hero), m_runAnimation, m_facedDirection == gf::Direction::Right);
      break;

    case HeroState::Jump:
      drawAnimation(m_physics.getPosition(m_hero) - gf::vec(0.0f, JumpTextureOffset), m_jumpAnimation, m_facedDirection == gf::Direction::Right);
      break;

    case HeroState::Fall:
      drawAnimation(m_physics.getPosition(m_hero) - gf::vec(0.0f, JumpTextureOffset), m_fallAnimation, m_facedDirection == gf::Direction::Right);
      break;

    case HeroState::Land:
      drawAnimation(m_physics.getPosition(m_hero) - gf::vec(0.0f, JumpTextureOffset), m_landAnimation, m_facedDirection == gf::Direction::Right);
      break;

    default:
      assert(false);
      break;
    }
  }
}
