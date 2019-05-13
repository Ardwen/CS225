#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace cs225;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  traversal = NULL;
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(Point x, ImageTraversal * d_b, const PNG & png, const double tolerance){
  tolerance_ = tolerance;
  png_ = png;
  traversal = d_b;
  current_ = x;
  start_ = d_b -> peek();
  for (int i = 0; i < (int)png_.width(); i++) {
    std::vector<bool> visit;
    visited.push_back(visit);
    for (int j = 0; j < (int)png_.height(); j++) {
      visited[i].push_back(false);
    }
  }//Initialize the true/false
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
 visited[current_.x][current_.y] = true;
 Point started = start_;
 HSLAPixel p1 = png_.getPixel(started.x, started.y);


  Point right = Point(current_.x+1, current_.y);
  Point above = Point(current_.x, current_.y+1);
  Point left = Point(current_.x-1, current_.y);
  Point below = Point(current_.x, current_.y-1);
  if (canBeVisited(right)) {
    traversal -> add(right);
  }
  if (canBeVisited(above)) {
    traversal -> add(above);
  }
  if (canBeVisited(left)) {
    traversal -> add(left);
  }
  if (canBeVisited(below)) {
    traversal -> add(below);
  }
if (traversal->empty() == false) {
    Point next = traversal->pop();
    while (visited[next.x][next.y] == true && traversal->empty() == false) {
      next = traversal->pop();
    }
    current_ = next;
    return *this;
  } else {
    traversal = NULL;
    return *this;
  }

}


bool ImageTraversal::Iterator::canBeVisited(Point p){
  Point started = start_;
  if (p.x >= png_.width()||p.y >= png_.height()) return false;
  HSLAPixel p1 = png_.getPixel(started.x, started.y);
  HSLAPixel p2 = png_.getPixel(p.x, p.y);
  return tolerance_ > calculateDelta(p1, p2);
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}
