/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is for generating random data
 */

# include <ctime>
# include <cstdlib>

# include "rand.h"

# include "../source/graph.h"

randomEngine:: randomEngine(bool state, double l, double r): flag(state) {
  unsigned seed = 19981011;
  if(flag) {
    seed = time(NULL);
  }
  generator = new std:: default_random_engine(seed);
  distribution = new std:: uniform_real_distribution<double> (l, r);
}

randomEngine:: ~randomEngine() {
  delete generator;
  delete distribution;
}

double randomEngine:: getRandom() {
  return (*distribution)(*generator);
}

void generateRG(Graph2d<double> &G, int nodes, double l, double r) {
  G.clear();
  randomEngine RE(false, l, r);
  for(int i = 0; i < nodes; ++ i) {
    double x = RE.getRandom();
    double y = RE.getRandom();
    // std:: cout << "Generating Point - " << i << " (" << x << ", " << y << ")" << std:: endl;
    G.push_back(Point<double>(x, y, i));
  }
}
