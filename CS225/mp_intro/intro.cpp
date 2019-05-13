#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG* original = new cs225::PNG();

  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();

  // Create out.png
  cs225::PNG* output = new cs225::PNG(width, height);
  for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
          cs225::HSLAPixel& prev = original->getPixel(x,y);
          (*output).getPixel(width - x - 1, height - y - 1) = prev;
      }
    }
  output->writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(800, 800);
  cs225::HSLAPixel ill = cs225::HSLAPixel(11, 0.8, 1, 1);
  for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        png.getPixel(x, y) = ill;
        double dist = 0;
        dist = sqrt((x-400) * (x - 400) + (y-400) * (y-400));
        if (dist > 200) {
          png.getPixel(x,y).h = 216;
        }
        else {
          png.getPixel(x,y).l = 1 - (dist * 0.005);
        }
      }
    }

  return png;
}
