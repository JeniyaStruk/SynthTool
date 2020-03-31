#pragma once

#include "Node.h"
#include <vector>
#include <iostream>
using namespace std;

class Graph
{
public:
	vector<Node*> nodes;
	Node* q0;
	Graph(vector<Node*> nodes, Node* q0)
	{
		this->nodes = nodes;
		this->q0 = q0;
	}
	vector<Node*> getNodesWithP()
	{
		vector <Node*> nodesWithP;
		for (size_t i = 0; i < nodes.size(); i++)
			if (nodes[i]->p)
				nodesWithP.push_back(nodes[i]);
		return nodesWithP;
	}

	void printWholeGraph()
	{
		size_t j, i;
		cout << "This is a Graph print:" << endl;
		cout << "q0: v" << q0->index << endl;

		for (i = 0; i < nodes.size(); i++)
		{
			cout << "These are v" << i << " system neighbours" << endl;
			vector<Node*> neig = nodes[i]->sysNeighbours;
			for (j = 0; j < neig.size(); j++)
			{
				cout << "v" << neig[j]->index << ", ";
			}
			cout << endl;
			cout << "These are v" << i << " Enviroment neighbours" << endl;
			neig = nodes[i]->envNeighbours;
			for (j = 0; j < neig.size(); j++)
			{
				cout << "v" << neig[j]->index << ", ";
			}
			cout << endl << endl;
		}
	}
};