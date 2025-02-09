
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;
  png.readFromFile("st2.png");

  FloodFilledImage image(png);

  DFS dfs(png, Point(40, 40), 0.2);
  BFS bfs1(png, Point(0, 0), 0.2);
  BFS bfs2(png, Point(80, 80), 0.2);
  MyColorPicker mycolor(0.05,0.005);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill(dfs, mycolor);
  image.addFloodFill(bfs1, rainbow);
  image.addFloodFill(bfs2, rainbow);


  Animation animation = image.animate(4000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
