#pragma once
#ifndef ORIGIN_N
#include "Node.h"
#include <vector>
#include <iostream>
#include <iostream>
using namespace std;
enum archLeadinToNode { Sys = 0, Env = 1 };

class OriginNode :public Node
{
public:
	vector<OriginNode*> neigbours;
	archLeadinToNode originArch;
	int dist;

	OriginNode(Node* node, bool cameFromSys)
	{
		if (cameFromSys)
			originArch = Sys;
		else
			originArch = Env;
		this->index = node->index;
		this->p = node->p;
		this->Good = node->Good;
		dist = -1;
	}

	void addOriginNeighbour(OriginNode *n)   //here gets a zero node ERROR
	{
		bool flag = true;
		for (size_t i = 0; i < neigbours.size(); i++)
			if (n->index == neigbours[i]->index&&n->originArch == neigbours[i]->originArch)
				flag = false;
		if (flag)
			neigbours.push_back(n);
	}

	vector<OriginNode*> getNeighbours()
	{
		return neigbours;
	}
	bool hasNeighbour(OriginNode *n)
	{
		for (size_t i = 0; i < neigbours.size(); i++)
			if (n->index == neigbours[i]->index)
				return true;
		return false;
	}
};
#endif