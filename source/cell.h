/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is algorithms inside a cell
 */

# ifndef __CELL_H__
# define __CELL_H__

# include <vector>

# include "graph.h"
# include "./KD-Opt/kdTree.h"

template <class valType>
class Cell {
public:
  int l, r;
  valType xL, xR;
  valType yL, yR;
  Graph4d<valType> *g4d;
  kdTree<valType> *kdt;
  Cell(int _l, int _r, valType _xL, valType _xR, valType _yL, valType _yR, Graph4d<valType> *_g4d):
    l(_l), r(_r), xL(_xL), xR(_xR), yL(_yL), yR(_yR), g4d(_g4d), kdt(NULL) { }

  void freeKDM();
  void preprocess();
  void query(Point<valType> ord, Point<valType> axi, Point<valType> &result, bool iss);
  void querySingle(Point<valType> point, Point<valType> axi, Point<valType> &result);
  void queryAll(Point<valType> point, Point<valType> &result);

};

# endif // __CELL_H__
