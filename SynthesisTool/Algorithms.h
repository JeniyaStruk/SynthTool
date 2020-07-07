#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "OriginNode.h"
#include "OriginGraph.h"
#include <ctype.h>
#include <ctime>
/*
	makes a graph from the original graph , but the new graph has devided nodes.
	nodes that its the enviroments turn when we are at them , and nodes that its the System tun when we are at them.
*/
OriginGraph* makeASeperatedGraph(Graph& g)
{
	vector<OriginNode*> newNodes;
	OriginNode* q0 = NULL;
	for (size_t i = 0; i < g.nodes.size(); i++)
	{
		OriginNode* v1 = new OriginNode(g.nodes[i], true);
		OriginNode* v2 = new OriginNode(g.nodes[i], false);
		if (g.nodes[i] == g.q0)
			q0 = v1;

		newNodes.push_back(v1);
		newNodes.push_back(v2);

	}
	OriginNode* v1;
	for (size_t i = 0; i < g.nodes.size(); i++)
	{
		vector<Node*> EnvNeig = g.nodes[i]->envNeighbours;
		for (size_t k = 0; k < EnvNeig.size(); k++)
		{
			int t = (EnvNeig[k]->index * 2 + 1);
			v1 = newNodes.at(t);
			newNodes[(2 * i)]->addOriginNeighbour(v1);
		}

		vector<Node*> SysNeig = g.nodes[i]->sysNeighbours;
		for (size_t j = 0; j < SysNeig.size(); j++)
		{
			int t = (SysNeig[j]->index * 2);
			v1 = newNodes.at(t);
			newNodes.at((2 * i) + 1)->addOriginNeighbour(v1);
		}

	}

	OriginGraph* newG = new OriginGraph(newNodes, q0);
	return newG;
}

/*
	addtion of System nodes that have at least one member entering to the group.
	or Env nodes that have only group members.
*/
void cpre_1(OriginGraph& g, vector<OriginNode*> group)
{
	for (size_t i = 0; i < g.nodes.size(); i++)
	{
		g.nodes[i]->Good = false;
		g.nodes[i]->in_cpre_1 = false;
	}
	for (size_t i = 0; i < group.size(); i++)
	{
		group[i]->Good = true;
	}
	for (size_t i = 0; i < g.nodes.size(); i++)
	{
		if (g.nodes[i]->originArch == Sys)
		{
			vector<OriginNode*> neig = g.nodes[i]->getNeighbours();
			if (neig.size() != 0)
			{
				bool flag = true;
				for (size_t j = 0; j < neig.size(); j++)
				{
					if (neig[j]->Good == false)
						flag = false;
				}
				if (flag)
					g.nodes[i]->in_cpre_1 = true;
			}
		}
		else
		{
			vector<OriginNode*> neig = g.nodes[i]->getNeighbours();
			for (size_t k = 0; k < neig.size(); k++)
				if (neig[k]->Good == true)
				{
					g.nodes[i]->in_cpre_1 = true;
					break;
				}
		}
	}
}

bool alwaysP(OriginGraph& g)
{
	int oldSize = 0;
	vector<OriginNode*> good;
	int dist_f_np = 0;
	size_t vSize = g.nodes.size();

	//determine who is the initial group
	for (size_t i = 0; i < vSize; i++)
	{
		OriginNode* n = g.nodes[i];
		if (n->p == true)
		{
			good.push_back(n);
		}
		else
			n->distance_from_notP = 0;

	}
	//starting the loop uptil fixed point
	int newSize = good.size();
	while (oldSize != newSize && g.q0->Good == true)
	{
		oldSize = newSize;
		dist_f_np++;
		cpre_1(g, good);
		size_t sizeG = good.size();
		for (size_t k = 0; k < sizeG; k++)
			if (good[k]->in_cpre_1 == false)
			{
				good[k]->distance_from_notP = dist_f_np;
				good.erase(good.begin() + k);
				sizeG--;
				k--;
			}
		newSize = good.size();
	}
	return g.q0->Good;
}

bool alwaysEventuallyP(OriginGraph& g)
{
	int oldSize = 0;
	vector<OriginNode*> group = g.nodes;
	vector<OriginNode*> l;
	size_t oldSizeL = 0, newSizeL;
	size_t oldSizeG = 0, newSizeG;
	newSizeG = group.size();
	while (oldSizeG != newSizeG)
	{
		oldSizeG = newSizeG;
		
		cpre_1(g, group);

		//removal of non p nodes.
		size_t sizeG = group.size();
		for (size_t k = 0; k < sizeG; k++)
			if (!(group[k]->p == true && group[k]->in_cpre_1))
			{
				group.erase(group.begin() + k);
				sizeG--;
				k--;
			}
		l = group;
		//now after initializion l as p & core_1 (g) we do a fixed point of l or cpre_1(l)
		oldSizeL = 0;
		newSizeL = l.size();
		int dist_f_np = 0;
		while (oldSizeL != newSizeL)
		{
			oldSizeL = newSizeL;
			dist_f_np++;
			cpre_1(g, l);
			for (size_t k = 0; k < g.nodes.size(); k++)
			{
				if ((g.nodes[k]->in_cpre_1) && (!(g.nodes[k]->Good)))
				{
					g.nodes[k]->distance_from_notP = dist_f_np;
					l.push_back(g.nodes[k]);
				}
			}
			newSizeL = l.size();
		}
		group = l;
		newSizeG = group.size();
	}
	if (g.q0->Good)
		return true;
	else
		return false;
}