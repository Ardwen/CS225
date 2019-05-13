/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <iostream>
#include "cs225/PNG.h"
#include <map>
#include <queue>
#include <stack>
using namespace std;
using namespace cs225;
class SquareMaze {

    public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall (int x, int y, int dir, bool exist);
    vector <int> solveMaze();
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
    PNG * drawCreativeMaze() const;



    private:
	  int size;
    int setoff;
    //int exitCell;
    int mazeWidth;
    int mazeHeight;

    vector <int> solution;
    DisjointSets cells;
    vector< pair< pair<int, int>, int > >  walls;
    vector<bool> rightWalls;
    vector<bool> bottomWalls;

    int getIndex(int x, int y) const;
    //int getCellX( int cellID);
    //int getCellY( int cellID);
    int getNextCell( int x, int y, int dir );

};
#endif
