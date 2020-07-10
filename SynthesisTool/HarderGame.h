#ifndef HARDER_GAME

#include <stdio.h>
#include <vector>
#include "Node.h"
#include "Graph.h"
#include "OriginNode.h"
#include "OriginGraph.h"
#include "Algorithms.h"
#include <iostream>
#include <chrono> 
using namespace std::chrono;


void tryContradictTheHarderGameTrue(OriginGraph& g, Graph& graph, bool GP, bool randomize_run)
{

	int num = 0, num_of_moves = 1;
	bool flag, EnvTurn = true;
	OriginNode* currentNode;
	currentNode = g.q0;
	boardState* current;
	bool condition1;
	if (randomize_run)
	{
		cout << "how many randomized moves do you want to see?" << endl;
		cin >> num_of_moves;
	}
	if (GP)
		condition1 = num != -1 && currentNode->p == true;
	else
		condition1 = num != -1 && currentNode->Good == true;
	while (condition1 && num_of_moves > 0)
	{
		if (!EnvTurn)
		{
			cout << "==============================================================================================" << endl;
			cout << "Current node is V" << currentNode->index << endl;
			current = (boardState*)graph.nodes[currentNode->index];
			current->printCurrent();
			cout << "It has " << currentNode->neigbours.size() << " neighbours System can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				current->printCurrent();

				if (currentNode->neigbours[i]->Good && currentNode->neigbours[i]->distance_from_notP < currentNode->distance_from_notP)
					num = i;
			}
			if (randomize_run)
				num_of_moves--;
			cout << endl << "Sys chooses V" << currentNode->neigbours[num]->index << endl;
			current = (boardState*)graph.nodes[currentNode->neigbours[num]->index];
			current->printCurrent();
			currentNode = currentNode->neigbours[num];
			EnvTurn = true;
		}
		else
		{
			flag = false;
			cout << "==============================================================================================" << endl;
			cout << "Current node is V" << currentNode->index << endl;
			current = (boardState*)graph.nodes[currentNode->index];
			current->printCurrent();
			cout << "It has " << currentNode->neigbours.size() << " neighbours You(Enviroment) can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				current->printCurrent();
			}
			cout << endl << "Please press the index of the node you want to go to , if you give up , choose -1" << endl;
			if (randomize_run)
			{
				num = rand() % currentNode->neigbours.size();
				num = currentNode->neigbours[num]->index;
			}
			else
				cin >> num;
			size_t size = currentNode->neigbours.size();
			for (size_t i = 0; i < size; i++)
			{

				if (num == currentNode->neigbours[i]->index)
				{
					flag = true;
					currentNode = currentNode->neigbours[i];
					cout << endl << "Env chooses V" << currentNode->index << endl;
					current = (boardState*)graph.nodes[currentNode->index];
					current->printCurrent();
					i = size;
					EnvTurn = false;
					if (randomize_run)
						num_of_moves--;
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
	if (randomize_run && num_of_moves <= 0)
	{
		cout << "Random Sequence has ended ! " << endl;
		return;
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

void tryContradictTheHarderGameFalse(OriginGraph& g, Graph& graph, bool GP)
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
			cout << "==============================================================================================" << endl;
			currentNode->printCurrent();
			boardState* current = (boardState*)graph.nodes[currentNode->index];
			current->printCurrent();
			cout << "It has " << currentNode->neigbours.size() << " neighbours Environment can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				//currentNode->printCurrent();
				//cout << "V" << currentNode->neigbours[i]->index << endl;
				//current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				//current->printCurrent();
				if (!currentNode->neigbours[i]->Good && currentNode->neigbours[i]->distance_from_notP < currentNode->distance_from_notP)
					num = i;
			}
			if (currentNode->neigbours.size() == 0)
			{
				cout << "There are no nodes for Env to move on to! " << endl;
				cout << "There go System HAS WON!! " << endl;
				break;

			}
			else
			{
				cout << endl << "Env chooses V" << currentNode->neigbours[num]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[num]->index];
				current->printCurrent();
				currentNode = currentNode->neigbours[num];
				EnvTurn = false;
			}
		}
		else
		{
			flag = false;
			cout << "==============================================================================================" << endl;
			cout << "Current node is V" << currentNode->index << endl;
			boardState* current = (boardState*)graph.nodes[currentNode->index];
			current->printCurrent();
			cout << "It has " << currentNode->neigbours.size() << " neighbours You(System) can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				current->printCurrent();
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
					current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
					current->printCurrent();
					currentNode = currentNode->neigbours[i];
					i = size;
					EnvTurn = true;
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
typedef std::map<std::string, boardState*> TheMap;
typedef std::pair<std::string, boardState*> ThePair;

void PlayHarderGame(int size)
{
	cout << "-----------------------------------------------------------------" << endl;
	cout << "We will start calculating the Game." << endl;
	long int wholeSize = size * size;
	vector<Node*>* all_states = new vector<Node*>();
	auto start = high_resolution_clock::now();
	int index = 0;
	int i = 0, j = 1, k = 2;
	TheMap myMap;
	for (i = 0; i < wholeSize; i++)
		if (i != j && i != k)
			for (j = 0; j < wholeSize; j++)
				if (j != i && j != k)
					for (k = 0; k < wholeSize; k++)
						if (k != i && k != j)
						{
							//cout << " i = " << i << " j = " << j << " k = " << k << endl;
							boardState* new_state = new boardState(index, false, size);
							index++;
							new_state->white_player_1 = i;
							new_state->white_player_2 = j;
							new_state->black_player = k;
							all_states->push_back(new_state);
							string str = to_string(i);
							str += ","; str += to_string(j); str += ","; str += to_string(k);
							myMap.insert(ThePair(str, new_state));
						}
	//now lets connect nodes with Sys arches (white moves)


	bool warningFlag = 0;
	Node* q0 = NULL;

	for (size_t i_n = 0; i_n < all_states->size(); i_n++)
	{
		//get white pawns cordinates
		boardState* current = (boardState*)all_states->at(i_n);
		int white_1 = current->white_player_1;
		int white_1_x = white_1 % size;
		int white_1_y = white_1 / size;


		//coordinates of white_2
		int white_2 = current->white_player_2;
		int white_2_x = white_2 % size;
		int white_2_y = white_2 / size;


		//get blacks coordinates ( to make sure it doesnt move) 
		int black_1 = current->black_player;
		int black_1_x = black_1 % size;
		int black_1_y = black_1 / size;

		if (q0 == NULL && white_1_x == 0 && white_1_y == 0 && white_2_x == 0 && white_2_y == size - 1 && black_1_x == size - 1 && black_1_y == size - 1)
			q0 = all_states->at(i_n);


		boardState* neigState;
		string str = to_string(white_1); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1);
		if (white_1_x != 0 && (white_1 != white_2 + 1) && (white_1 != black_1 + 1))
		{
			str = to_string(white_1 - 1); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();
		}
		if ((white_1_x != size - 1) && (white_1 != white_2 - 1) && (white_1 != black_1 - 1))
		{
			str = to_string(white_1 + 1); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();

		}
		if (white_1_y != 0 && (white_1 != white_2 + size) && (white_1 != black_1 + size))
		{
			str = to_string(white_1 - size); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();
		}
		if (white_1_y != size - 1 && (white_1 != white_2 - size) && (white_1 != black_1 - size))
		{
			str = to_string(white_1 + size); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();
		}

		if (white_2_x != 0 && (white_2 != white_1 + 1) && (white_2 != black_1 + 1))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2 - 1); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();
		}
		if (white_2_x != size - 1 && (white_2 != white_1 - 1) && (white_2 != black_1 - 1))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2 + 1); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();
		}
		if (white_2_y != 0 && (white_2 != white_1 + size) && (white_2 != black_1 + size))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2 - size); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();
		}
		if (white_2_y != size - 1 && (white_2 != white_1 - size) && (white_2 != black_1 - size))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2 + size); str += ","; str += to_string(black_1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, true);
			//current->printCurrent();
			//cout << "connected with sys Arch (white)" << endl;
			//neigState->printCurrent();
		}


		if (black_1_x != 0 && (black_1 != white_1 + 1) && (black_1 != white_2 + 1))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1 - 1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, false);
			//current->printCurrent();
			//cout << "connected with Env Arch (black)" << endl;
			//neigState->printCurrent();
		}
		if (black_1_x != size - 1 && (black_1 != white_1 - 1) && (black_1 != white_2 - 1))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1 + 1);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, false);
			//current->printCurrent();
			//cout << "connected with Env Arch (black)" << endl;
			//neigState->printCurrent();
		}
		if (black_1_y != 0 && (black_1 != white_1 + size) && (black_1 != white_2 + size))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1 - size);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, false);
			//current->printCurrent();
			//cout << "connected with Env Arch (black)" << endl;
			//neigState->printCurrent();
		}
		if (black_1_y != size - 1 && (black_1 != white_1 - size) && (black_1 != white_2 - size))
		{
			str = to_string(white_1); str += ","; str += to_string(white_2); str += ","; str += to_string(black_1 + size);
			neigState = myMap[str];
			all_states->at(i_n)->addNeighbour(neigState, false);
			//current->printCurrent();
			//cout << "connected with Env Arch (black)" << endl;
			//neigState->printCurrent();
		}
	}

	//adding all states that should connect to the winning state.
	int places[4] = { 0,size - 1,(size) * (size - 1),(size) * (size)-1 };
	boardState* next_state;
	size_t size_of_states = all_states->size();
	for (size_t i = 0; i < size_of_states; i++)
	{
		boardState* current = (boardState*)all_states->at(i);

		//get white pawns cordinates
		int white_1 = current->white_player_1;
		int white_1_x = white_1 % size;
		int white_1_y = white_1 / size;

		//coordinates of white_2
		int white_2 = current->white_player_2;
		int white_2_x = white_2 % size;
		int white_2_y = white_2 / size;

		//coordinates of black
		int black_1 = current->black_player;
		int black_1_x = black_1 % size;
		int black_1_y = black_1 / size;
		string str;
		if (black_1_y == white_1_y && (black_1_x == white_1_x + 1 || black_1_x == white_1_x - 1))
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->black_player;
			winning_state->white_player_2 = current->white_player_2;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			for (int k = 0; k < 4; k++)
			{
				int new_place_4_b = places[k];
				if (winning_state->white_player_1 != new_place_4_b && winning_state->white_player_2 != new_place_4_b)
				{
					str = to_string(winning_state->white_player_1); str += ","; str += to_string(winning_state->white_player_2); str += ","; str += to_string(new_place_4_b);
					next_state = myMap[str];
					winning_state->addNeighbour(next_state, false);
					//winning_state->printCurrent();
					//next_state->printCurrent();
				}
			}
		}
		if (black_1_y == white_2_y && (black_1_x == white_2_x + 1 || black_1_x == white_2_x - 1))
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->white_player_1;
			winning_state->white_player_2 = current->black_player;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			for (int k = 0; k < 4; k++)
			{
				int new_place_4_b = places[k];
				if (winning_state->white_player_1 != new_place_4_b && winning_state->white_player_2 != new_place_4_b)
				{
					str = to_string(winning_state->white_player_1); str += ","; str += to_string(winning_state->white_player_2); str += ","; str += to_string(new_place_4_b);
					next_state = myMap[str];
					winning_state->addNeighbour(next_state, false);
					//winning_state->printCurrent();
					//next_state->printCurrent();
				}
			}
		}
		if (black_1_x == white_1_x && (black_1_y == white_1_y + 1 || black_1_y == white_1_y - 1))
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->black_player;
			winning_state->white_player_2 = current->white_player_2;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			for (int k = 0; k < 4; k++)
			{
				int new_place_4_b = places[k];
				if (winning_state->white_player_1 != new_place_4_b && winning_state->white_player_2 != new_place_4_b)
				{
					str = to_string(winning_state->white_player_1); str += ","; str += to_string(winning_state->white_player_2); str += ","; str += to_string(new_place_4_b);
					next_state = myMap[str];
					winning_state->addNeighbour(next_state, false);
					//winning_state->printCurrent();
					//next_state->printCurrent();
				}
			}
		}
		if (black_1_x == white_2_x && (black_1_y == white_2_y + 1 || black_1_y == white_2_y - 1))
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->white_player_1;
			winning_state->white_player_2 = current->black_player;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			for (int k = 0; k < 4; k++)
			{
				int new_place_4_b = places[k];
				if (winning_state->white_player_1 != new_place_4_b && winning_state->white_player_2 != new_place_4_b)
				{
					str = to_string(winning_state->white_player_1); str += ","; str += to_string(winning_state->white_player_2); str += ","; str += to_string(new_place_4_b);
					next_state = myMap[str];
					winning_state->addNeighbour(next_state, false);
					//winning_state->printCurrent();
					//next_state->printCurrent();
				}
			}
		}
	}
	int num;
	boardState* current = (boardState*)q0;
	current->printCurrent();
	Graph g(*all_states, q0);
	OriginGraph* newG = makeASeperatedGraph(g);
	auto end_part_4 = steady_clock::now();
	auto duration = duration_cast<microseconds>(end_part_4 - start);
	if (alwaysEventuallyP(*newG))
	{
		auto end = steady_clock::now();;
		auto duration_gp = duration_cast<microseconds>(end - end_part_4);
		//cout << "MS Took " << duration.count() << "us to calculate" << endl;
		//cout << "It took " << duration_gp.count() << "us to calculate G(P)" << endl << endl;
		//cout << "States - " << newG->nodes.size() << endl;
		cout << " This Graph Has the Always Eventually P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cout << "Or .. do you want to see a randomized run , if so .. press 2 ?" << endl;
		cin >> num;
		//num = 0;
		if (num == 1)
		{
			tryContradictTheHarderGameTrue(*newG, g, false, false);
		}
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				if (num == 2)
					tryContradictTheHarderGameTrue(*newG, g, false, true);
				else
					cout << "You pressed the wrong option, Good Bye" << endl;
	}
	else
	{
		cout << " This Graph doesnt have the Always Eventually P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cout << "Or .. do you want to see a randomized run , if so .. press 2 ?" << endl;
		cin >> num;
		if (num == 1)
		{
			tryContradictTheHarderGameFalse(*newG, g, false);
		}
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				cout << "You pressed the wrong option, Good Bye" << endl;
	}

}
#pragma once
#endif