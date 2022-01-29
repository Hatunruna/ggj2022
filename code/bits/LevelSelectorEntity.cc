#include "LevelSelectorEntity.h"

#include "GameHub.h"

#include <gf/Coordinates.h>
#include <gf/Shapes.h>
#include <gf/Text.h>
#include <gf/Log.h>
#include <gf/Vector.h>

namespace hg
{
    LevelSelectorEntity::LevelSelectorEntity(gf::ResourceManager& resources, GameHub& game, gf::Vector2f position, std::string string)
    : m_game(game)
    , m_position(position)
    , m_string(string)
    , m_font(resources.getFont("Underdog.otf"))
    {
    }

    void LevelSelectorEntity::render(gf::RenderTarget& target, const gf::RenderStates& states)
    {
      gf::Coordinates coordinates(target);
      gf::CircleShape level;

      level.setColor(gf::Color::White);
      level.setAnchor(gf::Anchor::Center);
      level.setRadius(coordinates.getRelativeSize({0.05f, 0.f}).x);
      level.setPosition(coordinates.getRelativePoint(m_position));

      button(m_string,m_font,coordinates.getRelativeSize({0.05f, 0.f}).x);
      level.draw(button,states);
      level.draw(target, states);
    }
}