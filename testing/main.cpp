/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is the main of testing.
 */

# define THREADS_NUM 24

# define ENABLE_YAO
# define ENABLE_NORMAL

# include "time.h"
# include "rand.h"
# include "../source/graph.h"

# ifdef ENABLE_YAO
# include "../source/2d_Solver.h"
# endif // ENABLE_YAO

# ifdef ENABLE_NORMAL
# include "normal_Solver.h"
# endif // ENABLE_NORMAL

# include <omp.h>
# include <cmath>
# include <iomanip>
# include <cassert>
# include <iostream>

int main() {
  omp_set_num_threads(THREADS_NUM);

  std:: cout << "$ Generating random graph ... ";
  Graph2d<double> graph;
  generateRG(graph, 12000, 0, 10.0);
  std:: cout << "ok!" << std:: endl;

# ifdef ENABLE_YAO
  std:: cout << "$ Running Yao's algorithm ... " << std:: flush;
  unsigned long long t_start0 = get_wall_time();
  Solver2d<double> solver0(graph);
  double result0 = solver0.compute();
  unsigned long long t_end0 = get_wall_time();
  std:: cout << " ok!" << std:: endl;
# endif // ENABLE_YAO

# ifdef ENABLE_NORMAL
  std:: cout << "$ Running normal algorithm ... " << std:: flush;
  unsigned long long t_start1 = get_wall_time();
  normalSolver2d<double> solver1(graph);
  double result1 = solver1.compute();
  unsigned long long t_end1 = get_wall_time();
  std:: cout << " ok!" << std:: endl;
  std:: cout << std:: endl;
# endif // ENABLE_NORMAL

  std:: cout << "* RESULT:" << std:: endl;

# ifdef ENABLE_YAO
  std:: cout << "* Time0 = " << std:: fixed << std:: setprecision(6) << getTimeDiff(t_start0, t_end0) << "s" << std:: endl;
  std:: cout << "* Answer0 = " << std:: fixed << std:: setprecision(6) << result0 << std:: endl;
# endif // ENABLE_YAO

# ifdef ENABLE_NORMAL
  std:: cout << "* Time1 = " << std:: fixed << std:: setprecision(6) << getTimeDiff(t_start1, t_end1) << "s" << std:: endl;
  std:: cout << "* Answer1 = " << std:: fixed << std:: setprecision(6) << result1 << std:: endl;
# endif // ENABLE_NORMAL

  assert(fabs(result0 - result1) < 1e-4);
  std:: cout << "Correct !" << std:: endl;

  return 0;
}
