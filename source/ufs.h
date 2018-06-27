/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is the Union-Find Set Algorithm implement.
 */

# ifndef __UFS_H__
# define __UFS_H__

# include <vector>

/* NOTE: the index is from 0 to n - 1 */
class ufSet{
private:
  std:: vector<int> father;

  int getFather(int x);

public:
  int n;
  ufSet(int _n);

  bool isUnion(int x, int y);
  void letUnion(int x, int y);
};

# endif // __UFS_H__
