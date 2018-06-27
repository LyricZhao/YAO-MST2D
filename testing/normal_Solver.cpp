/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is bruteforce algorithm to solve 2D MST
 */

# include "normal_Solver.h"

# include "../source/kruskal.h"

template class normalSolver2d<float>;
template class normalSolver2d<double>;

template <class valType>
normalSolver2d<valType>:: normalSolver2d(const Graph2d<valType> &graph): KruskalSolver<valType>() {
  for(auto node: graph) {
    this -> addPoint(node);
  }

  int siz = graph.size();
  for(int i = 0; i < siz; ++ i) {
    for(int j = i + 1; j < siz; ++ j) {
      this -> addEdge(graph[i], graph[j]);
    }
  }
}

template <class valType>
valType normalSolver2d<valType>:: compute() {
  return this -> calcAnswer();
}
