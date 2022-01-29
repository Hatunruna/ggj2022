#include "MenuTitleEntity.h"

#include <gf/Coordinates.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

namespace hg {

    MenuTitleEntity::MenuTitleEntity(gf::ResourceManager& resources, AudioManager& audio)
  : m_font(resources.getFont("Underdog.otf"))
//   , m_backgroundTexture(resources.getTexture("logo.png"))
  {

  }

  void MenuTitleEntity::update([[maybe_unused]] gf::Time time) {
  }

  void MenuTitleEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    gf::Coordinates coords(target);
    unsigned titleCharacterSize = coords.getRelativeCharacterSize(0.1f);

    gf::Text title("Main menu", m_font, titleCharacterSize);
    title.setColor(gf::Color::White);
    title.setPosition(coords.getRelativePoint({ 0.5f, 0.0f }));
    title.setAnchor(gf::Anchor::TopCenter);
    target.draw(title, states);

    unsigned subtitleCharacterSize = coords.getRelativeCharacterSize(0.05f);

    gf::Text subtitle("Select level", m_font, subtitleCharacterSize);
    subtitle.setColor(gf::Color::White);
    subtitle.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
    subtitle.setAnchor(gf::Anchor::Center);
    target.draw(subtitle, states);
  }

}
