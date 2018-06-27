/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is a MST solver (kruskal algorithm).
 */

# ifndef __KRUSKAL_H__
# define __KRUSKAL_H__

# include <vector>

# include "graph.h"

template <class valType>
class KruskalSolver {
private:
  std:: vector<Edge<valType> > edges;
  std:: vector<Point<valType> > points;

public:
  KruskalSolver();
  void addPoint(const Point<valType> &x);
  void addEdge(const Edge<valType> &e);
  void addEdge(const Point<valType> &a, const Point<valType> &b);

  valType calcAnswer();
};

# endif // __KRUSKAL_H__
