using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Node.h"
#include "Graph.h"
#include "OriginNode.h"
#include "OriginGraph.h"
#include "Algorithms.h"
#include "SimpleGame.h"
#include "HarderGame.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>


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
			currentNode->printCurrent();
			cout << "It has " << currentNode->neigbours.size() << " neighbours System can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				currentNode->printCurrent();
				cout << "V" << currentNode->neigbours[i]->index << " ,";
				if (!currentNode->neigbours[i]->Good && currentNode->neigbours[i]->distance_from_notP < currentNode->distance_from_notP)
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

void doGPandGFP()
{
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
	/*vector<Node*> nodesG;
	for (int i = 0; i < 6; i++)
	{
		Node* v = new Node(i, i < 4);
		nodesG.push_back(v);
	}
	nodesG[0]->addNeighbour(nodesG[1], false);
	nodesG[0]->addNeighbour(nodesG[3], true);
	nodesG[1]->addNeighbour(nodesG[2], true);
	nodesG[1]->addNeighbour(nodesG[3], true);
	nodesG[1]->addNeighbour(nodesG[3], false);
	nodesG[2]->addNeighbour(nodesG[2], false);
	nodesG[2]->addNeighbour(nodesG[2], true);
	nodesG[3]->addNeighbour(nodesG[4], false);
	nodesG[4]->addNeighbour(nodesG[5], false);
	*/
	int size = 0, num = 0, secNum = 0, i;
	ifstream file("InputGraph.txt", ios::in | ios::binary | ios::ate);
	if (!file.is_open())
	{
		cout << "couldn't open the file , maybe its not in the directory of the exe? the name shoud be \"InputGraph.txt\"" << endl;
		return ;
	}
	size = file.tellg();
	char* InGraph = new char[size];
	file.seekg(0, ios::beg);
	file.read(InGraph, size);
	file.close();

	bool flagNumNodes = 0, flagPnodes = 0, flagSys = 0, flagEnv = 0;
	vector<Node*> nodes;
	Node* v;
	for (i = 0; i < size; i++)
	{
		if (flagNumNodes == 0)
		{
			if (isdigit(InGraph[i]))
			{
				num = atoi(&InGraph[i]);
				flagNumNodes = true;

				for (int k = 0; k < num; k++)
				{
					v = new Node(k, false);
					nodes.push_back(v);
				}
			}
		}
		else
		{
			if (flagPnodes == false)
			{
				if (isdigit(InGraph[i]))
				{
					while (InGraph[i] != 'S')
					{
						if (isdigit(InGraph[i]))
						{
							num = atoi(&InGraph[i]);
							nodes[num - 1]->p = true;
							nodes[num - 1]->Good = true;
						}
						i++;
					}
					flagPnodes = true;
				}
			}
			else
			{
				if (flagSys == false)
				{
					//here we need to take in pairs as arches.

					while (InGraph[i] != 'E')
					{
						if (isdigit(InGraph[i]))
						{
							num = atoi(&InGraph[i]);
							secNum = atoi(&InGraph[i + 2]);
							nodes[num - 1]->addNeighbour(nodes[secNum - 1], true);
							i = i + 2;
						}
						i++;
					}
					flagSys = true;

				}
				else
				{
					if (flagEnv == false)
					{
						while (InGraph[i] != 'E')
						{
							if (isdigit(InGraph[i]))
							{
								num = atoi(&InGraph[i]);
								secNum = atoi(&InGraph[i + 2]);
								nodes[num - 1]->addNeighbour(nodes[secNum - 1], false);
								i = i + 2;
							}
							i++;
						}
						flagEnv = true;
					}
					else
						break;
				}

			}
		}
	}

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
	return;
}



int main()
{
	int num=0, size;
	while (num != -1)
	{
		cout << "What do you want to play?" << endl << "1. 2 White knights and a Black knight. ( G(p) )" << endl << "2. 2 White knights and a black knight responding! ( G(F(p)) )" << endl << "3. Read an input Graph and do G(p) and G (F (p)) on it " << endl << "Press -1 to exit the games " << endl;
		cin >> num;
		switch (num)
		{
		case 1:
			cout << "what size of board do you want? " << endl;
			cin >> size;
			PlaySimpleGame(size);
			break;
		case 2:
			cout << "what size of board do you want? " << endl;
			cin >> size;
			PlayHarderGame(size);
			break;
		case 3:
			doGPandGFP();
			break;
		case -1:
			cout << "OK FINE !! now we are done." << endl;
			break;
		default:
			cout << " you little rebel , Now this game is ended." << endl;
			break;
		}
	}
	int d;
	cin >> d;
}