#ifndef SIMPLE_GAME

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Node.h"
#include "Graph.h"
#include "OriginNode.h"
#include "OriginGraph.h"
#include "Algorithms.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <chrono> 
using namespace std::chrono; 
class boardState : public Node
{
public:
	int white_player_1;
	int white_player_2;
	int black_player;
	int boardSize;
	vector<int> *numsToErase;

	boardState(int index, bool prop, int size) :Node(index, prop), boardSize(size) { numsToErase = NULL; }
	void printCurrent(bool obstacles=false)
	{
		//get white pawns cordinates
		int white_1 = white_player_1;
		int white_1_x = white_1 % boardSize;
		int white_1_y = white_1 / boardSize;

		//coordinates of white_2
		int white_2 = white_player_2;
		int white_2_x = white_2 % boardSize;
		int white_2_y = white_2 / boardSize;

		//get blacks coordinates ( to make sure it doesnt move) 
		int black_1 = black_player;
		int black_1_x = black_1 % boardSize;
		int black_1_y = black_1 / boardSize;
		bool flag = 0;
		if (black_player == white_player_1 || black_player == white_player_2)
			flag = 1;
		int index = 0;
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{

				if ((j == white_1_x) && (i == white_1_y) && (j == black_1_x) && (i == black_1_y))
					cout << "_W&B_ | ";
				else
					if ((j == white_2_x) && (i == white_2_y) && (j == black_1_x) && (i == black_1_y))
						cout << "_W&B_ | ";
					else
						if ((j == white_1_x) && (i == white_1_y))
							cout << "__W__ | ";
						else
							if ((j == white_2_x) && (i == white_2_y))
								cout << "__W__ | ";
							else
								if ((j == black_1_x) && (i == black_1_y))
									cout << "__B__ | ";
								else
									if (obstacles)
									{
										bool flag1 = false;
										for (size_t p = 0; p < numsToErase->size(); p++)
										{
											if (index == numsToErase->at(p))
												flag1 = true;
										}
										if(flag1==true)
											cout << "_XXX_ | ";
										else
											cout << "_____ | ";
									}
									else
										cout << "_____ | ";

				index++;
			}
			cout << endl;
		}
		if (flag == 1)
			cout << "SYSTEM WINSS!!!!!!" << endl << endl;
		cout << endl << endl;
	}

	
};

void printCleanBoardWithNumbers(int boardSize, vector<int> numsToErase)
{
	int index = 0;
	int wPawn = (boardSize - 1) * boardSize;
	int bPawn = wPawn + boardSize - 1;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			bool flag = false;
			for (size_t k = 0; k < numsToErase.size(); k++)
			{
				if (numsToErase[k] == index)
				{
					flag = true;
				}
			}
			if (flag == 1)
				cout << "___X__ |";
			else
			{
				if (index == 0 || index == wPawn || index == bPawn)
				{
					if(index == bPawn)
						cout << "__B" <<"P" << "__ |";
					else
						cout << "__W" << "P" << "__ |";
				}
				else
				{
					if (index <= 9)
						cout << "___" << index << "__ |";
					else
						cout << "__" << index << "__ |";
				}
			}

			index++;
		}
		cout << endl;
	}
	cout << endl ;
}

void tryContradictTrueTheGame(OriginGraph& g, Graph& graph, bool GP,bool randomize_run,bool obstacles)
{
	int num = 0,num_of_moves;
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
	while (condition1)
	{
		if (!EnvTurn)
		{
			cout << "==============================================================================================" << endl;
			cout << "Current node is V" << currentNode->index << endl;
			current = (boardState*)graph.nodes[currentNode->index];
			current->printCurrent(obstacles);
			cout << "It has " << currentNode->neigbours.size() << " neighbours System can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				current->printCurrent(obstacles);

				if (currentNode->neigbours[i]->Good)
					num = i;
			}
			cout << endl << "Sys chooses V" << currentNode->neigbours[num]->index << endl;
			current = (boardState*)graph.nodes[currentNode->neigbours[num]->index];
			current->printCurrent(obstacles);
			currentNode = currentNode->neigbours[num];
			EnvTurn = true;
		}
		else
		{
			flag = false;
			cout << "==============================================================================================" << endl;
			cout << "Current node is V" << currentNode->index << endl;
			current = (boardState*)graph.nodes[currentNode->index];
			current->printCurrent(obstacles);
			cout << "It has " << currentNode->neigbours.size() << " neighbours You(Enviroment) can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				current->printCurrent(obstacles);
			}
			cout << endl << "Please press the index of the node you want to go to , if you give up , choose -1" << endl;
			if (num_of_moves)
			{
				num_of_moves--;
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
					current->printCurrent(obstacles);
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

void tryContradictFalseTheGame(OriginGraph& g, Graph& graph, bool GP, bool randomize_run,bool obstacles)
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
			current->printCurrent(obstacles);
			cout << "It has " << currentNode->neigbours.size() << " neighbours Environment can Go to" << endl;
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				//currentNode->printCurrent(obstacles);
				//cout << "V" << currentNode->neigbours[i]->index << endl;
				//current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				//current->printCurrent(obstacles);
				if (!currentNode->neigbours[i]->Good && currentNode->neigbours[i]->distance_from_notP < currentNode->distance_from_notP)
					num = i;
			}
			if (currentNode->neigbours.size() == 0)
			{
				cout << "There are no nodes for Env to move on to! " << endl;
				cout << "There go G(p) doesn't occur! " << endl;
				break;

			}
			else
			{
				cout << endl << "Env chooses V" << currentNode->neigbours[num]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[num]->index];
				current->printCurrent(obstacles);
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
			current->printCurrent(obstacles);
			cout << "It has " << currentNode->neigbours.size() << " neighbours You(System) can Go to" << endl;

			if (currentNode->neigbours.size() == 0)
			{
				cout << "System has no neighbours left. It can't go anywhere." << endl;
				cout << "There go G(p) doesn't occur! " << endl;
				return;

			}
			for (size_t i = 0; i < currentNode->neigbours.size(); i++)
			{
				cout << "V" << currentNode->neigbours[i]->index << endl;
				current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
				current->printCurrent(obstacles);
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
					cout << endl << "Sys chooses V" << currentNode->neigbours[i]->index << endl;
					current = (boardState*)graph.nodes[currentNode->neigbours[i]->index];
					current->printCurrent(obstacles);
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
			cout << "This node's P value is false , You Have been Caught!! " << endl << "Thank you for trying!" << endl;
		else
			cout << "Our Always Eventually P algorithm is wrong , sorry to Disappoint from this node i cant guarentee i can go to a p node." << endl;
	else
		cout << "Thanks for trying !" << endl;
}

void PlaySimpleGame(int size)
{
	int num = 0;
	long int wholeSize = size * size;
	vector<Node*>* all_states = new vector<Node*>();
	vector<int> numsToErase;
	bool obstacles = false;

	cout << "Do you want to put obstacles ?  1 for yes , 0 or else for no" << endl;
	//cin >> num;
	num = 0;
	if (num == 1)
	{
		obstacles = true;
		while (num != -1)
		{
			cout << "=========================================================================" << endl;
			printCleanBoardWithNumbers(size, numsToErase);
			cout << "Where do you want to put Obstecles?" << endl;
			cout << "Press the number of the Space, or press -1 to end" << endl;
			cin >> num;
			bool flag = 0;
			for (size_t i = 0; i < numsToErase.size(); i++)
			{
				if (num == numsToErase[i] )
				{
					cout << "Please choose another number, This one is taken" << endl;
					flag = 1;
				}
			}
			if (num == 0 || num == wholeSize - 1 || num == wholeSize - size)
			{
				cout << "You can't put your obstacles on the Pieces" << endl;
				flag = 1;
			}
			if (num>=0 &&flag == 0 && num < wholeSize)
			{
				numsToErase.push_back(num);
			}
			else
				if(num!=-1)
					cout << "Please follow the rules" << endl;
		}
	}
	else
	{
		cout << "You chose No obstacles , We will start the Game." << endl;
	}
	
	cout << "-----------------------------------------------------------------" << endl;
	cout << "We will start calculating the Game." << endl;
	//auto start = steady_clock::now();
	int index = 0;
	int i = 0, j = 1, k = 2;
	for (i = 0; i < wholeSize; i++)
	{
		bool flag1 = false;
		for (size_t ind = 0; ind < numsToErase.size(); ind++)
		{
			if (numsToErase[ind] == i)
				flag1 = true;
		}
		if (i != j && i != k && flag1==false)
			for (j = 0; j < wholeSize; j++)
			{
				bool flag2 = false;
				for (size_t ind = 0; ind < numsToErase.size(); ind++)
				{
					if (numsToErase[ind] == j)
						flag2 = true;
				}
				if (j != i && j != k && flag2 == false)
					for (k = 0; k < wholeSize; k++)
					{
						bool flag3 = false;
						for (size_t ind = 0; ind < numsToErase.size(); ind++)
						{
							if (numsToErase[ind] == k)
								flag3 = true;
						}
						if (k != i && k != j&& flag3==false)
						{
							//cout << " i = " << i << " j = " << j << " k = " << k << endl;
							boardState* new_state = new boardState(index, true, size);
							index++;
							new_state->white_player_1 = i;
							new_state->white_player_2 = j;
							new_state->black_player = k;
							new_state->numsToErase = &numsToErase;
							all_states->push_back(new_state);
							//new_state->printCurrent(obstacles);
						}
					}
			}
	}
	//now lets connect nodes with Sys arches (white moves)
	//auto end_part_1 = steady_clock::now();
	//auto duration_p1 = duration_cast<microseconds>(end_part_1 - start);
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

		if (q0==NULL&&white_1_x == 0 && white_1_y == 0 && white_2_x == 0 && white_2_y == size - 1 && black_1_x == size - 1 && black_1_y == size - 1)
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

			bool flag_white_1_same_place = current->white_player_1 == current_2->white_player_1;
			bool flag_white_2_same_place = current->white_player_2 == current_2->white_player_2;
			bool flag_black_1_same_place = current->black_player == current_2->black_player;


			//cout << "State I" << endl;
			//all_states->at(i_n)->printCurrent(obstacles);
			//cout << "State J" << endl;
			//all_states->at(j_n)->printCurrent(obstacles);
			//cout << "-----------------------------------------------------------------------" << endl;
			//white_1 moves
			if (flag_white_2_same_place && flag_black_1_same_place)
			{
				if ((white_1_y == white_1_y_2))
				{
					if (white_1_x_2 == white_1_x + 1|| white_1_x_2 == white_1_x - 1)
					{
						all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
						//all_states->at(i_n)->printCurrent(obstacles);
						//cout << "connected with sys Arch (white)" << endl;
						//all_states->at(j_n)->printCurrent(obstacles);
						count--;
					}
				}
				if (white_1_x_2 == white_1_x)
				{
					if (white_1_y == white_1_y_2 + 1|| white_1_y == white_1_y_2 - 1)
					{
						all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
						//all_states->at(i_n)->printCurrent(obstacles);
						//cout << "connected with sys Arch (white)" << endl;
						//all_states->at(j_n)->printCurrent(obstacles);
						count--;
					}
				}
			}
			//white _ 2 moves.
			if (flag_white_1_same_place && flag_black_1_same_place)
			{
				if (white_2_y == white_2_y_2)
				{
					if (white_2_x_2 + 1 == white_2_x|| white_2_x_2 - 1 == white_2_x)
					{
						all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
						//all_states->at(i_n)->printCurrent(obstacles);
						//cout << "connected with sys Arch (white)" << endl;
						//all_states->at(j_n)->printCurrent(obstacles);
						count_2--;
					}
				}
				if (white_2_x_2 == white_2_x)
				{
					if (white_2_y + 1 == white_2_y_2|| white_2_y - 1 == white_2_y_2)
					{
						all_states->at(i_n)->addNeighbour(all_states->at(j_n), false);
						//all_states->at(i_n)->printCurrent(obstacles);
						//cout << "connected with sys Arch (white)" << endl;
						//all_states->at(j_n)->printCurrent(obstacles);
						count_2--;
					}
				}
			}
			//black moves.
			if (flag_white_1_same_place && flag_white_2_same_place)
			{
				if (black_1_y == black_1_y_2)
				{
					if (black_1_x_2 + 1 == black_1_x|| black_1_x_2 - 1 == black_1_x)
					{
						all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
						//all_states->at(i_n)->printCurrent(obstacles);
						//cout << "connected with Env Arch (black)" << endl;
						//all_states->at(j_n)->printCurrent(obstacles);
						count_3--;
					}
				}
				if (black_1_x_2 == black_1_x)
				{
					if (black_1_y + 1 == black_1_y_2|| (black_1_y - 1 == black_1_y_2))
					{
						all_states->at(i_n)->addNeighbour(all_states->at(j_n), true);
						//all_states->at(i_n)->printCurrent(obstacles);
						//cout << "connected with Env Arch (black)" << endl;
						//all_states->at(j_n)->printCurrent(obstacles);
						count_3--;
					}
				}
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

	//auto end_part_2 = steady_clock::now();
	//auto duration_p2 = duration_cast<microseconds>(end_part_2 - end_part_1);
	

	//now we need to choose which nodes contain P in them (white moves where black is reachable in one step)
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

		if (black_1_y == white_1_y && (black_1_x == white_1_x + 1 || black_1_x == white_1_x - 1))
		{
			boardState* winning_state = new boardState(index, false, size);
			index++;
			winning_state->white_player_1 = current->black_player;
			winning_state->white_player_2 = current->white_player_2;
			winning_state->black_player = current->black_player;
			winning_state->numsToErase = &numsToErase;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, false);

			//current->addNeighbour(winning_state, false);
			//current->printCurrent(obstacles);
		}
		if (black_1_y == white_2_y &&(black_1_x == white_2_x + 1 || black_1_x == white_2_x - 1))
		{
			boardState* winning_state = new boardState(index, false, size);
			index++;
			winning_state->white_player_1 = current->white_player_1;
			winning_state->white_player_2 = current->black_player;
			winning_state->black_player = current->black_player;
			winning_state->numsToErase = &numsToErase;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, false);

			//current->addNeighbour(winning_state, false);
			//current->printCurrent(obstacles);
		}

		if (black_1_x == white_1_x &&(black_1_y == white_1_y + 1 || black_1_y == white_1_y - 1) )
		{
			boardState* winning_state = new boardState(index, false, size);
			index++;
			winning_state->white_player_1 = current->black_player;
			winning_state->white_player_2 = current->white_player_2;
			winning_state->black_player = current->black_player;
			winning_state->numsToErase = &numsToErase;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, false);

			//current->addNeighbour(winning_state, false);
			//current->printCurrent(obstacles);
		}
		if (black_1_x == white_2_x && (black_1_y == white_2_y + 1 || black_1_y == white_2_y - 1) )
		{
			boardState* winning_state = new boardState(index, false, size);
			index++;
			winning_state->white_player_1 = current->white_player_1;
			winning_state->white_player_2 = current->black_player;
			winning_state->black_player = current->black_player;
			winning_state->numsToErase = &numsToErase;
			all_states->push_back(winning_state);
			current->addNeighbour(winning_state, false);

			//current->addNeighbour(winning_state, false);
			//current->printCurrent(obstacles);
		}


	}

	

	boardState* current = (boardState*)q0;
	current->printCurrent(obstacles);
	Graph g(*all_states, q0);
	//auto end_part_3 = steady_clock::now();
	//auto duration_p3 = duration_cast<microseconds>(end_part_3 - end_part_2);
	

	OriginGraph* newG = makeASeperatedGraph(g);
	auto end_part_4 = steady_clock::now();
	//auto duration_p4 = duration_cast<microseconds>(end_part_4 - end_part_3);
	//auto duration = duration_cast<microseconds>(end_part_4 - start);
	if (alwaysP(*newG))
	{
		cout << " This Graph Has the Always P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cout << "Or .. do you want to see a randomized run , if so .. press 2 ?" << endl;
		cin >> num;
		if (num == 1)
			tryContradictTrueTheGame(*newG, g, true,false, obstacles);
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				if (num == 2)
					tryContradictTrueTheGame(*newG, g, true, true, obstacles);
				else
					cout << "You pressed the wrong option, Good Bye" << endl;
	}
	else
	{
		/*auto end = steady_clock::now();;
		auto duration_gp = duration_cast<microseconds>(end - end_part_4);
		auto all_time = duration_cast<microseconds>(end - end_part_2);
		cout << "p1 took " << duration_p1.count() << "us to calculate" << endl;
		cout << "p2 took " << duration_p2.count() << "us to calculate" << endl;
		cout << "p3 took " << duration_p3.count() << "us to calculate" << endl;
		cout << "p4 Took " << duration_p4.count() << "us to calculate" << endl;
		cout << "MS Took " << duration.count() << "us to calculate" << endl;
		cout << "It took " << duration_gp.count() << "us to calculate G(P)" << endl << endl;
		cout << "It took " << all_time.count() << "us to calculate ALL " << endl<<endl;*/

		cout << " This Graph doesnt have the Always P Propery " << endl;
		cout << " do you want to try and contradict it? press 1 for Yes , 0 for no" << endl;
		cout << "Or .. do you want to see a randomized run , if so .. press 2 ?" << endl;
		cin >> num;
		if (num == 1)
		{
			tryContradictFalseTheGame(*newG, g, true,false,obstacles);
		}
		else
			if (num == 0)
				cout << "okay , Thank you and GoodBye" << endl;
			else
				if (num == 2)
					tryContradictFalseTheGame(*newG, g, true, true, obstacles);
				else
				cout << "You pressed the wrong option, Good Bye" << endl;
	}

}
#endif // !1