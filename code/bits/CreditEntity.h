#ifndef HG_CREDIT_ENTITY_H
#define HG_CREDIT_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

#include "AudioManager.h"

namespace hg {

  class CreditEntity : public gf::Entity {
  public:
      CreditEntity(gf::ResourceManager& resources, AudioManager& audio);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;
  private:
    gf::Font& m_font;
    gf::Texture& m_backgroundTexture;
  };


}


#endif // HG_CREDIT_ENTITY_H
