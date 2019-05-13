#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
#include <iostream>
/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  std::unordered_map<std::string, int> dist;
  std::unordered_map<std::string, bool> visited;
  std::unordered_map<std::string, std::string> pre;

  //std::vector<string> ;
  //std::string cur;
  for (auto i : vertexMap) {
    dist[i.first] = 99999;
    visited[i.first] = false;
    pre[i.first] = "none";
    //Q.enqueue(i.first);
  }
  dist[start] = 0;
  pre[start] = "start";
  std::string cur;
  for(unsigned i = 0; i < vertexMap.size(); i++) {
    //find the min dist
  int min = 99999;
  for (auto k : dist){
    if(!visited[k.first] && k.second <= min) {
      cur = k.first;
      min = k.second;
    }
  }
    visited[cur] = true;
    if(cur == end) {

      while(cur != "start"){
        path.push_front(cur);
        cur = pre[cur];
      }
      return path;
    }
   for(auto j : vertexMap) {
     if(isAdjacent(cur,j.first)){
       string next = j.first;
       if(!visited[next] && dist[cur] + 1 < dist[next]) {
         dist[next] = dist[cur] + 1;
         pre[next] = cur;
       }
     }
   }
  }
  return path;
}
