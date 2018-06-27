/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is for the KD Tree to replace the Voronoi algorithm
 */

# ifndef __KD_TREE_H__
# define __KD_TREE_H__

# include <vector>
# include <iostream>

# include "../graph.h"

# define INF_VALUE 1e9

/* Node on K-D Tree */
template <class valType>
class kdNode {
public:
	kdNode<valType> *lch, *rch;
	valType rangeL[2], rangeR[2];
	Point<valType> point;

	kdNode(Point<valType> &inputPoint): point(inputPoint) {
		lch = rch = NULL;
		for(int i = 0; i < 2; ++ i) rangeL[i] = inputPoint.d(i);
		for(int i = 0; i < 2; ++ i) rangeR[i] = inputPoint.d(i);
	}
	valType evaluate(Point<valType> &qPoint);
	void updateStatus();
};

/* Point comparer */
template <class valType, int dim>
struct PCOMP {
	bool operator () (Point<valType> &pA, Point<valType> &pB) {
		return pA.d(dim) < pB.d(dim);
	}
};

/* K-D Tree */
template <class valType>
class kdTree {
private:
	std:: pair<valType, Point<valType> > answer;
	kdNode<valType> *root;
	void nodeFree(kdNode<valType> *curNode);
	void treeQuery(kdNode<valType> *curNode, Point<valType> &qPoint);
	void treeBuild(kdNode<valType>* &curNode, int l, int r, int curDim, std:: vector<Point<valType> > &vPoints);

public:
	kdTree(std:: vector<Point<valType> > &vPoints);
	~kdTree();
	std:: pair<valType, Point<valType> > query(Point<valType> &qPoint);
};

# endif