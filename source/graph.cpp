/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is for the functions that are related to the graph, such as point or edge.
 */

# include <cmath>

# include "graph.h"

template class Point<float>;
template class Point<double>;

template class Edge<float>;
template class Edge<double>;

template <class valType> valType dot(const Point<valType> &a, const Point<valType> &b) {
  return a.x * b.x + a.y * b.y;
}

template <class valType>
valType Point<valType>:: length() {
  return sqrt(dot<valType>(*this, *this));
}

template <class valType>
valType& Point<valType>:: d(int sw) {
	return sw == 0 ? x : y;
}

template <class valType>
valType distance(const Point<valType> &a, const Point<valType> &b) {
  return (a - b).length();
}

template float distance<float> (const Point<float> &a, const Point<float> &b);
template double distance<double> (const Point<double> &a, const Point<double> &b);
