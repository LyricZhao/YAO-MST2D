/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is the main part of Yao's algorithm.
 */

# ifndef __2D_SOLVER_H__
# define __2D_SOLVER_H__

# include "cell.h"
# include "graph.h"
# include "kruskal.h"

/* For dividing the cells */
# define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
# define BLOCK_HGH(id, p, n) (BLOCK_LOW((id) + 1, p, n) - 1)
# define BLOCK_SIZ(id, p, n) (BLOCK_HGH(id, p, n) - BLOCK_LOW(id, p, n) + 1)
# define BLOCK_OWN(j, p, n) (((p) * ((j) + 1) - 1) / (n))

template <class valType>
class Solver2d {
private:
  Graph4d<valType> graph, curGraph;
  std:: vector<Cell<valType> > cells;
  std:: vector<int> cellOwner;
  void cellsDivide();
  void transformCoordinateIntoCurrent();
  void querySinglePoint(Point<valType> ord, Point<valType> axi, Point<valType> &result);

public:
  valType compute();
  Solver2d(const Graph2d<valType> &_graph);
};

template <class valType>
Point<valType> PointTransform(const Point<valType> &point);

template <class valType>
Point<valType> PointRotate(const Point<valType> &point);

# endif // __2D_SOLVER_H__
