#include "maze.h"

SquareMaze::SquareMaze()
{
    mazeWidth = 0;
    mazeHeight = 0;
    size = 0;
    cells = DisjointSets();
}
void SquareMaze::makeMaze(int width, int height) {

    mazeHeight = height;
    mazeWidth = width;
    size = width * height;
    setoff = rand() % 999999;
    for(int i = 0; i < size; i++)
    {
        bottomWalls.push_back(true);
        rightWalls.push_back(true);
    }

    cells.addelements(size);

    srand(time(NULL)+ setoff);

    for (int i = 0; i < size - 1;)
    {
        int removex = rand() % width;
        int removey = rand() % height;

        if(rand() % 2)
        {
            if (removex < width - 1)
            {
                if (cells.find(removey * width + removex) != cells.find(removey * width + removex + 1))
                {
                    rightWalls[removey * width + removex] = false;
                    cells.setunion(removey * width + removex, removey * width + (removex + 1));
                    i++;
                }
            }
        }
        else if (removey < height - 1)
        {
            if (cells.find(removey * width + removex) != cells.find((removey + 1) * width + removex))
            {
                bottomWalls[removey * width + removex] = false;
                cells.setunion(removey * width + removex, (removey + 1) * width + removex);
                i++;
            }
        }
    }
}


bool SquareMaze::canTravel(int x, int y, int dir) const
{
  int curr_index = y*mazeWidth+x;
  if(dir == 0){
    if(x==mazeWidth-1){
      return false;
    }
    if(rightWalls[curr_index]){
      return false;
    }
    return true;
  }
  if(dir == 1){
    if(y==mazeHeight-1){
      return false;
    }
    if(bottomWalls[curr_index]){
      return false;
    }
    return true;
  }
  if(dir == 2){
    if(x==0){
      return false;
    }
    if(rightWalls[curr_index-1]){
      return false;
    }
    return true;
  }
  if(dir == 3){
    if(y==0){
      return false;
    }
    if(bottomWalls[(y-1)*mazeWidth+x]){
      return false;
    }
    return true;
  }
  return false;
}

void SquareMaze::setWall (int x, int y, int dir, bool exists)
{
    int cellId = getIndex(x, y);

    if (dir == 0)
        rightWalls[cellId] = exists;
    else
        bottomWalls[cellId] = exists;
}

vector <int> SquareMaze::solveMaze()
{
    map <int, pair<int,int>> pathMap;
    vector<bool> visited(mazeWidth * mazeHeight, false);

    //  neighbors
    queue <int > q;

    q.push(0);
    //mark start visited
    visited[0] = true;

    while (!q.empty())
    {
        int cur = q.front();
        int curY = cur / mazeWidth;
        int curX = cur % mazeWidth;

        q.pop();

        // loop through four directions to see if the next cell in that dir is travelable
        for (int i = 0; i < 4; i++)
        {
            // info of next cell
            int nextCell = getNextCell( curX, curY, i );
            int nextY = nextCell / mazeWidth;
            int nextX = nextCell % mazeHeight;


            // check if we can go there
            if (canTravel( curX, curY, i) && !visited[nextCell])
            {
                //get next cell and put it in queue
                q.push(nextCell);
                visited[nextCell] = true;
                //map next to cur and the direction
                pathMap[nextCell] = make_pair(cur,i);
            }
        }
    }
	  int max= 0;
    int maxlength= 0;

    //find out the longest path
    for (int i = 0; i < mazeWidth; i++)
    {
        int end = getIndex(i, mazeHeight -1);
        int rout = 0;


        // count number of steps
        while (end != 0)
        {
            end = pathMap[end].first;
            rout++;
        }
        if (rout > maxlength)
        {
            maxlength = rout;
            max = i;
        }
    }
    // create the vecotr for longest path
    int lastCell = getIndex( max, mazeHeight -1);

    int start = 0;
    int end = lastCell;

    stack<int> steps;
    while (end != start)
    {
        solution.push_back(pathMap[end].second);
        end = pathMap[end].first;
    }
    std::reverse(solution.begin(),solution.end());
    return solution;
}
PNG * SquareMaze::drawMaze() const
{
  int curX;
      int curY;
      PNG * retval = new PNG( 10 * mazeWidth + 1, 10 * mazeHeight +1);

      for (int i = 0; i < 10 * mazeHeight +1; i++ )
      {
          (retval->getPixel(0, i)).h = 0;
          (retval->getPixel(0, i)).s = 0;
          (retval->getPixel(0, i)).l = 0;

      }
      for ( int i = 10; i < 10 * mazeWidth +1; i++)
      {
          (retval->getPixel(i, 0)).h = 0;
          (retval->getPixel(i, 0)).l = 0;
          (retval->getPixel(i, 0)).s = 0;

      }

      for (int y = 0; y < mazeHeight; y++ )
      {
  		for ( int x = 0; x < mazeWidth; x++ )
          {
              if (bottomWalls[ getIndex(x, y) ] )
              {
                  for (int i = 0; i <= 10; i++ )
                  {
                      curY = ( y + 1 ) * 10;
                      curX = x * 10 + i;

                  	(retval->getPixel(curX, curY)).l = 0;
                      (retval->getPixel(curX, curY)).h = 0;
                      (retval->getPixel(curX, curY)).s = 0;

                  }
              }

              if ( rightWalls[ getIndex(x, y) ] )
              {
                  for (int i = 0; i <= 10; i++)
                  {
                      curY = y * 10 + i;
                      curX = (x + 1) * 10;

                      (retval->getPixel(curX, curY)).h = 0;
                      (retval->getPixel(curX, curY)).l = 0;
                      (retval->getPixel(curX, curY)).s = 0;

                  }
              }
          }
      }

      return retval;
  }
  PNG * SquareMaze::drawCreativeMaze() const
  {
        int curX;
        int curY;
        PNG * retval = new PNG( 10 * mazeWidth + 1, 10 * mazeHeight +1);

        for (int i = 0; i < 10 * mazeHeight +1; i++ )
        {
            (retval->getPixel(0, i)).h = 0;
            (retval->getPixel(0, i)).s = 0;
            (retval->getPixel(0, i)).l = 0;

        }
        for ( int i = 10; i < 10 * mazeWidth +1; i++)
        {
            (retval->getPixel(i, 0)).h = 0;
            (retval->getPixel(i, 0)).l = 0;
            (retval->getPixel(i, 0)).s = 0;

        }

        for (int y = 0; y < mazeHeight / 2; y++ )
        {
    		for ( int x = 0; x < mazeWidth - y ; x++ )
            {
                if (bottomWalls[ getIndex(x, y) ] )
                {
                    for (int i = 0; i <= 10; i++ )
                    {
                        curY = ( y + 1 ) * 10;
                        curX = x * 10 + i;

                    	(retval->getPixel(curX, curY)).l = 0;
                        (retval->getPixel(curX, curY)).h = 0;
                        (retval->getPixel(curX, curY)).s = 0;

                    }
                }

                if ( rightWalls[ getIndex(x, y)] )
                {
                    for (int i = 0; i <= 10; i++)
                    {
                        curY = y * 10 + i;
                        curX = (x + 1) * 10;

                        (retval->getPixel(curX, curY)).h = 0;
                        (retval->getPixel(curX, curY)).l = 0;
                        (retval->getPixel(curX, curY)).s = 0;

                    }
                }
            }
            for (int y = mazeHeight/2; y < mazeHeight; y++ )
            {
        		for ( int x = 0; x < mazeWidth - y ; x++ )
                {
                    if (bottomWalls[ getIndex(x, y) ] )
                    {
                        for (int i = 0; i <= 10; i++ )
                        {
                            curY = ( y + 1 ) * 10;
                            curX = x * 10 + i;

                        	(retval->getPixel(curX, curY)).l = 0;
                            (retval->getPixel(curX, curY)).h = 0;
                            (retval->getPixel(curX, curY)).s = 0;

                        }
                    }

                    if ( rightWalls[ getIndex(x, y)] )
                    {
                        for (int i = 0; i <= 10; i++)
                        {
                            curY = y * 10 + i;
                            curX = (x + 1) * 10;

                            (retval->getPixel(curX, curY)).h = 0;
                            (retval->getPixel(curX, curY)).l = 0;
                            (retval->getPixel(curX, curY)).s = 0;

                        }
                    }
                }
        }
    }
    return retval;
}
PNG * SquareMaze::drawMazeWithSolution()
{
    if (solution.size() == 0)
    {
        return new PNG();
    }


    PNG * retval = drawMaze();

    int curY = 5;
    int curX = 5;


    for ( unsigned i= 0; i < solution.size(); i++)
    {
        if ( solution[i] == 0 )
        {
            for (int j = 0; j <= 10; j++ )
            {
                (retval->getPixel( curX + j, curY )).h = 0;
                (retval->getPixel( curX + j, curY )).s = 1;
                (retval->getPixel( curX + j, curY )).l = 0.5;

            }
            curX += 10;
        }
        else if ( solution [i] == 3)
        {
            for (int j = 0; j <= 10; j++)
            {
                (retval->getPixel( curX , curY -j)).h = 0;
                (retval->getPixel( curX , curY -j)).s = 1;
                (retval->getPixel( curX , curY -j)).l = 0.5;

            }
            curY -= 10;
        }
        else if ( solution [i] == 1)
        {
            for (int j = 0; j <= 10; j++)
            {
                (retval->getPixel( curX , curY +j)).h = 0;
                (retval->getPixel( curX , curY +j)).s = 1;
                (retval->getPixel( curX , curY +j)).l = 0.5;

            }
            curY += 10;
        }
        else if ( solution [i] == 2)
        {
            for (int j = 0; j <= 10; j++)
            {
                (retval->getPixel( curX - j, curY )).h = 0;
                (retval->getPixel( curX - j, curY )).s = 1;
                (retval->getPixel( curX - j, curY )).l = 0.5;

            }
            curX -= 10;
        }

    }

    int exitY = curY + 5;
    int exitX = curX - 5;

    for (int i = 1; i < 10; i++)
    {
                (retval->getPixel( exitX + i, exitY )).h = 0;
                (retval->getPixel( exitX + i, exitY )).s = 0;
                (retval->getPixel( exitX +i, exitY )).l = 1;

    }

    return retval;
  }

int SquareMaze::getIndex(int x, int y) const
{
    return y * mazeWidth + x;
}


int SquareMaze::getNextCell( int x, int y, int dir )
{
    if (dir==0)
        return getIndex(x+1,y);
    if (dir==1)
        return getIndex(x,y+1);
    if (dir==2)
        return getIndex(x-1,y);
    if (dir==3)
        return getIndex(x,y-1);
    else
        return 0;
}
