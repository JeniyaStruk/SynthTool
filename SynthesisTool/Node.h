#pragma once

#include <vector>
class Node
{
public:
	int index;
	vector<Node*> envNeighbours;
	vector<Node*> sysNeighbours;
	bool p;
	bool Good;
	bool in_cpre_1;

	Node() {}
	Node(int index, bool prop)
	{
		this->index = index;
		p = prop;
		Good = p;
		in_cpre_1 = false;
	}
	void addNeighbour(Node* n, bool sys)
	{
		if (sys)
			sysNeighbours.push_back(n);
		else
			envNeighbours.push_back(n);
	}
	bool hasEnvNeighbour(Node* n)
	{
		int i = 0;
		int size = envNeighbours.size();
		for (i = 0; i < size; i++)
		{
			if (envNeighbours[i]->index == n->index)
				return true;
		}
		return false;
	}
	bool hasSysNeighbour(Node* n)
	{
		for (size_t i = 0; i < sysNeighbours.size(); i++)
			if (sysNeighbours[i]->index == n->index)
				return true;
		return false;
	}
	vector<Node*> getNeighbours(bool sys)
	{
		if (sys)
			return sysNeighbours;
		else
			return envNeighbours;
	}
};
