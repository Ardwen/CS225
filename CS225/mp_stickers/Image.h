/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

class Image : public cs225::PNG {
  public:
    void lighten();
    void lighten(double image);
    void darken();
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void rotateColor(double degree);
    void illinify();
    void scale(double factor);
    void scale(unsigned w, unsigned h);

};
