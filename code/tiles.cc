#include <cassert>

#include <gf/Color.h>
#include <gf/Direction.h>
#include <gf/Image.h>


namespace {
  constexpr int Size = 34;
  constexpr int Mid = 17;
  constexpr int Lo = 9;
  constexpr int Hi = 25;
  constexpr int Gap = 5;

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


  void makeCableStraightHorizontal(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = 0; i < Size; ++i) {
      for (int j = Mid - 1; j < Mid + 1; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCableStraightHorizontalRight(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = 0; i < Mid; ++i) {
      for (int j = Mid - 1; j < Mid + 1; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCableStraightHorizontalLeft(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid; i < Size; ++i) {
      for (int j = Mid - 1; j < Mid + 1; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCableStraightVertical(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid - 1; i < Mid + 1; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCableStraightVerticalDown(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid - 1; i < Mid + 1; ++i) {
      for (int j = 0; j < Mid; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCableStraightVerticalUp(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid - 1; i < Mid + 1; ++i) {
      for (int j = Mid; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCableCross(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = 0; i < Size; ++i) {
      for (int j = Mid - 1; j < Mid + 1; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    for (int i = Mid - 1; i < Mid + 1; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeCableTurn(gf::Color4f color, gf::Direction from, gf::Direction to, gf::Path path) {
    gf::Image image = makeBase();

    if (from == gf::Direction:: Left) {
      for (int i = 0; i < Mid + 1; ++i) {
        for (int j = Mid - 1; j < Mid + 1; ++j) {
          image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
        }
      }
    } else {
      assert(from == gf::Direction::Right);

      for (int i = Mid - 1; i < Size; ++i) {
        for (int j = Mid - 1; j < Mid + 1; ++j) {
          image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
        }
      }
    }

    if (to == gf::Direction::Down) {
      for (int i = Mid - 1; i < Mid + 1; ++i) {
        for (int j = Mid - 1; j < Size; ++j) {
          image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
        }
      }
    } else {
      assert(to == gf::Direction::Up);

      for (int i = Mid - 1; i < Mid + 1; ++i) {
        for (int j = 0; j < Mid + 1; ++j) {
          image.setPixel(gf::vec(i, j), gf::Color::toRgba32(color));
        }
      }
    }

    image.saveToFile(path);
  }

  void makeDoubleCableFull(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid - 1; i < Mid + 1; ++i) {
      for (int j = 0; j < Size; ++j) {
        image.setPixel(gf::vec(i - Gap, j), gf::Color::toRgba32(color));
        image.setPixel(gf::vec(i + Gap, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeDoubleCableUp(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid - 1; i < Mid + 1; ++i) {
      for (int j = Mid; j < Size; ++j) {
        image.setPixel(gf::vec(i - Gap, j), gf::Color::toRgba32(color));
        image.setPixel(gf::vec(i + Gap, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeDoubleCableDown(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int i = Mid - 1; i < Mid + 1; ++i) {
      for (int j = 0; j < Mid; ++j) {
        image.setPixel(gf::vec(i - Gap, j), gf::Color::toRgba32(color));
        image.setPixel(gf::vec(i + Gap, j), gf::Color::toRgba32(color));
      }
    }

    image.saveToFile(path);
  }

  void makeSink(gf::Color4f color, gf::Path path) {
    gf::Image image = makeBase();

    for (int k = 0; k < Size; ++k) {
      image.setPixel(gf::vec(k, k), gf::Color::toRgba32(color));
      image.setPixel(gf::vec(k, Size - k - 1), gf::Color::toRgba32(color));
    }

    image.saveToFile(path);
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

  makeSink(gf::Color::White, "07-sink.png");

  // red

  makeHorizontalLeft(gf::Color::Red, "08-platform_red_HL.png");
  makeHorizontal(gf::Color::Red, "09-platform_red_H.png");
  makeHorizontalRight(gf::Color::Red, "10-platform_red_HR.png");

  makeVerticalUp(gf::Color::Red, "11-plateform_red_VU.png");
  makeVertical(gf::Color::Red, "12-platform_red_V.png");
  makeVerticalDown(gf::Color::Red, "13-plateform_red_VD.png");

  makeCross(gf::Color::Red, "14-platform_red_C.png");

  makeSink(gf::Color::Red, "15-start_red.png");

  // blue

  makeHorizontalLeft(gf::Color::Blue, "16-platform_blue_HL.png");
  makeHorizontal(gf::Color::Blue, "17-platform_blue_H.png");
  makeHorizontalRight(gf::Color::Blue, "18-platform_blue_HR.png");

  makeVerticalUp(gf::Color::Blue, "19-plateform_blue_VU.png");
  makeVertical(gf::Color::Blue, "20-platform_blue_V.png");
  makeVerticalDown(gf::Color::Blue, "21-plateform_blue_VD.png");

  makeCross(gf::Color::Blue, "22-platform_blue_C.png");

  makeSink(gf::Color::Blue, "23-start_blue.png");

  // limits

  makeHorizontal(gf::Color::Gray(), "24-limit_H.png");
  makeVertical(gf::Color::Gray(), "25-limit_V.png");
  makeCross(gf::Color::Gray(), "26-limit_C.png");

  base.saveToFile("27-empty.png");
  base.saveToFile("28-empty.png");
  base.saveToFile("29-empty.png");

  makeSink(gf::Color::Green, "30-exit.png");

  makeSink(gf::Color::Gray(), "31-button.png");

  // cables

  makeCableStraightHorizontalLeft(gf::Color::Gray(0.75f), "32-cable_straight_HL.png");
  makeCableStraightHorizontal(gf::Color::Gray(0.75f), "33-cable_straight_H.png");
  makeCableStraightHorizontalRight(gf::Color::Gray(0.75f), "34-cable_straight_HR.png");
  makeCableStraightVerticalUp(gf::Color::Gray(0.75f), "35-cable_straight_VU.png");
  makeCableStraightVertical(gf::Color::Gray(0.75f), "36-cable_straight_V.png");
  makeCableStraightVerticalDown(gf::Color::Gray(0.75f), "37-cable_straight_VD.png");
  makeCableCross(gf::Color::Gray(0.75f), "38-cable_cross.png");

  base.saveToFile("39-empty.png");

  makeCableTurn(gf::Color::Gray(0.75f), gf::Direction::Left, gf::Direction::Down, "40-cable_turn_LD.png");
  makeCableTurn(gf::Color::Gray(0.75f), gf::Direction::Left, gf::Direction::Up, "41-cable_turn_LU.png");
  makeCableTurn(gf::Color::Gray(0.75f), gf::Direction::Right, gf::Direction::Down, "42-cable_turn_RD.png");
  makeCableTurn(gf::Color::Gray(0.75f), gf::Direction::Right, gf::Direction::Up, "43-cable_turn_RU.png");

  // double cable

  makeDoubleCableFull(gf::Color::Gray(0.25f), "44-double_cable_V.png");
  makeDoubleCableDown(gf::Color::Gray(0.25f), "45-double_cable_D.png");
  makeDoubleCableUp(gf::Color::Gray(0.25f), "46-double_cable_U.png");

  base.saveToFile("47-empty.png");

}
