/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is for generating random data
 */

# ifndef __RAND_H__
# define __RAND_H__

# include <random>

# include "../source/graph.h"

/* Random based on time if flag = true */
class randomEngine {
private:
  bool flag;
  std:: default_random_engine *generator;
  std:: uniform_real_distribution<double> *distribution;

public:
  randomEngine(bool state, double l, double r);
  ~randomEngine();
  double getRandom();
};

void generateRG(Graph2d<double> &G, int nodes, double l, double r);

# endif // __RAND_H__
