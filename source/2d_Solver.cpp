/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is the main part of Yao's algorithm.
 */

# include <cmath>
# include <cassert>
# include <iostream>
# include <algorithm>

# include "cell.h"
# include "2d_Solver.h"

# define ENABLE_OPENMP

template class Solver2d<float>;
template class Solver2d<double>;

template <class valType>
Solver2d<valType>:: Solver2d(const Graph2d<valType> &_graph) {
  graph.clear(), curGraph.clear();
  cells.clear(); cellOwner.clear();
  for(auto node: _graph) {
    graph.push_back(std:: make_pair(node, node));
  }
  cellOwner.resize(graph.size());
}

template <class valType>
Point<valType> PointTransform(const Point<valType> &point) {
  return Point<valType>(point.x - point.y, sqrt(2) * point.y, point.Id);
}

template <class valType>
Point<valType> PointRotate(const Point<valType> &point) {
  return Point<valType>(sqrt(0.5) * point.x + sqrt(0.5) * point.y, -sqrt(0.5) * point.x + sqrt(0.5) * point.y, point.Id);
}

template <class valType>
bool Point4dX(const Point4d<valType> &p1, const Point4d<valType> &p2) {
  Point<valType> v1 = p1.second, v2 = p2.second;
  return v1.x < v2.x;
}

template <class valType>
bool Point4dY(const Point4d<valType> &p1, const Point4d<valType> &p2) {
  Point<valType> v1 = p1.second, v2 = p2.second;
  return v1.y < v2.y;
}

template Point<float> PointTransform(const Point<float> &point);
template Point<double> PointTransform(const Point<double> &point);

template Point<float> PointRotate(const Point<float> &point);
template Point<double> PointRotate(const Point<double> &point);

template bool Point4dX(const Point4d<float> &p1, const Point4d<float> &p2);
template bool Point4dX(const Point4d<double> &p1, const Point4d<double> &p2);

template bool Point4dY(const Point4d<float> &p1, const Point4d<float> &p2);
template bool Point4dY(const Point4d<double> &p1, const Point4d<double> &p2);

/* NOTE: this function will rotate the coordinate by (Pi/4), clockwise */
template <class valType>
void Solver2d<valType>:: transformCoordinateIntoCurrent() {
  /* build current graph */
  curGraph.clear();
  for(auto node: graph) {
    Point<valType> ord = node.second;
    Point<valType> axi = PointTransform(ord);
    // std:: cout << ord.Id << " " << "(" << node.first.x << "," << node.first.y << "," << axi.x << "," << axi.y << ")" << std:: endl;
    curGraph.push_back(std:: make_pair(node.first, axi));
  }

  /* rotate points (second) */
  int siz = graph.size();
  for(int i = 0; i < siz; ++ i) {
    Point<valType> u0 = graph[i].first;
    Point<valType> u1 = graph[i].second;
    graph[i] = std:: make_pair(u0, PointRotate(u1));
  }
}

template <class valType>
valType Solver2d<valType>:: compute() {
  KruskalSolver<valType> kruskalAlgorithm;
  std:: vector<Edge<valType> > edges;

  for(auto node: graph) {
    Point<valType> ord = node.first;
    kruskalAlgorithm.addPoint(ord);
  } // Though it's useless, but for OOP Design Style, it's good.

  for(int mode = 0; mode < 8; ++ mode) {
    // std:: cout << "mode = " << mode << std:: endl;

    transformCoordinateIntoCurrent();
    cellsDivide();

    for(auto node: curGraph) {
      Point<valType> ord = node.first;
      Point<valType> axi = node.second;
      Point<valType> result(1e9, 1e9, 0);

      // std:: cout << "querying " << node.first.Id << " (mode = " << mode << ")" << std:: endl;
      querySinglePoint(ord, axi, result);

      if(result.x < 1e8) {
        // std:: cout << "adding edge: " << ord.Id << " to " << result.Id << std:: endl;
        kruskalAlgorithm.addEdge(ord, result);
      }
      // std:: cout << std:: endl;
    }

    /* Free KD Tree */
    for(auto cell: cells) {
      cell.freeKDM();
    }
    cells.clear();
  }

  return kruskalAlgorithm.calcAnswer();
}

template <class valType>
void Solver2d<valType>:: cellsDivide() {
  int nodes = curGraph.size();
  int blockTot = int(pow(nodes, 1.0 / 3.0));
  if(blockTot < 1) blockTot = 1;

  std:: sort(curGraph.begin(), curGraph.end(), Point4dX<valType>);
  for(int xi = 0; xi < blockTot; ++ xi) {
    int bxl = BLOCK_LOW(xi, blockTot, nodes);
    int bxr = BLOCK_HGH(xi, blockTot, nodes);
    int bxs = BLOCK_SIZ(xi, blockTot, nodes);

    std:: sort(curGraph.begin() + bxl, curGraph.begin() + bxr + 1, Point4dY<valType>);
    for(int yi = 0; yi < blockTot; ++ yi) {
      int byl = BLOCK_LOW(yi, blockTot, bxs);
      int byr = BLOCK_HGH(yi, blockTot, bxs);
      int bys = BLOCK_SIZ(yi, blockTot, bxs);

      int indexL = bxl + byl, indexR = bxl + byr;
      /* Let us make a cell ! */
      valType xL = 1e8, xR = -1e8, yL = 1e8, yR = -1e8;
      # ifdef ENABLE_OPENMP
      # pragma omp parallel for
      # endif
      for(int i = indexL; i <= indexR; ++ i) {
        xL = std:: min(xL, curGraph[i].second.x);
        xR = std:: max(xR, curGraph[i].second.x);
        yL = std:: min(yL, curGraph[i].second.y);
        yR = std:: max(yR, curGraph[i].second.y);
        cellOwner[curGraph[i].first.Id] = cells.size();
      }
      cells.push_back(Cell<valType>(indexL, indexR, xL, xR, yL, yR, &curGraph));
      cells[cells.size() - 1].preprocess();
    }
  }
}

template <class valType>
void Solver2d<valType>:: querySinglePoint(Point<valType> ord, Point<valType> axi, Point<valType> &result) {
  # ifdef ENABLE_OPENMP
  # pragma omp parallel for
  # endif
  for(int i = 0; i < cells.size(); ++ i) {
    Point<valType> singleCellResult(1e9, 1e9, 0);
    cells[i].query(ord, axi, singleCellResult, i == cellOwner[ord.Id]);
    if(singleCellResult.x < 1e8) {
      if(result.x > 1e8 ||
        distance<valType> (singleCellResult, ord) < distance<valType> (result, ord)) {
          result = singleCellResult;
        }
    }
  }
}
