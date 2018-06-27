/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is for the functions that are related to the graph, such as point or edge.
 */

# ifndef __GRAPH_H__
# define __GRAPH_H__

# include <vector>
# include <iostream>

/* Point */
template <class valType>
class Point {
public:
  valType x, y; int Id;

  Point(valType _x, valType _y, int id = 0): x(_x), y(_y), Id(id) {}

  friend Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
  friend Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }

  valType length();
  valType& d(int sw);
};

template <class valType> valType dot(const Point<valType> &a, const Point<valType> &b);
template <class valType> valType distance(const Point<valType> &a, const Point<valType> &b);

/* Edge */
template <class valType>
class Edge {
public:
  Point<valType> u, v;
  valType weight;

  Edge(const Point<valType> &a, const Point<valType> &b): u(a), v(b), weight(distance(a, b)) {}

  friend bool operator < (const Edge<valType> &a, const Edge<valType> &b) {
    return a.weight < b.weight;
  }
};

template <class valType>
using Graph2d = std:: vector<Point<valType> >;

template <class valType>
using Point4d = std:: pair<Point<valType>, Point<valType> >;

template <class valType>
using Graph4d = std:: vector<std:: pair<Point<valType>, Point<valType> > >;

# endif // __GRAPH_H__
