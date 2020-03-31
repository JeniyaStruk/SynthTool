#pragma once
#include "OriginNode.h"

class OriginGraph
{
public:
	vector<OriginNode*> nodes;
	OriginNode* q0;
	OriginGraph(vector<OriginNode*> nodes, OriginNode* q0)
	{
		this->nodes = nodes;
		this->q0 = q0;
	}
	vector<OriginNode*> getNodesWithP()
	{
		vector <OriginNode*> nodesWithP;
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
				cout << "v" << neig[j]->index << ", ";
			cout << endl;
			cout << "These are v" << i << " Enviroment neighbours" << endl;
			neig = nodes[i]->envNeighbours;
			for (j = 0; j < neig.size(); j++)
				cout << "v" << neig[j]->index << ", ";
			cout << endl << endl;
		}
	}
};