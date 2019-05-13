#include "Image.h"
#include "cs225/HSLAPixel.h"

void Image::lighten() {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).l += 0.1;
      if ((this->getPixel(i, j)).l > 1) {
        (this->getPixel(i, j)).l = 1;
      }
    }
  }
}
void Image::lighten(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).l += amount;
      if ((this->getPixel(i, j)).l > 1) {
        (this->getPixel(i, j)).l = 1;
      }
    }
  }
}

void Image::darken() {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).l -= 0.1;
      if ((this->getPixel(i, j)).l < 0) {
        (this->getPixel(i, j)).l = 0;
      }
    }
  }
}

void Image::darken(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).l -= amount;
      if ((this->getPixel(i, j)).l < 0) {
        (this->getPixel(i, j)).l = 0;
      }
    }
  }
}

void Image::saturate() {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).s += 0.1;
      if ((this->getPixel(i, j)).s > 1) {
        (this->getPixel(i, j)).s = 1;
      }
    }
  }
}
void Image::saturate(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).s += amount;
      if ((this->getPixel(i, j)).s > 1) {
        (this->getPixel(i, j)).s = 1;
      }
    }
  }
}
void Image::desaturate() {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).s -= 0.1;
      if ((this->getPixel(i, j)).s < 0) {
        (this->getPixel(i, j)).s = 0;
      }
    }
  }
}
void Image::desaturate(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).s += amount;
      if ((this->getPixel(i, j)).s < 0) {
        (this->getPixel(i, j)).s = 0;
      }
    }
  }
}

void Image::grayscale() {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
        (this->getPixel(i, j)).s = 0;
    }
  }
}

void Image::rotateColor(double degree) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      (this->getPixel(i, j)).h += degree;
      if ((this->getPixel(i, j)).h > 360) {
        (this->getPixel(i, j)).h -= 360;
      }
      if ((this->getPixel(i, j)).h < 0) {
        (this->getPixel(i, j)).h += 360;
      }
    }
  }
}
void Image::illinify(){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      double ph = 0;
      ph = (this->getPixel(i, j)).h;
      if (ph > 293.5 || ph < 113.5) {
        (this->getPixel(i, j)).h = 11;
      } else {
        (this->getPixel(i, j)).h = 216;
      }
    }
  }
}
void Image::scale(double factor) {
  Image tmp = Image(*this);
  resize(this->width() * factor, this->height() * factor);
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      this->getPixel(i, j) = tmp.getPixel(i / factor, j / factor);
    }
  }
}
void Image::scale(unsigned w, unsigned h) {
    double factor = w/this->width();
    resize(w,h * factor);
    Image tmp = Image(*this);
    for (unsigned i = 0; i < this->width(); i++) {
      for (unsigned j = 0; j < this->height(); j++) {
        this->getPixel(i, j) = tmp.getPixel(i / factor, j / factor);
      }
    }
}
