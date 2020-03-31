using namespace std;
#include <stdio.h>
#include <vector>
#include "Node.h"
#include "Graph.h"
#include "OriginNode.h"
#include "OriginGraph.h"


/*
	makes a graph from the original graph , but the new graph has devided nodes.
	nodes that its the enviroments turn when we are at them , and nodes that its the System tun when we are at them.
*/
OriginGraph* makeASeperatedGraph(Graph& g)
{
	vector<OriginNode*> newNodes;

	for (size_t i = 0; i < g.nodes.size(); i++)
	{
		OriginNode* v1 = new OriginNode(g.nodes[i], true);
		OriginNode* v2 = new OriginNode(g.nodes[i], false);

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
			v1 = newNodes[t];
			newNodes[(2 * i)]->addOriginNeighbour(v1);
		}

		vector<Node*> SysNeig = g.nodes[i]->sysNeighbours;
		for (size_t j = 0; j < SysNeig.size(); j++)
		{
			int t = (SysNeig[j]->index * 2);
			v1 = newNodes[t];
			newNodes[(2 * i) + 1]->addOriginNeighbour(v1);
		}

	}

	OriginGraph* newG = new OriginGraph(newNodes, newNodes[0]);
	return newG;
}


/*
	addtion of System nodes that have at least one member entering to the group.
	or Env nodes that have only group members.
*/
void cpre_1(OriginGraph &g, vector<OriginNode*> group)
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
	size_t vSize = g.nodes.size();

	//determine who is the initial group
	for (size_t i = 0; i < vSize; i++)
	{
		OriginNode* n = g.nodes[i];
		if (n->p == true)
		{
			good.push_back(n);
		}

	}
	//starting the loop uptil fixed point
	int newSize = good.size();
	while (oldSize != newSize && g.q0->Good == true)
	{
		oldSize = newSize;
		cpre_1(g, good);
		size_t sizeG = good.size();
		for (size_t k = 0; k < sizeG; k++)
			if (good[k]->in_cpre_1 == false)
			{
				good.erase(good.begin() + k);
				sizeG--;
				k--;
			}
		newSize = good.size();
	}
	return g.q0->Good;
}

bool alwaysEventuallyP(OriginGraph &g)
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
			if (group[k]->p == false||(group[k]->Good&&!group[k]->in_cpre_1))
			{
				group.erase(group.begin() + k);
				sizeG--;
				k--;
			}
		l = group;
		//now after initializion l as p & core_1 (g) we do a fixed point of l or cpre_1(l)
		oldSizeL = l.size();
		newSizeL = 0;
		while (oldSizeL != newSizeL)
		{
			oldSizeL = newSizeL;
			cpre_1(g, l);
			for (size_t k = 0; k < g.nodes.size(); k++)
				if (g.nodes[k]->in_cpre_1 && !g.nodes[k]->Good)
					l.push_back(g.nodes[k]);
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


void tryContradictTrue(OriginGraph &g, bool GP)
{
	int num = 0;
	bool flag, EnvTurn = true;
	OriginNode* currentNode;
	currentNode = g.q0;

	bool condition1;
	if (GP)
		condition1 = num != -1 && currentNode->p == true;
	else
		condition1 = num != -1 && currentNode->Good == true;
	while (condition1)
	{
		if (!EnvTurn)
		{
			cout << "Current node is V" << currentNode->index << endl;
			cout << "It has " << currentNode->neigbours.size() << " neighbours System can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << " ,";
				if (currentNode->neigbours[i]->Good)
					num = i;
			}
			cout << endl << "Sys chooses V" << currentNode->neigbours[num]->index << endl;
			currentNode = currentNode->neigbours[num];
			EnvTurn = true;
		}
		else
		{
			flag = false;
			cout << "Current node is V" << currentNode->index << endl;
			cout << "It has " << currentNode->neigbours.size() << " neighbours You(Enviroment) can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << " ,";
			}
			cout << endl << "Please press the index of the node you want to go to , if you give up , choose -1" << endl;
			cin >> num;
			size_t size = currentNode->neigbours.size();
			for (size_t i = 0; i < size; i++)
			{

				if (num == currentNode->neigbours[i]->index)
				{
					flag = true;
					currentNode = currentNode->neigbours[i];
					cout << endl << "Env chooses V" << currentNode->index << "and it p value is " << currentNode->p << endl;
					i = size;
					EnvTurn = false;
				}
			}
			if (flag == false)
			{
				if (num != -1)
					cout << "Please choose a node that is a neighbour , or choose -1 to quit" << endl;
			}
		}
		if (GP)
			condition1 = num != -1 && currentNode->p == true;
		else
			condition1 = num != -1 && currentNode->Good == true;

	}
	if (GP)
	{
		if (currentNode->p == false)
			cout << "Our Always P algorithm is wrong , sorry to Disappoint" << endl;
		else
			cout << "Thanks for trying !" << endl;
	}
	else
	{
		if (currentNode->Good == false)
			cout << "Our Always Eventually P algorithm is wrong , sorry to Disappoint from this node i cant guarentee i can go to a p node." << endl;
		else
			cout << "Thanks for trying !" << endl;
	}
}


void tryContradictFalse(OriginGraph &g, bool GP)
{
	int num = 0;
	bool flag, EnvTurn = true;
	OriginNode* currentNode;
	currentNode = g.q0;
	bool condition1;
	if (GP)
		condition1 = num != -1 && currentNode->p == true;
	else
		condition1 = num != -1 && currentNode->Good == true;
	while (condition1)
	{
		if (EnvTurn)
		{
			cout << "Current node is V" << currentNode->index << endl;
			cout << "It has " << currentNode->neigbours.size() << " neighbours System can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << " ,";
				if (!currentNode->neigbours[i]->Good)
					num = i;
			}
			cout << endl << "Env chooses V" << currentNode->neigbours[num]->index << endl;
			currentNode = currentNode->neigbours[num];
			EnvTurn = false;
		}
		else
		{
			flag = false;
			cout << "Current node is V" << currentNode->index << endl;
			cout << "It has " << currentNode->neigbours.size() << " neighbours You(System) can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << " ,";
			}
			cout << endl << "Please press the index of the node you want to go to , if you give up , choose -1" << endl;
			cin >> num;
			size_t size = currentNode->neigbours.size();
			for (size_t i = 0; i < size; i++)
			{
				if (num == currentNode->neigbours[i]->index)
				{
					flag = true;
					cout << endl << "Sys chooses V" << currentNode->neigbours[i]->index << endl;
					currentNode = currentNode->neigbours[i];
					i = size;
					EnvTurn = false;
				}
			}
			if (flag == false)
			{
				if (num != -1)
					cout << "Please choose a node that is a neighbour , or choose -1 to quit" << endl;
			}
		}
	}
	if (GP)
		condition1 = (currentNode->p == false);
	else
		condition1 = (currentNode->Good == false);

	if (condition1)
		if (GP)
			cout << "This node's P value is false ! " << endl << "Thank you for trying!" << endl;
		else
			cout << "Our Always Eventually P algorithm is wrong , sorry to Disappoint from this node i cant guarentee i can go to a p node." << endl;
	else
		cout << "Thanks for trying !" << endl;
}


int main()
{
	int size = 0, num = 0, i;
	/*while (size <= 0)
	{
		cout << "How many nodes do you want in your graph? (must be above 0)" << endl;
		cin >> size;
	}
	vector<Node*> nodes;
	for (i = 0; i < size; i++)
	{
		Node* v = new Node(i, false);
		nodes.push_back(v);
	}
	while (num != -1)
	{
		cout << "Which nodes will have P in them? (0-" << size - 1 <<")" << endl << "choose one and then press enter until you want to stop and then press -1" << endl;
		cin >> num;
		if (0 <= num && num < size)
			nodes[num]->p=true;
	}

	for (i = 0; i < size; i++)
	{
		num = 0;
		while (num != -1)
		{
			cout << "which node do you want to connect to node " << i << "?" << endl;
			cout << "to finish adding nodes to node " << i << " please enter -1" << endl;
			cin >> num;
			if (0 <= num && num < size)
			{
				cout << "do you want it to be a Sys arch or an Env arc , for System put 1 , Enviroment put 0" << endl;
				cin >> type;
				if (type == 1)
					nodes[i]->addNeighbour(nodes[num], true);
				else
					if (type == 0)
						nodes[i]->addNeighbour(nodes[num], false);
					else
						cout << "please choose only 1 or 0" << endl;
			}
		}
	}
	*/

	vector<Node*> nodes;
	for (i = 0; i < 6; i++)
	{
		Node* v = new Node(i, i < 4);
		nodes.push_back(v);
	}
	nodes[0]->addNeighbour(nodes[1], false);
	nodes[0]->addNeighbour(nodes[3], true);
	nodes[1]->addNeighbour(nodes[2], true);
	nodes[1]->addNeighbour(nodes[3], true);
	nodes[1]->addNeighbour(nodes[3], false);
	nodes[2]->addNeighbour(nodes[2], false);
	nodes[2]->addNeighbour(nodes[2], true);
	nodes[3]->addNeighbour(nodes[4], false);
	nodes[4]->addNeighbour(nodes[5], false);


	Graph g(nodes, nodes[0]);
	OriginGraph* newG = makeASeperatedGraph(g);

	if (alwaysP(*newG))
	{
		cout << " This Graph Has the Always P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cin >> num;
		if (num == 1)
		{
			tryContradictTrue(*newG, true);
		}
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				cout << "You pressed the wrong option, Good Bye" << endl;
	}
	else
	{
		cout << " This Graph doesnt have the Always P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cin >> num;
		if (num == 1)
		{
			tryContradictFalse(*newG, true);
		}
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				cout << "You pressed the wrong option, Good Bye" << endl;
	}

	if (alwaysEventuallyP(*newG))
	{
		cout << " This Graph Has the Always Eventually P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cin >> num;
		if (num == 1)
		{
			tryContradictTrue(*newG, false);
		}
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				cout << "You pressed the wrong option, Good Bye" << endl;
	}
	else
	{
		cout << " This Graph doesnt have the Always Eventually P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cin >> num;
		if (num == 1)
		{
			tryContradictFalse(*newG, false);
		}
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				cout << "You pressed the wrong option, Good Bye" << endl;
	}

	int d;
}