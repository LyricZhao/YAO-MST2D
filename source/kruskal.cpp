/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is a MST solver (kruskal algorithm).
 */

# include <cassert>
# include <iostream>
# include <algorithm>

# include "ufs.h"
# include "graph.h"
# include "kruskal.h"

template class KruskalSolver<float>;
template class KruskalSolver<double>;

template <class valType>
KruskalSolver<valType>:: KruskalSolver() {
  edges.clear(); points.clear();
}

template <class valType>
void KruskalSolver<valType>:: addPoint(const Point<valType> &x) {
  points.push_back(x);
}

template <class valType>
void KruskalSolver<valType>:: addEdge(const Edge<valType> &e) {
  edges.push_back(e);
}

template <class valType>
void KruskalSolver<valType>:: addEdge(const Point<valType> &a, const Point<valType> &b) {
  edges.push_back(Edge<valType>(a, b));
}

template<class valType>
valType KruskalSolver<valType>:: calcAnswer() {
  valType answer = 0;

  ufSet uf_set(points.size());
  std:: sort(edges.begin(), edges.end());

  int edge_count = 0;

  for(auto edge: edges) {
    int u = edge.u.Id, v = edge.v.Id;
    if(!uf_set.isUnion(u, v)) {
      ++ edge_count;
      answer += edge.weight;
      uf_set.letUnion(u, v);
    }

    if(edge_count == points.size() - 1) break;
  }

  assert(edge_count == points.size() - 1);
  return answer;
}
