#ifndef HG_MENU_TITLE_ENTITY_H
#define HG_MENU_TITLE_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

#include "AudioManager.h"

namespace hg {

  class MenuTitleEntity : public gf::Entity {
  public:
      MenuTitleEntity(gf::ResourceManager& resources, AudioManager& audio);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;
  private:
    gf::Font& m_font;
    gf::Texture& m_backgroundTexture;
  };


}


#endif // HG_MENU_TITLE_ENTITY_H
