#include "CreditEntity.h"

#include <gf/Coordinates.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

namespace hg {

  CreditEntity::CreditEntity(gf::ResourceManager& resources, AudioManager& audio)
  : m_font(resources.getFont("Underdog.otf"))
  , m_backgroundTexture(resources.getTexture("title.png"))
  {

  }

  void CreditEntity::update([[maybe_unused]] gf::Time time) {
  }

  void CreditEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
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
    unsigned subtitleCharacterSize = coords.getRelativeCharacterSize(0.07f);
    unsigned gitCharacterSize = coords.getRelativeCharacterSize(0.05f);

    gf::Text title("Credits", m_font, titleCharacterSize);
    title.setColor(gf::Color::White);
    title.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
    title.setAnchor(gf::Anchor::Center);
    target.draw(title, states);

    gf::Text git("", m_font, gitCharacterSize);
    git.setParagraphWidth(40.0f);
    git.setString("Github: https://github.com/Hatunruna/ggj2022");
    git.setColor(gf::Color::White);
    git.setPosition(coords.getRelativePoint({ 0.5f, 0.7f}));
    git.setAnchor(gf::Anchor::Center);

    gf::Text developper("", m_font, subtitleCharacterSize);
    developper.setParagraphWidth(20.0f);
    developper.setAlignment(gf::Alignment::Justify);
    developper.setString("Developper:"
                         " Ahugeat "
                         " Jube"
                         " Magestik "
                         " Mcvitiz "
                         " NiiRoZz ");
    developper.setColor(gf::Color::White);
    developper.setPosition(coords.getRelativePoint({ 0.1f, 0.4f}));
    developper.setAnchor(gf::Anchor::Center);

    gf::Text sound("", m_font, subtitleCharacterSize);
    sound.setParagraphWidth(20.0f);
    sound.setAlignment(gf::Alignment::Justify);
    sound.setString("Sound:"
                         " Antho ");
    sound.setColor(gf::Color::White);
    sound.setPosition(coords.getRelativePoint({ 0.4f, 0.4f}));
    sound.setAnchor(gf::Anchor::Center);


    gf::Text art("", m_font, subtitleCharacterSize);
    art.setParagraphWidth(20.0f);
    art.setAlignment(gf::Alignment::Justify);
    art.setString("Art:"
                         " Bovinbleu ");
    art.setColor(gf::Color::White);
    art.setPosition(coords.getRelativePoint({ 0.7f, 0.4f}));
    art.setAnchor(gf::Anchor::Center);

    target.draw(developper, states);
    target.draw(sound, states);
    target.draw(art, states);
    target.draw(git, states);
  }

}
