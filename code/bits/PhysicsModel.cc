#include "PhysicsModel.h"

#include <cassert>

#include <gf/Collision.h>
#include <gf/Log.h>

#include "Constants.h"
#include "GameData.h"

namespace hg {

  PhysicsModel::PhysicsModel() = default;

  void PhysicsModel::loadLevel(const GameData& data, std::size_t number) {
    m_static.clear();

    assert(number < data.levels.size());
    const LevelData & level = data.levels[number];

    for (auto & platform : level.platforms) {
      gf::RectF rect = gf::RectF::fromMinMax(platform.segment.p0 * TileSize, (platform.segment.p1 + 1) * TileSize);

      rect.min.x += TileSize.width * 1.25f;
      rect.max.x -= TileSize.width * 1.25f;
      rect.max.y -= TileSize.width * 0.5f;

      Body body;
      body.position = rect.getCenter();
      body.size = rect.getSize();
      body.velocity = gf::vec(0.0f, 0.0f);

      switch (platform.type) {
        case PlatformType::Neutral_H:
        case PlatformType::Neutral_V:
          body.collision = BodyCollision::WithBoth;
          break;
        case PlatformType::Red_H:
        case PlatformType::Red_V:
          body.collision = BodyCollision::WithHanz;
          break;
        case PlatformType::Blue_H:
        case PlatformType::Blue_V:
          body.collision = BodyCollision::WithGret;
          break;
        default:
          gf::Log::debug("Type: %i\n", (int) platform.type);
          assert(false);
          break;
      }

      m_static.push_back(body);
    }

    for (auto & limit : level.limits) {
      gf::RectF rect = gf::RectF::fromMinMax(limit.p0 * TileSize, (limit.p1 + 1) * TileSize);

      Body body;
      body.position = rect.getCenter();
      body.size = rect.getSize();
      body.velocity = gf::vec(0.0f, 0.0f);
      body.collision = BodyCollision::WithBoth;

      m_static.push_back(body);
    }

    gf::Log::debug("Static bodies: %zu\n", m_static.size());

    m_hanz.position = level.hanz * TileSize + TileSize / 2;
    m_hanz.velocity = gf::vec(0.0f, 0.0f);
    m_hanz.size = 2 * TileSize;
    m_hanz.collision = BodyCollision::WithHanz;

    m_gret.position = level.gret * TileSize + TileSize / 2;
    m_gret.velocity = gf::vec(0.0f, 0.0f);
    m_gret.size = 2 * TileSize;
    m_gret.collision = BodyCollision::WithGret;
  }

  bool PhysicsModel::jump(Hero hero) {
    switch (hero) {
      case Hero::Hanz:
        return applyJump(m_hanz, 1.25f, m_isHanzColliding);
      case Hero::Gret:
        return applyJump(m_gret, 1.0f, m_isGretColliding);
    }

    assert(false);
    return false;
  }

  void PhysicsModel::setDirection(Hero hero, gf::Direction direction) {
    switch (hero) {
      case Hero::Hanz:
        applyDirection(m_hanz, 1.0f, direction);
        break;
      case Hero::Gret:
        applyDirection(m_gret, 1.5f, direction);
        break;
    }
  }

  void PhysicsModel::switchPlatform(std::size_t index) {
    assert(index < m_static.size());
    auto & body = m_static[index];

    switch (body.collision) {
      case BodyCollision::WithHanz:
        body.collision = BodyCollision::WithGret;
        break;
      case BodyCollision::WithGret:
        body.collision = BodyCollision::WithHanz;
        break;
      case BodyCollision::WithBoth:
        assert(false);
        break;
    }
  }

  gf::Vector2f PhysicsModel::getPosition(Hero hero) const {
    switch (hero) {
      case Hero::Hanz:
        return m_hanz.position;
      case Hero::Gret:
        return m_gret.position;
    }

    assert(false);
    return gf::vec(0.0f, 0.0f);
  }

  gf::Vector2f PhysicsModel::getVelocity(Hero hero) const {
    switch (hero) {
      case Hero::Hanz:
        return m_hanz.velocity;
      case Hero::Gret:
        return m_gret.velocity;
    }

    assert(false);
    return gf::vec(0.0f, 0.0f);
  }

  bool PhysicsModel::isColliding(Hero hero) const {
    switch (hero) {
      case Hero::Hanz:
        return m_isHanzColliding;
      case Hero::Gret:
        return m_isGretColliding;
    }

    assert(false);
    return true;
  }

  void PhysicsModel::update(gf::Time time) {
    applyGravity(m_hanz, time);
    applyGravity(m_gret, time);
    checkCollision(m_hanz, m_isHanzColliding);
    checkCollision(m_gret, m_isGretColliding);
  }

  bool PhysicsModel::applyJump(Body& body, float factor, bool colliding) {
    if (colliding && std::abs(body.velocity.y) < gf::Epsilon) {
      body.velocity += JumpImpulse * factor;
      return true;
    }

    return false;
  }

  void PhysicsModel::applyDirection(Body& body, float factor, gf::Direction direction) {
    switch (direction) {
      case gf::Direction::Left:
        body.velocity.x = -RunVelocity * factor;
        break;
      case gf::Direction::Right:
        body.velocity.x = +RunVelocity * factor;
        break;
      case gf::Direction::Center:
        body.velocity.x = 0.0f;
        break;
      default:
        assert(false);
        break;
    }
  }

  void PhysicsModel::applyGravity(Body& body, gf::Time time) {
    body.velocity += Gravity * time.asSeconds();
    body.position += body.velocity * time.asSeconds();
  }

  void PhysicsModel::checkCollision(Body& body, bool& colliding) {
    gf::RectF bounds = gf::RectF::fromCenterSize(body.position, body.size);
    colliding = false;

    for (auto & other : m_static) {
      if (other.collision != body.collision && other.collision != BodyCollision::WithBoth) {
        continue;
      }

      gf::Penetration penetration;
      gf::RectF otherBounds = gf::RectF::fromCenterSize(other.position, other.size);

      if (gf::collides(otherBounds, bounds, penetration)) {
        colliding = true;
        body.position += penetration.depth * penetration.normal * 0.4f;
        body.velocity -= gf::dot(body.velocity, penetration.normal) * penetration.normal;
      }
    }
  }

}
