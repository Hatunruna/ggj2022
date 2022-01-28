#include <gf/Color.h>
#include <gf/Image.h>

constexpr int Size = 34;
constexpr int Mid = 17;
constexpr int Lo = 9;
constexpr int Hi = 25;

namespace {

  gf::Image makeBase() {
    return gf::Image(gf::vec(Size, Size), gf::Color::toRgba32(gf::Color::Transparent));
  }

  void makeHorizontal(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = 0; i < Size; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeHorizontalRight(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = 0; i < Mid; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeHorizontalLeft(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid; i < Size; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeVertical(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Lo; i < Hi; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeVerticalDown(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Lo; i < Hi; ++i) {
      for (int j = 0; j < Mid; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeVerticalUp(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Lo; i < Hi; ++i) {
      for (int j = Mid; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCross(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Lo; i < Hi; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    for (int i = 0; i < Size; ++i) {
      for (int j = Lo; j < Hi; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path); // cross
  }

}


int main() {
  gf::Image base = makeBase();

  // neutral

  makeHorizontalLeft(gf::Color::White, "00-platform_neutral_HL.png");
  makeHorizontal(gf::Color::White, "01-platform_neutral_H.png");
  makeHorizontalRight(gf::Color::White, "02-platform_neutral_HR.png");

  makeVerticalUp(gf::Color::White, "03-plateform_neutral_VU.png");
  makeVertical(gf::Color::White, "04-platform_neutral_V.png");
  makeVerticalDown(gf::Color::White, "05-plateform_neutral_VD.png");

  makeCross(gf::Color::White, "06-platform_neutral_C.png");

  base.saveToFile("07-empty.png");

  // red

  makeHorizontalLeft(gf::Color::Red, "08-platform_red_HL.png");
  makeHorizontal(gf::Color::Red, "09-platform_red_H.png");
  makeHorizontalRight(gf::Color::Red, "10-platform_red_HR.png");

  makeVerticalUp(gf::Color::Red, "11-plateform_red_VU.png");
  makeVertical(gf::Color::Red, "12-platform_red_V.png");
  makeVerticalDown(gf::Color::Red, "13-plateform_red_VD.png");

  makeCross(gf::Color::Red, "14-platform_red_C.png");

  base.saveToFile("15-empty.png");

  // blue

  makeHorizontalLeft(gf::Color::Blue, "16-platform_blue_HL.png");
  makeHorizontal(gf::Color::Blue, "17-platform_blue_H.png");
  makeHorizontalRight(gf::Color::Blue, "18-platform_blue_HR.png");

  makeVerticalUp(gf::Color::Blue, "19-plateform_blue_VU.png");
  makeVertical(gf::Color::Blue, "20-platform_blue_V.png");
  makeVerticalDown(gf::Color::Blue, "21-plateform_blue_VD.png");

  makeCross(gf::Color::Blue, "22-platform_blue_C.png");

  base.saveToFile("23-empty.png");


  // limits

  makeHorizontal(gf::Color::Gray(), "24-limit_H.png");
  makeVertical(gf::Color::Gray(), "25-limit_V.png");
  makeCross(gf::Color::Gray(), "26-limit_C.png");

}
