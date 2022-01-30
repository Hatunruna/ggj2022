#ifndef HG_BUTTONS_ENTITY_H
#define HG_BUTTONS_ENTITY_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>

#include "Hero.h"

namespace hg {

  struct GameData;
  struct GameState;
  class PhysicsModel;

  class ButtonsEntity : public gf::Entity {
  public:
    ButtonsEntity(gf::ResourceManager& resources, const GameData& data, GameState& state, PhysicsModel& physics);

    void activate(Hero hero);

    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    const GameData& m_data;
    GameState& m_state;
    PhysicsModel& m_physics;
  };

}

#endif // HG_BUTTONS_ENTITY_H
