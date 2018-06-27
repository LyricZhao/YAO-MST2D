/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is algorithms inside a cell
 */

# include "cell.h"

# define ENABLE_KD_OPT

template class Cell<float>;
template class Cell<double>;

template <class valType>
void Cell<valType>:: freeKDM() {
  # ifdef ENABLE_KD_OPT
  if(kdt) delete kdt;
  # endif
}

template <class valType>
void Cell<valType>:: preprocess() {
    # ifdef ENABLE_KD_OPT
    std:: vector<Point<valType> > vPoints;
    vPoints.clear();

    for(int i = l; i <= r; ++ i) {
      vPoints.push_back((*g4d)[i].first);
    }

    kdt = new kdTree<valType> (vPoints);
    # endif
}     

template <class valType>
void Cell<valType>:: query(Point<valType> ord, Point<valType> axi, Point<valType> &result, bool iss) {
  if(!iss && axi.x <= xL && axi.y <= yL) {
    # ifdef ENABLE_KD_OPT
    queryAll(ord, result);
    # else
    querySingle(ord, axi, result);
    # endif
  } else if(axi.x > xR && axi.y > yR) {
    // do nothing
  } else {
    querySingle(ord, axi, result);
  }
}

template <class valType>
void Cell<valType>:: querySingle(Point<valType> point, Point<valType> axi, Point<valType> &result) {
  for(int i = l; i <= r; ++ i) {
    Point<valType> ord = (*g4d)[i].first;
    Point<valType> ost = (*g4d)[i].second;
    if(ord.Id == point.Id) continue;
    if((result.x > 1e8 ||
      distance<valType> (point, ord) < distance<valType> (point, result)) &&
      (axi.x <= ost.x && axi.y <= ost.y)) {
        result = ord;
      }
  }
}

template <class valType>
void Cell<valType>:: queryAll(Point<valType> point, Point<valType> &result) {
  std:: pair<valType, Point<valType> > answer = kdt -> query(point);
  result = answer.second;
}
