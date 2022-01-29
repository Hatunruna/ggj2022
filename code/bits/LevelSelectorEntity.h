#ifndef HG_LEVEL_SELECTOR_ENTITY_H
#define HG_LEVEL_SELECTOR_ENTITY_H

#include <gf/Entity.h>
#include <gf/Coordinates.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>
#include <gf/Widgets.h>
#include <string>

namespace hg
{
  class GameHub;

  class LevelSelectorEntity: public gf::Entity
  {
  public:
    LevelSelectorEntity(gf::ResourceManager& resources, GameHub& game, gf::Vector2f position, std::string string);
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    GameHub& m_game;
    gf::Font& m_font;

    gf::Vector2f m_position;
    std::string m_string;

    gf::TextButtonWidget button;
  };
}
#endif // HG_LEVEL_SELECTOR_ENTITY_H