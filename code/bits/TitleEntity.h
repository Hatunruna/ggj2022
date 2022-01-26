#ifndef XY_TITLE_ENTITY_H
#define XY_TITLE_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

#include "AudioManager.h"

namespace xy {

  class TitleEntity : public gf::Entity {
  public:
    TitleEntity(gf::ResourceManager& resources, AudioManager& audio);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;
  private:
    gf::Font& m_font;
//     gf::Texture& m_backgroundTexture;

    sf::Music& m_music;
  };


}


#endif // XY_TITLE_ENTITY_H
