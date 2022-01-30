#include "MenuTitleEntity.h"

#include <gf/Coordinates.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

namespace hg {

    MenuTitleEntity::MenuTitleEntity(gf::ResourceManager& resources, AudioManager& audio)
  : m_font(resources.getFont("Underdog.otf"))
  , m_backgroundTexture(resources.getTexture("title.png"))
  {

  }

  void MenuTitleEntity::update([[maybe_unused]] gf::Time time) {
  }

  void MenuTitleEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    gf::Coordinates coords(target);

    float backgroundHeight = coords.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
    float backgroundScale = backgroundHeight / m_backgroundTexture.getSize().height;

    gf::Sprite background(m_backgroundTexture);
    background.setColor(gf::Color::Opaque(0.20f));
    background.setPosition(coords.getCenter());
    background.setAnchor(gf::Anchor::Center);
    background.setScale(backgroundScale);
    target.draw(background, states);

    unsigned titleCharacterSize = coords.getRelativeCharacterSize(0.1f);

    gf::Text title("Main menu", m_font, titleCharacterSize);
    title.setColor(gf::Color::White);
    title.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
    title.setAnchor(gf::Anchor::TopCenter);
    target.draw(title, states);

    unsigned subtitleCharacterSize = coords.getRelativeCharacterSize(0.05f);

    gf::Text subtitle("Select level", m_font, subtitleCharacterSize);
    subtitle.setColor(gf::Color::White);
    subtitle.setPosition(coords.getRelativePoint({ 0.5f, 0.2f }));
    subtitle.setAnchor(gf::Anchor::Center);
    target.draw(subtitle, states);
  }

}
