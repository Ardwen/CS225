#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze png;
    png.makeMaze(100, 100);
    PNG* canvas = png.drawCreativeMaze();
    canvas->writeToFile("creative.png");
    cout << "creative maze" << endl;
    return 0;
}
