#include "Image.h"
#include "StickerSheet.h"
namespace cs225{
StickerSheet::StickerSheet (const Image &picture, unsigned max) {
  max_ = max;
  stickersptr = new Image*[max];
  base = new Image(picture);
  xc = new int[max];
  yc = new int[max];
  for (unsigned i = 0; i < max; i ++) {
    stickersptr[i] = NULL;
    xc[i] = 0;
    yc[i] = 0;
  }
}

void StickerSheet::_delete() {
  for (unsigned i = 0; i < max_; i++) {
    if (stickersptr[i] != NULL) {
    delete stickersptr[i];
    stickersptr[i] = NULL;
  }
  }
  delete[] stickersptr;
  delete[] xc;
  delete[] yc;
  delete base;
  stickersptr = NULL;
  xc = NULL;
  yc = NULL;
  base = NULL;
}

void StickerSheet::_copy(const StickerSheet & other) {
  max_ = other.max_;
  stickersptr = new Image*[max_];
  base = new Image(*(other.base));
  xc = new int[max_];
  yc = new int[max_];
  for (unsigned i = 0; i < max_; i++) {
    if (other.stickersptr[i] != NULL) {
    stickersptr[i] = new Image ();
    *stickersptr[i] = *(other.stickersptr[i]);
    xc[i] = other.xc[i];
    yc[i] = other.yc[i];
  } else {
    stickersptr[i] = NULL;
    xc[i] = 0;
    yc[i] = 0;
  }
  }
}
StickerSheet:: ~StickerSheet () {
  _delete();
}
StickerSheet:: StickerSheet(const StickerSheet &other) {
  _copy(other);
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
  int index = -1;
  for (unsigned i = 0; i < max_; i++) {
    if(stickersptr[i] == NULL) {
      index = i;
      break;
    }
  }
  if (index < 0) {
    return -1;
  } else {
  stickersptr[index] = new Image(sticker);
  xc[index] = x;
  yc[index] = y;
  return index;
}
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
  if (index > max_ - 1 || stickersptr[index] == NULL ) {
    return false;
  }
  xc[index] = x;
  yc[index] = y;
  return true;
}

void StickerSheet::removeSticker (unsigned index) {
  if (index > max_ - 1 || stickersptr[index] == NULL ) {return;}
  stickersptr[index] = NULL;
  xc[index] = 0;
  yc[index] = 0;
}

void StickerSheet::changeMaxStickers (unsigned max) {
  if (max == max_) {return;}
  Image **tmp = new Image*[max_];
  int *txc = new int[max_];
  int *tyc = new int[max_];
  for (unsigned j = 0; j < max_; j++) {
    tmp[j] = stickersptr[j];
    txc[j] = xc[j];
    tyc[j] = yc[j];
    }
    delete[] stickersptr;
    delete[] xc;
    delete[] yc;
    stickersptr = new Image*[max];
    xc = new int[max];
    yc = new int[max];
   for (unsigned i = 0; i < max; i++) {
      stickersptr[i] = NULL;
      xc[i] = 0;
      yc[i] = 0;
    }
    for (unsigned i = 0; i < max; i++) {
      if (i < max_) {
      stickersptr[i] = tmp[i];
      xc[i] = txc[i];
      yc[i] = tyc[i];
  }
  }
  max_ = max;
  delete[] tmp;
  delete[] txc;
  delete[] tyc;
}

Image *StickerSheet::getSticker (unsigned index) {
  if (index > max_ - 1 || stickersptr[index] == NULL) {
    return NULL;
  }
  Image *gsticker = stickersptr[index];
  return gsticker;
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
  if (this != &other) {
  _delete();
  _copy(other);
}
  return *this;
}

Image StickerSheet::render () const {
  Image *output = new Image(*base);
  unsigned hei;
  unsigned wid;
  hei = base->height();
  wid = base->width();
  for (unsigned i = 0; i < max_; i++) {
    if (stickersptr[i] != NULL) {
    if (yc[i] + stickersptr[i] -> height() > hei) {
      hei = yc[i] + stickersptr[i] ->height();
    }
    if (xc[i] + stickersptr[i] -> width() > wid) {
      wid = xc[i] + stickersptr[i]-> width();
    }
  }
  }
  output -> resize(wid, hei);
  for (unsigned j = 0; j < max_; j++) {
    if (stickersptr[j] != NULL) {
      for (unsigned k = 0; k < stickersptr[j] -> width(); k++) {
        for (unsigned m = 0; m < stickersptr[j] -> height(); m++) {
          HSLAPixel &stick = stickersptr[j] -> getPixel(k,m);
          if (stick.a != 0) {
          output-> getPixel(k + xc[j], m + yc[j]) = stick;
        }
      }
    }
  }
}
  return *output;
}
}
