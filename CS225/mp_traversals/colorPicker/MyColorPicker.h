#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(double increment, double decrement);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  double hue;
  double sat;
  double increment;
  double decrement;

};
