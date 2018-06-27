/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is for the KD Tree to replace the Voronoi algorithm
 */

# include <cassert>
# include <iostream>
# include <algorithm>

# include "kdTree.h"

template class kdTree<float>;
template class kdTree<double>;

/* Evaluating the min distance */
template <class valType>
valType kdNode<valType>:: evaluate(Point<valType> &qPoint) {
	valType ret = 0;
	for(int i = 0; i < 2; ++ i) ret += std:: max((valType)0.0, rangeL[i] - qPoint.d(i));
	for(int i = 0; i < 2; ++ i) ret += std:: max((valType)0.0, qPoint.d(i) - rangeR[i]);
	return ret;
}

/* Updating the status */
template <class valType>
void kdNode<valType>:: updateStatus() {
	for(int i = 0; i < 2; ++ i) {
		if(lch) {
			rangeL[i] = std:: min(rangeL[i], lch -> rangeL[i]);
			rangeR[i] = std:: max(rangeR[i], lch -> rangeR[i]);
		}
		if(rch) {
			rangeL[i] = std:: min(rangeL[i], rch -> rangeL[i]);
			rangeR[i] = std:: max(rangeR[i], rch -> rangeR[i]);
		}
	}
}

/* On-tree Query */
template <class valType>
void kdTree<valType>:: treeQuery(kdNode<valType> *curNode, Point<valType> &qPoint) {
	assert(curNode != NULL);

	valType dist = distance(curNode -> point, qPoint);
	if(dist < answer.first) answer = std:: make_pair(dist, curNode -> point);
	valType evaVL = INF_VALUE, evaVR = INF_VALUE;
	if(curNode -> lch) evaVL = curNode -> lch -> evaluate(qPoint);
	if(curNode -> rch) evaVR = curNode -> rch -> evaluate(qPoint);
	if(evaVL < evaVR) {
		if(evaVL < answer.first) this -> treeQuery (curNode -> lch, qPoint);
		if(evaVR < answer.first) this -> treeQuery (curNode -> rch, qPoint);
	} else {
		if(evaVR < answer.first) this -> treeQuery (curNode -> rch, qPoint);
		if(evaVL < answer.first) this -> treeQuery (curNode -> lch, qPoint);
	}
}

/* On-tree Build */
template <class valType>
void kdTree<valType>:: treeBuild(kdNode<valType>* &curNode, int l, int r, int curDim, std:: vector<Point<valType> > &vPoints) {
	int mid = (l + r) >> 1;

	if(curDim == 0) std:: nth_element(&vPoints[l], &vPoints[mid], &vPoints[r + 1], PCOMP<valType, 0> ());
	if(curDim == 1) std:: nth_element(&vPoints[l], &vPoints[mid], &vPoints[r + 1], PCOMP<valType, 1> ());
	assert(curDim == 1 || curDim == 0);

	curNode = new kdNode<valType> (vPoints[mid]);
	if(l < mid) this -> treeBuild(curNode -> lch, l, mid - 1, curDim ^ 1, vPoints);
	if(r > mid) this -> treeBuild(curNode -> rch, mid + 1, r, curDim ^ 1, vPoints);

	curNode -> updateStatus();
}

/* Constructor */
template <class valType>
kdTree<valType>:: kdTree(std:: vector<Point<valType> > &vPoints): answer(INF_VALUE, Point<valType> (0, 0)) {
	assert(vPoints.size() > 0);

	root = NULL;
	this -> treeBuild(root, 0, vPoints.size() - 1, 0, vPoints);
}

/* Free node memory */
template <class valType>
void kdTree<valType>:: nodeFree(kdNode<valType> *curNode) {
	assert(curNode != NULL);
	if(curNode -> lch != NULL) this -> nodeFree(curNode -> lch);
	if(curNode -> rch != NULL) this -> nodeFree(curNode -> rch);
	delete curNode;
}

/* Destrutor */
template <class valType>
kdTree<valType>:: ~kdTree() {
	this -> nodeFree(root);
}

/* Query function */
template <class valType>
std:: pair<valType, Point<valType> > kdTree<valType>:: query(Point<valType> &qPoint) {
	answer.first = INF_VALUE;
	this -> treeQuery(root, qPoint);
	return answer;
}