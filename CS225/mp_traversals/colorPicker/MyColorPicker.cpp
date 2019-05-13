#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;
MyColorPicker::MyColorPicker(double increment, double decrement)
  : hue(0),sat(1), increment(increment),decrement(decrement) { }

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue, sat, 0.5);
  hue += increment;
  sat -= decrement;
  if (hue >= 360) { hue -= 360; }
  if (sat < 0) {sat += 1;}
  return pixel;
}
