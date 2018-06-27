/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is bruteforce algorithm to solve 2D MST
 */

# ifndef __NORMAL_SOLVER_H__
# define __NORMAL_SOLVER_H__

# include "../source/graph.h"
# include "../source/kruskal.h"

template <class valType>
class normalSolver2d: public KruskalSolver<valType> {
public:
  normalSolver2d(const Graph2d<valType> &graph);
  valType compute();
};

# endif // __NORMAL_SOLVER_H__
