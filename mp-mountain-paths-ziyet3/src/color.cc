#include "color.hpp"

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  if (r < 0 || r > kMaxColorValue || g < 0 || g > kMaxColorValue || b < 0 ||
      b > kMaxColorValue) {
    throw std::invalid_argument("invalid argument");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}