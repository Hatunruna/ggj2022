#ifndef HG_PHYSICS_MODEL_H
#define HG_PHYSICS_MODEL_H

#include <vector>

#include <gf/Direction.h>
#include <gf/Model.h>
#include <gf/Vector.h>

#include "Hero.h"

namespace hg {
  struct GameData;

  class PhysicsModel : public gf::Model {
  public:
    PhysicsModel();

    void loadLevel(const GameData& data, std::size_t number);

    bool jump(Hero hero);
    void setDirection(Hero hero, gf::Direction direction);
    void switchColor(std::size_t index);

    gf::Vector2f getPosition(Hero hero) const;
    gf::Vector2f getVelocity(Hero hero) const;
    bool isColliding(Hero hero) const;

    void update(gf::Time time) override;

  private:
    enum class BodyCollision {
      WithHanz,
      WithGret,
      WithBoth,
    };

    struct Body {
      gf::Vector2f position;
      gf::Vector2f velocity;
      gf::Vector2f size;
      BodyCollision collision;
    };


  private:
    bool applyJump(Body& body, float factor, bool colliding);
    void applyDirection(Body& body, float factor, gf::Direction direction);

    void applyGravity(Body& body, gf::Time time);
    void checkCollision(Body& body, bool& colliding);

  private:

    Body m_hanz;
    bool m_isHanzColliding;

    Body m_gret;
    bool m_isGretColliding;

    std::vector<Body> m_static;
  };

}

#endif // HG_PHYSICS_MODEL_H
