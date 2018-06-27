/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is the Union-Find Set Algorithm implement.
 */

# include <cassert>
# include <iostream>

# include "ufs.h"

ufSet:: ufSet(int _n): n(_n) {
  father.resize(n);
  for(int i = 0; i < n; i ++)
    father[i] = i;
}

int ufSet:: getFather(int x) {
  return father[x] == x ? x : father[x] = getFather(father[x]);
}

void ufSet:: letUnion(int x, int y) {
  assert(0 <= x && x < n);
  assert(0 <= y && y < n);

  int u = getFather(x), v = getFather(y);
  if(u != v) {
    father[u] = v;
  }
}

bool ufSet:: isUnion(int x, int y) {
  assert(0 <= x && x < n);
  assert(0 <= y && y < n);
  return getFather(x) == getFather(y);
}
