#ifndef HARDER_GAME

#include <stdio.h>
#include <vector>
#include "Node.h"
#include "Graph.h"
#include "OriginNode.h"
#include "OriginGraph.h"
#include "Algorithms.h"
#include <iostream>



void tryContradictTheHarderGameTrue(OriginGraph& g, Graph& graph, bool GP)
{
	int num = 0;
	bool flag, EnvTurn = true;
	OriginNode* currentNode;
	currentNode = g.q0;
	boardState* current;
	bool condition1;
	if (GP)
		condition1 = num != -1 && currentNode->p == true;
	else
		condition1 = num != -1 && currentNode->Good == true;
	while (condition1)
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

				if (currentNode->neigbours[i]->Good)
					num = i;
			}
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

void PlayHarderGame(int size)
{
	long int wholeSize = size * size;
	vector<Node*>* all_states = new vector<Node*>();

	int index = 0;
	int i = 0, j = 1, k = 2;
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
		int count = 4;
		if (white_1_x == 0)
			count--;
		if (white_1_x == size - 1)
			count--;
		if (white_1_y == 0)
			count--;
		if (white_1_y == size - 1)
			count--;

		//coordinates of white_2
		int white_2 = current->white_player_2;
		int white_2_x = white_2 % size;
		int white_2_y = white_2 / size;
		int count_2 = 4;
		if (white_2_x == 0)
			count_2--;
		if (white_2_x == size - 1)
			count_2--;
		if (white_2_y == 0)
			count_2--;
		if (white_2_y == size - 1)
			count_2--;

		//get blacks coordinates ( to make sure it doesnt move) 
		int black_1 = current->black_player;
		int black_1_x = black_1 % size;
		int black_1_y = black_1 / size;
		int count_3 = 4;
		if (black_1_x == 0)
			count_3--;
		if (black_1_x == size - 1)
			count_3--;
		if (black_1_y == 0)
			count_3--;
		if (black_1_y == size - 1)
			count_3--;

		if (white_1_x == 0 && white_1_y == 0 && white_2_x == 0 && white_2_y == size - 1 && black_1_x == size - 1 && black_1_y == size - 1)
			q0 = all_states->at(i_n);

		//connectin all states that act as moves for each pawn.
		for (size_t j_n = 0; j_n < all_states->size(); j_n++)
		{
			boardState* current_2 = (boardState*)all_states->at(j_n);

			int white_1_2 = current_2->white_player_1;
			int white_1_x_2 = white_1_2 % size;
			int white_1_y_2 = white_1_2 / size;

			int white_2_2 = current_2->white_player_2;
			int white_2_x_2 = white_2_2 % size;
			int white_2_y_2 = white_2_2 / size;

			int black_1_2 = current_2->black_player;
			int black_1_x_2 = black_1_2 % size;
			int black_1_y_2 = black_1_2 / size;

			bool flag_white_1_same_place = (white_1_x == white_1_x_2) && (white_1_y == white_1_y_2);
			bool flag_white_2_same_place = (white_2_x == white_2_x_2) && (white_2_y == white_2_y_2);
			bool flag_black_1_same_place = (black_1_x == black_1_x_2) && (black_1_y == black_1_y_2);


			//cout << "State I" << endl;
			//all_states->at(i_n)->printCurrent();
			//cout << "State J" << endl;
			//all_states->at(j_n)->printCurrent();
			//cout << "-----------------------------------------------------------------------" << endl;
			//white_1 moves

			if (flag_white_2_same_place && flag_black_1_same_place && (white_1_x_2 == white_1_x + 1) && (white_1_y == white_1_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count--;
			}
			if (flag_white_2_same_place && flag_black_1_same_place && (white_1_x_2 == white_1_x - 1) && (white_1_y == white_1_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count--;
			}
			if (flag_white_2_same_place && flag_black_1_same_place && (white_1_x_2 == white_1_x) && (white_1_y == white_1_y_2 + 1))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count--;
			}
			if (flag_white_2_same_place && flag_black_1_same_place && (white_1_x_2 == white_1_x) && (white_1_y == white_1_y_2 - 1))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count--;
			}

			//white _ 2 moves.

			if (flag_white_1_same_place && flag_black_1_same_place && (white_2_x_2 + 1 == white_2_x) && (white_2_y == white_2_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_2--;
			}
			if (flag_white_1_same_place && flag_black_1_same_place && (white_2_x_2 - 1 == white_2_x) && (white_2_y == white_2_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_2--;
			}
			if (flag_white_1_same_place && flag_black_1_same_place && (white_2_x_2 == white_2_x) && (white_2_y + 1 == white_2_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_2--;
			}
			if (flag_white_1_same_place && flag_black_1_same_place && (white_2_x_2 == white_2_x) && (white_2_y - 1 == white_2_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with sys Arch (white)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_2--;
			}

			//black moves.

			if (flag_white_1_same_place && flag_white_2_same_place && (black_1_x_2 + 1 == black_1_x) && (black_1_y == black_1_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with Env Arch (black)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_3--;
			}
			if (flag_white_1_same_place && flag_white_2_same_place && (black_1_x_2 - 1 == black_1_x) && (black_1_y == black_1_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with Env Arch (black)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_3--;
			}
			if (flag_white_1_same_place && flag_white_2_same_place && (black_1_x_2 == black_1_x) && (black_1_y + 1 == black_1_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with Env Arch (black)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_3--;
			}
			if (flag_white_1_same_place && flag_white_2_same_place && (black_1_x_2 == black_1_x) && (black_1_y - 1 == black_1_y_2))
			{
				all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
				//all_states->at(i_n)->printCurrent();
				//cout << "connected with Env Arch (black)" << endl;
				//all_states->at(j_n)->printCurrent();
				count_3--;
			}


			if (count < 0 || count_2 < 0 || count_3 < 0)
			{
				cout << " SOMETHING IS WRONGGGG!!!!!!! " << endl;
				warningFlag = 1;
				break;
			}

			if (count == 0 && (count_2 == count) && (count_3 == count))
				break;
		}
		if (warningFlag == 1)
		{
			cout << " SOMETHING IS WRONGGGG!!!!!!! " << endl;
			break;
		}

	}

	//adding all states that should connect to the winning state.
	for (size_t i = 0; i < all_states->size(); i++)
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

		if ((black_1_x == white_1_x + 1 || black_1_x == white_1_x - 1) && black_1_y == white_1_y)
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->black_player;
			winning_state->white_player_2 = current->white_player_2;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			int places[4] = { 0,size - 1,(size) * (size - 2),(size) * (size - 1) };
			bool flag = 1;
			int num;
			while (flag == 1)
			{
				num = rand() % 4;
				if (winning_state->black_player == places[num] || winning_state->white_player_1 == places[num] || winning_state->white_player_2 == places[num])
				{
					places[num] = places[(num + 1) % 4];
				}
				else
					flag = 0;
			}
			int new_place_4_b = places[num];

			boardState* next_state;
			for (size_t j = 0; j < all_states->size(); j++)
			{
				next_state = (boardState*)all_states->at(j);
				if (next_state->white_player_1 == winning_state->white_player_1 && next_state->white_player_2 == winning_state->white_player_2 && next_state->black_player == new_place_4_b)
				{
					winning_state->addNeighbour(next_state, false);
					//next_state->printCurrent();
					break;
				}
			}
		}
		if ((black_1_x == white_2_x + 1 || black_1_x == white_2_x - 1) && black_1_y == white_2_y)
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->white_player_1;
			winning_state->white_player_2 = current->black_player;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			int places[4] = { 0,size - 1,(size ) * (size - 2),(size) * (size - 1) };
			bool flag = 1;
			int num;
			while (flag == 1)
			{
				num = rand() % 4;
				if (winning_state->black_player == places[num] || winning_state->white_player_1 == places[num] || winning_state->white_player_2 == places[num])
				{
					places[num] = places[(num + 1) % 4];
				}
				else
					flag = 0;
			}
			int new_place_4_b = places[num];

			boardState* next_state;
			for (size_t j = 0; j < all_states->size(); j++)
			{
				next_state = (boardState*)all_states->at(j);
				if (next_state->white_player_1 == winning_state->white_player_1 && next_state->white_player_2 == winning_state->white_player_2 && next_state->black_player == new_place_4_b)
				{
					winning_state->addNeighbour(next_state, false);
					//next_state->printCurrent();
					break;
				}
			}
		}
		if ((black_1_y == white_1_y + 1 || black_1_y == white_1_y - 1) && black_1_x == white_1_x)
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->black_player;
			winning_state->white_player_2 = current->white_player_2;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			int places[4] = { 0,size - 1,(size) * (size - 2),(size) * (size - 1) };
			bool flag = 1;
			int num;
			while (flag == 1)
			{
				num = rand() % 4;
				if (winning_state->black_player == places[num] || winning_state->white_player_1 == places[num] || winning_state->white_player_2 == places[num])
				{
					places[num] = places[(num + 1) % 4];
				}
				else
					flag = 0;
			}
			int new_place_4_b = places[num];

			boardState* next_state;
			for (size_t j = 0; j < all_states->size(); j++)
			{
				next_state = (boardState*)all_states->at(j);
				if (next_state->white_player_1 == winning_state->white_player_1 && next_state->white_player_2 == winning_state->white_player_2 && next_state->black_player == new_place_4_b)
				{
					winning_state->addNeighbour(next_state, false);
					//next_state->printCurrent();
					break;
				}
			}
		}
		if ((black_1_y == white_2_y + 1 || black_1_y == white_2_y - 1) && black_1_x == white_2_x)
		{
			boardState* winning_state = new boardState(index, true, size);
			index++;
			winning_state->white_player_1 = current->white_player_1;
			winning_state->white_player_2 = current->black_player;
			winning_state->black_player = current->black_player;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, true);
			//winning_state->printCurrent();
			int places[4] = { 0,size - 1,(size) * (size - 2),(size) * (size - 1) };
			bool flag = 1;
			int num;
			while (flag == 1)
			{
				num = rand() % 4;
				if (winning_state->black_player == places[num] || winning_state->white_player_1 == places[num] || winning_state->white_player_2 == places[num])
				{
					places[num] = places[(num + 1) % 4];
				}
				else
					flag = 0;
			}
			int new_place_4_b = places[num];

			boardState* next_state;
			for (size_t j = 0; j < all_states->size(); j++)
			{
				next_state = (boardState*)all_states->at(j);
				if (next_state->white_player_1 == winning_state->white_player_1 && next_state->white_player_2 == winning_state->white_player_2 && next_state->black_player == new_place_4_b)
				{
					winning_state->addNeighbour(next_state, false);
					//next_state->printCurrent();
					break;
				}
			}
		}
	}


	int num;
	boardState* current = (boardState*)q0;
	current->printCurrent();
	Graph g(*all_states, q0);

	OriginGraph* newG = makeASeperatedGraph(g);
	if (alwaysEventuallyP(*newG))
	{
		cout << " This Graph Has the Always Eventually P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cin >> num;
		if (num == 1)
		{
			tryContradictTheHarderGameTrue(*newG,g, false);
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
			//tryContradictTheHarderGameFalse(*newG, false);
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