#include <gf/Color.h>
#include <gf/Image.h>

constexpr int Size = 32;
constexpr int Mid = 16;
constexpr int Lo = 8;
constexpr int Hi = 24;

int main() {
  gf::Image base(gf::vec(Size, Size), gf::Color::toRgba32(gf::Color::Transparent));

  {
    gf::Image image = base;

    for (int i = 0; i < Size; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::White));
      }
    }

    image.saveToFile("00-platform_H.png");
  }

  {
    gf::Image image = base;

    for (int i = 0; i < Mid; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::White));
      }
    }

    image.saveToFile("01-platform_HR.png");
  }

  {
    gf::Image image = base;

    for (int i = Mid; i < Size; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::White));
      }
    }

    image.saveToFile("02-platform_HL.png");
  }

  {
    gf::Image image = base;

    for (int i = Lo; i < Hi; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::White));
      }
    }

    image.saveToFile("03-platform_V.png");
  }

  {
    gf::Image image = base;

    for (int i = Lo; i < Hi; ++i) {
      for (int j = 0; j < Mid; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::White));
      }
    }

    image.saveToFile("04-platform_VD.png");
  }

  {
    gf::Image image = base;

    for (int i = Lo; i < Hi; ++i) {
      for (int j = Mid; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::White));
      }
    }

    image.saveToFile("05-platform_VU.png");
  }


  {
    gf::Image image = base;

    for (int i = Lo; i < Hi; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::Gray()));
      }
    }

    image.saveToFile("06-limit_V.png");
  }

  {
    gf::Image image = base;

    for (int i = 0; i < Size; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::Gray()));
      }
    }

    image.saveToFile("07-limit_H.png");
  }

  {
    gf::Image image = base;

    for (int i = Lo; i < Hi; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::Gray()));
      }
    }

    for (int i = 0; i < Size; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(gf::Color::Gray()));
      }
    }

    image.saveToFile("08-limit_C.png"); // cross
  }


}
