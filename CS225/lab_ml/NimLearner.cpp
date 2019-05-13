/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
  for (unsigned i = 0; i <= startingTokens; i++) {
    string p1 = "p1-"+ std::to_string(i);
    string p2 = "p2-"+ std::to_string(i);
    g_.insertVertex(p1);
    g_.insertVertex(p2);
  }
  //add vertex
  for (int i = startingTokens; i >= 2; i--) {
    g_.insertEdge("p1-"+ std::to_string(i),"p2-"+ std::to_string(i-1));
    g_.insertEdge("p1-"+ std::to_string(i),"p2-"+ std::to_string(i-2));
    g_.insertEdge("p2-"+ std::to_string(i),"p1-"+ std::to_string(i-1));
    g_.insertEdge("p2-"+ std::to_string(i),"p1-"+ std::to_string(i-2));
    g_.setEdgeWeight("p1-"+ std::to_string(i),"p2-"+ std::to_string(i-1),0);
    g_.setEdgeWeight("p1-"+ std::to_string(i),"p2-"+ std::to_string(i-2),0);
    g_.setEdgeWeight("p2-"+ std::to_string(i),"p1-"+ std::to_string(i-1),0);
    g_.setEdgeWeight("p2-"+ std::to_string(i),"p1-"+ std::to_string(i-2),0);
  }
  g_.insertEdge("p1-"+ std::to_string(1),"p2-"+ std::to_string(0));
  g_.insertEdge("p2-"+ std::to_string(1),"p1-"+ std::to_string(0));
  g_.setEdgeWeight("p1-"+ std::to_string(1),"p2-"+ std::to_string(0),0);
  g_.setEdgeWeight("p2-"+ std::to_string(1),"p1-"+ std::to_string(0),0);
    /* Your code goes here! */
  startingVertex_ = "p1-"+ std::to_string(startingTokens);
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
 Vertex current = startingVertex_;
 while(current != "p1-0" && current != "p2-0" && current != "p1-1" && current != "p2-1"){
   Vertex source = current;
   current = g_.getAdjacent(current)[rand()%2];
   path.push_back(g_.getEdge(source,current));
 }
 if (current == "p1-1"){
   path.push_back(g_.getEdge("p1-1","p2-0"));
 }
 if (current == "p2-1"){
   path.push_back(g_.getEdge("p2-1","p1-0"));
 }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 //p1win
  if(path.back().dest == "p2-0"){
    auto curr = path.begin();
    for (unsigned i = 0; i < path.size(); i++){
      if(i % 2 == 0) {
        int weight = g_.getEdgeWeight(curr->source,curr->dest) + 1;
        g_.setEdgeWeight(curr->source,curr->dest,weight);
      } else {
        int weight = g_.getEdgeWeight(curr->source,curr->dest)-1;
        g_.setEdgeWeight(curr->source,curr->dest,weight);
      }
      curr++;
    }
  }
    if(path.back().dest == "p1-0"){
      auto curr = path.begin();
      for (unsigned i = 0; i < path.size(); i++){
        if(i % 2 == 0) {
          int weight = g_.getEdgeWeight(curr->source,curr->dest) - 1;
          g_.setEdgeWeight(curr->source,curr->dest,weight);
        } else {
          int weight = g_.getEdgeWeight(curr->source,curr->dest)+1;
          g_.setEdgeWeight(curr->source,curr->dest,weight);
        }
        curr++;
      }
    }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
